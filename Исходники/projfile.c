static GtkWidget * populate_predefined_projections(int projection)
{
    gchar * proj_dir=NULL;
    GDir * dir;
    GtkWidget * m;
    GtkWidget * item;

    m = gtk_menu_new();

    item = gtk_menu_item_new_with_label("User Defined");
    gtk_menu_append(GTK_MENU(m), item);
    gtk_widget_show(item);

    item = gtk_separator_menu_item_new();
    gtk_menu_append(GTK_MENU(m), item);
    gtk_widget_show(item);

    // do not populate the predefined projections for UTM -- too many,
    // the large dropdownlist causes crashes on windows. Also, no
    // predefined projections for the lat/lon psuedoprojection
    if (projection != PROJ_UTM && projection != PROJ_LATLON) {
      proj_dir = projection_directory(projection);
      if (proj_dir)
      {
        dir = g_dir_open(proj_dir, 0, NULL);
        
        if (dir)
        {
          int i, n;
          char *names[512];
          
          n = 0;
          while (TRUE)
          {
            const char * name;
            
            name = (char*) g_dir_read_name(dir);
            
            if (name)
            {
              char * name_dup;
              char * p;
              
              name_dup = STRDUP(name);
              p = strrchr(name_dup, '.');
              
              if (p && strcmp(p, ".proj") == 0)
              {
                *p = '\0';
                
                names[n] = name_dup;
                ++n;
                
                if (n >= sizeof(names)/sizeof(names[0]))
                  break;
              }
            }
            else
            {
              break;
            }
          }
          
          g_dir_close(dir);
          
          qsort(names, n, sizeof(char *), my_strcmp);
          for (i = 0; i < n; ++i)
          {
            item = gtk_menu_item_new_with_label(
              fudge_the_name(projection, names[i]));
            
            g_object_set_data(G_OBJECT(item),
                              "file", (gpointer)names[i]);
            
            gtk_menu_append(GTK_MENU(m), item);
            gtk_widget_show(item);
          }
        }
      }
    }

    if (proj_dir)
      g_free(proj_dir);

    return m;
}