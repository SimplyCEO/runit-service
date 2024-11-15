#!/bin/sh

# Directories
RUNIT_AVAILABLE_SERVICES="/etc/runit/sv"
RUNIT_LOADED_SERVICE_PATH="/run/runit/service"
RUNIT_DEFAULT_SERVICE_PATH="/etc/runit/runsvdir/default"

# Files
RUNIT_DISABLED_SERVICE="/etc/runit/runsvdir/default/$2/down"

help_function()
{
  printf "runit-service: A custom tool to manage runit services.\n"
  printf "\n"
  printf "Usage: runit-service <mode> <service>\n"
  printf "\n"
  printf "Available modes:\n"
  printf "\tlist    -  List the services located at '/etc/runit/sv'.\n"
  printf "\tunlink  -  Unlink the service from '/etc/runit/runsvdir/default'.\n"
  printf "\tlink    -  Link the service from '/etc/runit/sv' to '/etc/runit/runsvdir/default'.\n"
  printf "\tenabled -  List the enabled services located at '/etc/runit/runsvdir/default'.\n"
  printf "\tdisable -  Disable a service from activating at boot.\n"
  printf "\tenable  -  Enable a service activation after boot.\n"
  printf "\tstatus  -  Display the service information.\n"
  printf "\tstart   -  Start the service.\n"
  printf "\trestart -  Stop and start the service.\n"
  printf "\tstop    -  Stop the service.\n"
  exit 0
}

version_function()
{
  printf "runit-service v0.1:\n"
  printf "\tGitHub: https://github.com/SimplyCEO/runit-service.git\n"
  printf "\tGitLab: https://gitlab.com/SimplyCEO/runit-service.git\n"
  exit 0
}

OPTIONS=`getopt -o vh --long version:,help -- "$@"`
eval set -- "${OPTIONS}"
while true; do
  case "$1" in
    -h|--help) help_function; shift ;;
    -v|--version) version_function; shift ;;
    --) shift; break ;;
    *) break ;;
  esac
done

# Code might be messed, but intention is to put in C
case "$1" in
  disable|enable|unlink|link|status|start|restart|stop)
    if [ "$(whoami)" != "root" ]; then printf "\033[31merror\033[0m: Must be root to use this command.\n"; exit 1; fi

    if [ -z "$2" ]; then printf "\033[31merror\033[0m: A service is needed. No service found.\n"; exit 1; fi
    if [ ! -d "${RUNIT_AVAILABLE_SERVICES}/$2" ]; then printf "\033[31merror\033[0m: No service found.\n"; exit 1; fi

    case "$1" in
      unlink) rm "${RUNIT_DEFAULT_SERVICE_PATH}/$2"; exit 0 ;;
      link)
        # Cannot link an already linked service
        if [ -d "${RUNIT_DEFAULT_SERVICE_PATH}/$2" ]; then
          printf "\033[31merror\033[0m: Service already linked.\n"
          exit 1
        fi
        ln -s "${RUNIT_AVAILABLE_SERVICES}/$2" "${RUNIT_DEFAULT_SERVICE_PATH}/$2"
        touch "${RUNIT_DISABLED_SERVICE}"
        printf "\033[32mrunit-service\033[0m: Linked service \"$2\".\n"
        exit 0
        shift
        ;;
      disable)
        # Cannot disable a service that is not linked
        if [ ! -d "${RUNIT_DEFAULT_SERVICE_PATH}/$2" ]; then
          printf "\033[31merror\033[0m: Service not linked.\n"
          exit 1
        fi
        # Cannot disable a service if it is already down
        if [ -f "${RUNIT_DISABLED_SERVICE}" ]; then
          printf "\033[31merror\033[0m: Service already disabled.\n"
          exit 1
        fi
        touch "${RUNIT_DISABLED_SERVICE}"
        printf "\033[32mrunit-service\033[0m: Disabled service \"$2\" from boot.\n"
        exit 0
        shift
        ;;
      enable)
        # Cannot enable a service that is not linked
        if [ ! -d "${RUNIT_DEFAULT_SERVICE_PATH}/$2" ]; then
          printf "\033[31merror\033[0m: Service not linked.\n"
          exit 1
        fi
        # Cannot enable a service if it is already up
        if [ ! -f "${RUNIT_DISABLED_SERVICE}" ]; then
          printf "\033[31merror\033[0m: Service already enabled.\n"
          exit 1
        fi
        rm -f "${RUNIT_DISABLED_SERVICE}"
        printf "\033[32mrunit-service\033[0m: Enabled service \"$2\" to boot.\n"
        exit 0
        shift
        ;;
      status|start|restart|stop) sv "$1" "$2"; exit 0; shift ;;
      *) break ;;
    esac
    ;;
  list)
    printf "\033[34m"
    ls "${RUNIT_AVAILABLE_SERVICES}"
    printf "\033[0m"
    exit 0
    shift
    ;;
  enabled)
    if [ -n "$2" ] && [ "$2" != "list" ]; then
      # Cannot check a service that is not linked
      if [ ! -d "${RUNIT_DEFAULT_SERVICE_PATH}/$2" ]; then
        printf "\033[31merror\033[0m: Service not linked.\n"
        exit 1
      fi
      if [ -f "${RUNIT_DISABLED_SERVICE}" ]; then
        printf "\033[31merror\033[0m: Service not enabled.\n"
        exit 1
      fi
      printf "\033[32mrunit-service\033[0m: Service is enabled.\n"
      exit 0
    fi
    printf "\033[34m"
    for service in $(ls "${RUNIT_DEFAULT_SERVICE_PATH}"); do
      if [ ! -f "${RUNIT_DEFAULT_SERVICE_PATH}/$service/down" ]; then
        SERVICES="${SERVICES} $service"
      fi
    done
    printf "${SERVICES}\n"
    printf "\033[0m"
    shift
    ;;
  # TODO: Fix loaded function to display only services that are running.
  #printf "\tloaded  -  List the loaded services located at '/run/runit/service'.\n"
  #loaded)
  #  if [ -n "$2" ] && [ "$2" != "list" ]; then
  #    if [ ! -d "${RUNIT_LOADED_SERVICE_PATH}/$2" ]; then
  #      printf "\033[31merror\033[0m: Service not loaded.\n"
  #      exit 1
  #    fi
  #    printf "\033[32mrunit-service\033[0m: Service is loaded.\n"
  #    exit 0
  #  fi
  #  printf "\033[34m"
  #  ls "${RUNIT_LOADED_SERVICE_PATH}"
  #  printf "\033[0m"
  #  exit 0
  #  shift
  #  ;;
  *) break ;;
esac

