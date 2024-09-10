// Populate both the drop-down on the import tab and within the file browse dialog
void populate_polsarpro_classification_optionmenu()
{
  // Set up the menus (one on the import tab, the other on the input file browse dialog
  GtkWidget *browse_menu = NULL;
  GtkWidget *browse_option_menu = get_widget_checked("browse_select_colormap_optionmenu");
  if (browse_option_menu) {
    browse_menu = gtk_option_menu_get_menu(GTK_OPTION_MENU(browse_option_menu));
    if (browse_menu) {
      gtk_option_menu_remove_menu(GTK_OPTION_MENU(browse_option_menu));
    }
  }
  browse_menu = gtk_menu_new();

  GtkWidget *browse_item = gtk_menu_item_new_with_label("None");
  gtk_menu_append(GTK_MENU(browse_menu), browse_item);
  gtk_widget_show(browse_item);

  browse_item = gtk_separator_menu_item_new();
  gtk_menu_append(GTK_MENU(browse_menu), browse_item);
  gtk_widget_show(browse_item);

  char lut_loc[1024];
  sprintf(lut_loc, "%s%clook_up_tables", get_asf_share_dir(), DIR_SEPARATOR);
  if (g_polsarpro_classification_optionmenu_ht == NULL) {
    g_polsarpro_classification_optionmenu_ht = g_hash_table_new(g_str_hash,g_str_equal);
  }

  // Open up the share dir's look up tables list, populate dropdown
  // from the files in that directory.
  GDir *lut_dir = g_dir_open(lut_loc, 0, NULL);
  if (lut_dir) {
    unsigned int i, n=0;
    char **names = (char**)MALLOC(sizeof(char*)*MAX_LUTS);

    while (1) {
      const char *name = (char*)g_dir_read_name(lut_dir);
      if (name) {
        char *name_dup = STRDUP(name);
        char *p = findExt(name_dup);
        if (p && strcmp(p, ".pal") == 0 && is_jasc_palette_lut(name)) {
          *p = '\0'; // don't show ".pal" extension in menu
          names[n++] = name_dup;
          // quit when we get too many
          if (n > MAX_LUTS)
            break;
        }
      } else
        break;
    }
    g_dir_close(lut_dir);

    // alphabetize
    qsort(names, n, sizeof(char*), my_strcmp);

    // now populate the menus
    for (i=0; i<n; ++i) {
      browse_item = gtk_menu_item_new_with_label(names[i]);
      g_object_set_data(G_OBJECT(browse_item), "file", (gpointer)names[i]);
      g_object_set_data(G_OBJECT(browse_item), "index", GUINT_TO_POINTER(i+2));
      gtk_menu_append(GTK_MENU(browse_menu), browse_item);
      gtk_widget_show(browse_item);
      g_hash_table_insert(g_polsarpro_classification_optionmenu_ht,
                          (gpointer)g_strdup(names[i]),
                           GUINT_TO_POINTER(i+2));
    }
  }

  browse_option_menu = get_widget_checked("browse_select_colormap_optionmenu");

  gtk_option_menu_set_menu(GTK_OPTION_MENU(browse_option_menu), browse_menu);
  gtk_option_menu_set_history(GTK_OPTION_MENU(browse_option_menu), 0);

  gtk_widget_show(browse_menu);
  gtk_widget_show(browse_option_menu);
}