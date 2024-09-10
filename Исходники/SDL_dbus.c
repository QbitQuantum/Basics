void
SDL_DBus_Quit(void)
{
    if (dbus.system_conn) {
        dbus.connection_close(dbus.system_conn);
        dbus.connection_unref(dbus.system_conn);
    }
    if (dbus.session_conn) {
        dbus.connection_close(dbus.session_conn);
        dbus.connection_unref(dbus.session_conn);
    }
/* Don't do this - bug 3950
   dbus_shutdown() is a debug feature which closes all global resources in the dbus library. Calling this should be done by the app, not a library, because if there are multiple users of dbus in the process then SDL could shut it down even though another part is using it.
*/
#if 0
    if (dbus.shutdown) {
        dbus.shutdown();
    }
#endif
    SDL_zero(dbus);
    UnloadDBUSLibrary();
}