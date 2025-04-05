#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "types.h"
#include "main.h"
#include "helper.h"
#include "toolbox.h"
#include "system.h"

char *appname = NULL;
int _argc = 0; char **_argv = NULL;

static void
set_appname(const char *name)
{
  appname = (char*)name;
}

static void
set_parameters(int argc, char *argv[])
{
  _argc = argc;
  _argv = argv;
}

static int
manage_application(void)
{
  int opt = 0;
  while ((opt = getopt(_argc, _argv, ":hv")) != -1)
  {
    switch (opt)
    {
      case 'h': print_help(); return 0;
      case 'v': print_version(); return 0;
      case '?': return print_usage();
      default: break;;
    }
  }

  /* appname only lead to help */
  switch (_argc)
  { case 0: case 1: return print_usage(); default: break; }
  char *mode = _argv[1];

  /* Entrances that depend on service */
  const char *entrances[] = {"unlink","link","disable","enable","status","start","restart","stop","purge","list","enabled","journal"};
  unsigned char mode_index = 0;
  switch (mode_index = mstrncmp(mode, entrances, sizeof(entrances)))
  {
    case 0: fprintf(stderr, "%serror%s: '%s' is not a mode.\n", COLOUR_RED, COLOUR_RESET, _argv[1]); return 1;
    case 10: case 11: case 12:
    {
      switch (_argc)
      {
        case 0: case 1: case 2:
        {
          switch (mode_index)
          {
            /* application list */
            case 10:
            {
              exec("ls '%s'", RUNIT_AVAILABLE_SERVICES);
            } return 0;

            /* application enabled */
            case 11:
            {
              exec("printf \"\033[34m\"; \
                    for service in $(ls '%s'); do \
                      if [ ! -f '%s/$service/down' ]; then \
                        SERVICES=\"${SERVICES} $service\"; \
                      fi \
                    done; \
                    printf \"${SERVICES}\n\"; \
                    printf \"\033[0m\"", RUNIT_DEFAULT_SERVICE_PATH, RUNIT_DEFAULT_SERVICE_PATH);
            } return 0;

            /* application journal */
            case 12:
            {
              FILE* journal = fopen("/var/log/runit-journal.log", "r");
              if (journal == NULL)
              {
                fprintf(stderr, "Could not listen to kernel.\n");
                return 1;
              }

              char message[256] = {0};
              while (fgets(message, sizeof(message), journal) != NULL)
              { printf("%s", message); }

              fclose(journal);
            } return 0;
            default: return print_usage();
          }
        } break;
        default: break;
      }
    }
    default:
    {
      /* Everything here need to be run as root */
      switch (geteuid())
      { case 0: break; default: fprintf(stderr, "%serror%s: Must be root to use this command.\n", COLOUR_RED, COLOUR_RESET); return 1; }

      switch (_argc)
      { case 0: case 1: case 2: fprintf(stderr, "%serror%s: A service is needed. No service found.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }

      char *service = _argv[2];

      switch (ifdir("%s/%s", RUNIT_AVAILABLE_SERVICES, service))
      { case 0: fprintf(stderr, "%serror%s: No service found.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }

      switch (mode_index)
      {
        /* application unlink <service> */
        case 1:
        {
          switch (ifdir("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service))
          { case 0: fprintf(stderr, "%serror%s: Service already unlinked.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }

          rm("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service);
          printf("%s%s%s: Unlinked service \"%s\".\n", COLOUR_GREEN, appname, COLOUR_RESET, service);
        } return 0;

        /* application link <service> */
        case 2:
        {
          switch (ifdir("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service))
          { case 1: fprintf(stderr, "%serror%s: Service already linked.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }

          link_service(service);
          touch("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service);
          printf("%s%s%s: Linked service \"%s\".\n", COLOUR_GREEN, appname, COLOUR_RESET, service);
        } return 0;

        /* application disable <service> */
        case 3:
        {
          switch (ifdir("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service) )
          { case 0: fprintf(stderr, "%serror%s: Service not linked.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }
          switch (iffile("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service))
          { case 1: fprintf(stderr, "%serror%s: Service already disabled.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }

          touch("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service);
          printf("%s%s%s: Disabled service \"%s\" from boot.\n", COLOUR_GREEN, appname, COLOUR_RESET, service);
        } return 0;

        /* application enable <service> */
        case 4:
        {
          switch (ifdir("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service))
          { case 0: fprintf(stderr, "%serror%s: Service not linked.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }
          switch (iffile("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service))
          { case 0: fprintf(stderr, "%serror%s: Service already enabled.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }

          rm("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service);
          printf("%s%s%s: Enabled service \"%s\" from boot.\n", COLOUR_GREEN, appname, COLOUR_RESET, service);
        } return 0;

        /* application status/stop/restart/start <service> */
        case 5: case 6: case 7: case 8:
        {
          exec("sv '%s' '%s'", mode, service);
        } return 0;

        /* application purge <service> */
        case 9:
        {
          printf("%sFAIL SAFE SECURITY%s: Are you sure you want to delete \"%s\" service? (N/y)> ", COLOUR_RED, COLOUR_RESET, service);
          switch (fgetc(stdin))
          {
            case '1': case 'Y': case 'y':
            {
              rm("%s/%s", RUNIT_LOADED_SERVICE_PATH, service);
              rm("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service);
              rm("%s/%s", RUNIT_AVAILABLE_SERVICES, service);
              return 0;
            } break;
            default: return 1;
          }
        } break;

        /* application enabled <service> */
        case 11:
        {
          switch (ifdir("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service))
          { case 0: fprintf(stderr, "%serror%s: Service not linked.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }
          switch (iffile("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service))
          { case 1: fprintf(stderr, "%serror%s: Service not enabled.\n", COLOUR_RED, COLOUR_RESET); return 1; default: break; }

          printf("%s%s%s: Service is enabled.\n", COLOUR_GREEN, appname, COLOUR_RESET);
        } return 0;
        default: return print_usage();
      }
    } break;
  }

  return 0;
}

int
main(int argc, char *argv[])
{
  set_parameters(argc, argv);
  set_appname(_argv[0]);
  return manage_application();
}

