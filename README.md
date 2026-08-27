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
- purge: Will stop, unlink, and remove the service permanently.
- journal: Listen kernel logs.

Installation
------------

- C:

Compile the code:
```sh
make BUILD_TYPE=Release
```

Give yourself `root` privileges.

Install the binary and the service on system:
```sh
make INSTALL_PREFIX=/usr install
```

Start `runit-journal` service:
```sh
runit-service link runit-journal
runit-service enable runit-journal
runit-service start runit-journal
```

- Shell script:

Give yourself `root` privileges and run these instructions.

Set mode to `rwxr-xr-x` or `0755`:
```sh
chmod 0755 runit-service.sh
```

Move it to a `bin` folder. Preferably along runit scripts:
```sh
cp runit-service.sh /usr/bin/runit-service
```

