char *CGTKBase::GetPassword(const char *str)
{
    const int windoww = 400;
    
    GtkWidget *dialog = gtk_dialog_new_with_buttons(GetTranslation("Password dialog"), NULL, GTK_DIALOG_MODAL,
                                                    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OK, GTK_RESPONSE_OK,
                                                    NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog), windoww, -1);
    
    GtkWidget *label = gtk_label_new(str);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), label, TRUE, TRUE, 15);
    gtk_widget_show(label);

    GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
    
    GtkWidget *input = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(input), FALSE);
    gtk_box_pack_end(GTK_BOX(hbox), input, TRUE, TRUE, 15);
    gtk_widget_show(input);
    
    gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), hbox);
    gtk_widget_show(hbox);
    
    gint dialogret = gtk_dialog_run(GTK_DIALOG(dialog));
    char *ret = (dialogret == GTK_RESPONSE_OK) ? StrDup(gtk_entry_get_text(GTK_ENTRY(input))) : NULL;
    
    gtk_widget_destroy(dialog);

    return ret;
}