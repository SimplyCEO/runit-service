runit-service
=============

A custom tool to manage runit services.<br>
The main goal is to provide a `systemctl` like command to easily manage complex commands.

Usage
-----

In most cases `runit-service <mode> <service>` can be used.<br>
Only when using `list`, `<service>` can be empty. `enabled` too, but it accepts a value.

Available modes:

- list: List the services located at '/etc/runit/sv'.
- link: Link the service from '/etc/runit/sv' to '/etc/runit/runsvdir/default'.
- enabled: List the enabled services located at '/etc/runit/runsvdir/default'.
- disable: Disable a service from activating at boot.
- enable: Enable a service activation after boot.
- status: Display the service information.
- start: Start the service.
- restart: Stop and start the service.
- stop: Stop the service.

Installation
------------

Give yourself `root` privileges and run these instructions.

Set mode to `rwxr-xr-x` or `0755`:
```shell
chmod 0755 runit-service.sh
```

Move it to a `bin` folder. Preferably along runit scripts:
```shell
mv runit-service.sh /usr/bin/runit-service
```

