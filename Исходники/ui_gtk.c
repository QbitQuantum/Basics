static bool_t title_change_cb (void)
{
    if (delayed_title_change_source)
    {
        g_source_remove (delayed_title_change_source);
        delayed_title_change_source = 0;
    }

    if (aud_drct_get_playing ())
    {
        if (aud_drct_get_ready ())
        {
            char * title = aud_drct_get_title ();
            SPRINTF (title_s, _("%s - Audacious"), title);
            gtk_window_set_title ((GtkWindow *) window, title_s);
            str_unref (title);
        }
        else
            gtk_window_set_title ((GtkWindow *) window, _("Buffering ..."));
    }
    else
        gtk_window_set_title ((GtkWindow *) window, _("Audacious"));

    return FALSE;
}