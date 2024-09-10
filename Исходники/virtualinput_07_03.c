void window_insert(struttura *str)
{ 
  GtkWidget *winDialog,*button1,*button2,*label;
  GtkDialog *dialog;
  char slabel[LEN_WORD_DB+16];
  

  gtk_widget_hide(str->window);
  winDialog = gtk_dialog_new();
  dialog=GTK_DIALOG(winDialog);
  gtk_window_set_title(GTK_WINDOW(winDialog), "new word?");
  
  button1=gtk_dialog_add_button(dialog,"cancel",0);
 
  button2=gtk_dialog_add_button(dialog,"insert",1);

  snprintf(slabel,LEN_WORD_DB+16,"insert '%s' in db?",intToChar(str->ins.new_word));
  label = gtk_label_new (slabel);
  gtk_box_pack_start (GTK_BOX(gtk_dialog_get_content_area(dialog)),label, TRUE, TRUE, 0);
  
  gtk_widget_show (label);
  
  g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK (gtk_widget_destroy), winDialog);
  g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(button_pressed_insert), str);  
  
  g_signal_connect_swapped (winDialog, "destroy",
                              G_CALLBACK (gtk_widget_destroy), 
                              winDialog);
  gtk_dialog_run(dialog);
  setMove(str,str->window);
  gtk_widget_show(str->window);
  gtk_widget_destroy(winDialog);
  ins(str);
}