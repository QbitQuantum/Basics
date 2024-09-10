static void
on_fork(void *data)
{
    unsigned i;

    static const char *daemon_possible_paths[] = {
        "/usr/libexec/bluetooth/bluetoothd", // fedora/yocto-style
        "/usr/lib/bluetooth/bluetoothd", // arch-style
        "/usr/sbin/bluetoothd" // debian-style
    };

    const char *argv[] = {
        NULL, // waiting to be set
        "--nodetach",
        NULL
    };

    static const char *envp[] = {
        "BLUETOOTH_SYSTEM_BUS_ADDRESS=unix:path=/run/dbus/system_bus_socket",
        NULL
    };

    for (i = 0; i < SOL_UTIL_ARRAY_SIZE(daemon_possible_paths); i++) {
        argv[0] = daemon_possible_paths[i];
        SOL_INF("attempting to exec %s", daemon_possible_paths[i]);
        execvpe(argv[0], (char *const *)argv, (char *const *)envp);
    }

    SOL_INF("bluetooth daemon executable not found, aborting");
    sol_platform_linux_fork_run_exit(EXIT_FAILURE);
}