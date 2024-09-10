EXPORT void audgui_jump_to_time (void)
{
    if (audgui_reshow_unique_window (AUDGUI_JUMP_TO_TIME_WINDOW))
        return;

    GtkWidget * entry = gtk_entry_new ();
    gtk_entry_set_activates_default ((GtkEntry *) entry, TRUE);

    GtkWidget * button1 = audgui_button_new (_("Jump"), "go-jump", jump_cb, entry);
    GtkWidget * button2 = audgui_button_new (_("Cancel"), "process-stop", NULL, NULL);

    GtkWidget * dialog = audgui_dialog_new (GTK_MESSAGE_OTHER,
     _("Jump to Time"), _("Enter time (minutes:seconds):"), button1, button2);

    audgui_dialog_add_widget (dialog, entry);

    if (aud_drct_get_playing ())
    {
        int time = aud_drct_get_time () / 1000;
        SPRINTF (buf, "%u:%02u", time / 60, time % 60);
        gtk_entry_set_text ((GtkEntry *) entry, buf);
    }

    audgui_show_unique_window (AUDGUI_JUMP_TO_TIME_WINDOW, dialog);
}