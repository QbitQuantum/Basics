static void confirm_delete (void)
{
    int playlist = aud_playlist_get_active ();
    int entry_count = aud_playlist_entry_count (playlist);

    for (int i = 0; i < entry_count; i ++)
    {
        if (! aud_playlist_entry_get_selected (playlist, i))
            continue;

        char * uri = aud_playlist_entry_get_filename (playlist, i);
        char * filename = uri_to_filename (uri);

        if (filename)
        {
            if (aud_get_bool ("delete_files", "use_trash"))
                move_to_trash (filename);
            else
                really_delete (filename);

            str_unref (filename);
        }
        else
        {
            SPRINTF (error, _("Error deleting %s: not a local file."), uri);
            aud_interface_show_error (error);
        }

        str_unref (uri);
    }

    aud_playlist_delete_selected (playlist);
}