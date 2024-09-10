void
ServerApp::_LaunchAddOnServer()
{
    // Try to launch media_addon_server by mime signature.
    // If it fails (for example on the Live CD, where the executable
    // hasn't yet been mimesetted), try from this application's
    // directory
    status_t err = be_roster->Launch(B_MEDIA_ADDON_SERVER_SIGNATURE);
    if (err == B_OK)
        return;

    app_info info;
    BEntry entry;
    BDirectory dir;
    entry_ref ref;

    err = GetAppInfo(&info);
    err |= entry.SetTo(&info.ref);
    err |= entry.GetParent(&entry);
    err |= dir.SetTo(&entry);
    err |= entry.SetTo(&dir, "media_addon_server");
    err |= entry.GetRef(&ref);

    if (err == B_OK)
        be_roster->Launch(&ref);
    if (err == B_OK)
        return;

    (new BAlert("media_server", "Launching media_addon_server failed.\n\n"
                "media_server will terminate", "OK"))->Go();
    fprintf(stderr, "Launching media_addon_server (%s) failed: %s\n",
            B_MEDIA_ADDON_SERVER_SIGNATURE, strerror(err));
    exit(1);
}