#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "main.h"

#include "helper.h"
#include "toolbox.h"
#include "types.h"
#include "system.h"

#define SERVICE_ENTRANCES \
{ \
  "unlink",  "link",    "disable", \
  "enable",  "status",  "start", \
  "restart", "stop",    "purge", \
  "list",    "enabled", "journal" \
}

const char* appname = NULL;

static void
set_appname(const char* name)
{
  const char* posix_separator = strrchr(name, '/');
  const char* dos_separator = strrchr(name, '\\');
  const char* separator = (posix_separator > dos_separator) ? posix_separator : dos_separator;

  if (separator == NULL)
  { appname = (char*)name; }
  else
  { appname = (char*)(separator+1); }
}

static int
manage_application(int argc, char* argv[])
{
  int opt = 0;
  while ((opt = getopt(argc, argv, ":hv")) != -1)
  {
    switch (opt)
    {
      case 'h': print_help(); return 0;
      case 'v': print_version(); return 0;
      case '?': return print_usage();
      default: break;
    }
  }

  /* appname only lead to help */
  if (argc < 2)
  { return print_usage(); }

  /* TODO: Parse one service at time, if multiple. */
  if (argc > 3)
  { errprintf("More than one service given."); return 1; }

  /* Entrances that depend on service */
  char* service = NULL;
  const char* mode = argv[1];
  const char* entrances[] = SERVICE_ENTRANCES;
  service_mode mIndex = mstrncmp(mode, entrances, 12);

  switch (mIndex)
  {
    case MODE_NONE:
    {
      errprintf(strfmt("'%s' is not a mode.", argv[1]));
    } return 1;
    case MODE_LIST:
    case MODE_JOURNAL:
    case MODE_ENABLED: break;
    default:
    {
      if (argc < 3)
      { errprintf("A service is needed. No service found."); return 1; }

      /* Everything here need to be run as root */
      if (geteuid() != 0)
      { errprintf("Must be root to use this command."); return 1; }

      if (ifdir(strfmt("%s/%s", RUNIT_AVAILABLE_SERVICES, service = argv[2])) == true)
      { errprintf("No service found."); return 1; }
    } break;
  }

  switch (mIndex)
  {
    case MODE_UNLINK:
    {
      if (ifdir(strfmt("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service)) == true)
      { errprintf("Service already unlinked."); return 1; }

      rm(strfmt("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service));
      printf("%s%s%s: Unlinked service \"%s\".\n", COLOUR_GREEN, appname, COLOUR_RESET, service);
    } break;
    case MODE_LINK:
    {
      if (ifdir(strfmt("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service)) == false)
      { errprintf("Service already linked."); return 1; }

      link_service(service);
      touch(strfmt("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service));
      printf("%s%s%s: Linked service \"%s\".\n", COLOUR_GREEN, appname, COLOUR_RESET, service);
    } break;
    case MODE_DISABLE:
    {
      if (ifdir(strfmt("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service)) == true)
      { errprintf("Service not linked."); return 1; }
      if (iffile(strfmt("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service)) == false)
      { errprintf("Service already disabled."); return 1; }

      touch(strfmt("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service));
      printf("%s%s%s: Disabled service \"%s\" from boot.\n", COLOUR_GREEN, appname, COLOUR_RESET, service);
    } break;
    case MODE_ENABLE:
    {
      if (ifdir(strfmt("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service)) == true)
      { errprintf("Service not linked."); return 1; }
      if (iffile(strfmt("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service)) == true)
      { errprintf("Service already enabled."); return 1; }

      rm(strfmt("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service));
      printf("%s%s%s: Enabled service \"%s\" from boot.\n", COLOUR_GREEN, appname, COLOUR_RESET, service);
    } break;
    case MODE_STATUS:
    case MODE_STOP:
    case MODE_RESTART:
    case MODE_START:
    {
      exec(strfmt("sv '%s' '%s'", mode, service));
    } break;
    case MODE_PURGE:
    {
      printf("%sFAIL SAFE SECURITY%s: Are you sure you want to delete \"%s\" service? (N/y)> ", COLOUR_RED, COLOUR_RESET, service);
      switch (fgetc(stdin))
      {
        case '1': case 'Y': case 'y':
        {
          rm(strfmt("%s/%s", RUNIT_LOADED_SERVICE_PATH, service));
          rm(strfmt("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service));
          rm(strfmt("%s/%s", RUNIT_AVAILABLE_SERVICES, service));
        } break;
        default: return 1;
      }
    } break;
    case MODE_LIST:
    {
      exec(strfmt("ls '%s'", RUNIT_AVAILABLE_SERVICES));
    } break;
    case MODE_ENABLED:
    {
      if (argc > 2)
      {
        if (ifdir(strfmt("%s/%s", RUNIT_DEFAULT_SERVICE_PATH, service)) == true)
        { errprintf("Service not linked."); return 1; }
        if (iffile(strfmt("%s/%s/down", RUNIT_DEFAULT_SERVICE_PATH, service)) == false)
        { errprintf("Service not enabled."); return 1; }

        printf("%s%s%s: Service is enabled.\n", COLOUR_GREEN, appname, COLOUR_RESET);
        return 0;
      }

      exec(strfmt(
        "printf \"\033[34m\"; \
        cd %s && ls -d */ | grep -v \"$(dirname $(ls -d */down))\" | sed \'s/\\///g\' | column -c $(tput cols); \
        printf \"\033[0m\"", RUNIT_DEFAULT_SERVICE_PATH
      ));
    } break;
    case MODE_JOURNAL:
    {
      FILE* journal = fopen("/var/log/runit-journal.log", "r");
      if (journal == NULL)
      { errprintf("Could not read the kernel logs."); return 1; }

      while (feof(journal) == 0)
      { printf("%c", fgetc(journal)); }

      fclose(journal);
    } break;
    default: return print_usage();
  }

  return 0;
}

int
main(int argc, char* argv[])
{
  set_appname(argv[0]);
  return manage_application(argc, argv);
}

