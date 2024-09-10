SIGNAL_CALLBACK void
on_browse_input_files_button_clicked(GtkWidget *widget)
{
  GtkWidget *combo = get_widget_checked("browse_format_combobox");
  GtkWidget *browse_select_colormap_optionmenu =
      get_widget_checked("browse_select_colormap_optionmenu");
  GtkWidget *browse_select_colormap_label =
      get_widget_checked("browse_select_colormap_label");
  GtkWidget *browse_select_image_data_type_optionmenu =
      get_widget_checked("browse_select_colormap_optionmenu");
  GtkWidget *browse_select_image_data_type_label =
      get_widget_checked("browse_select_colormap_label");
  GtkWindow *ancillary_dialog =
      GTK_WINDOW(get_widget_checked("add_file_with_ancillary_dialog"));
  GtkWindow *main_window =
      GTK_WINDOW(get_widget_checked("asf_convert"));
  int sel = gtk_combo_box_get_active(GTK_COMBO_BOX(combo));
  GtkWidget *ok_button =
    get_widget_checked("add_file_with_ancillary_ok_button");

  // open the "add with ancillary" if needed, otherwise we'll use the
  // normal 'open file' dialog
  if (sel==FORMAT_GAMMA || sel==FORMAT_POLSARPRO || sel==FORMAT_UAVSAR) {
    show_widget("hbox_polsarpro", sel==FORMAT_POLSARPRO);
    show_widget("hbox_gamma", sel==FORMAT_GAMMA);
    show_widget("vbox_uavsar", sel==FORMAT_UAVSAR);
    switch (sel) {
      case FORMAT_GAMMA:
        put_string_to_label("add_with_ancillary_format_label", "GAMMA");
        show_widget("hbox_gamma_description", TRUE);
        gtk_widget_set_sensitive(ok_button, TRUE);	
        break;
      case FORMAT_UAVSAR:
        put_string_to_label("add_with_ancillary_format_label", "UAVSAR");
        show_widget("hbox_gamma_description", FALSE);
        gtk_widget_set_sensitive(ok_button, FALSE);	
        break;
      case FORMAT_POLSARPRO:
        put_string_to_label("add_with_ancillary_format_label", "PolSARPro");
        show_widget("hbox_gamma_description", FALSE);
        gtk_widget_show(browse_select_colormap_optionmenu);
        gtk_widget_show(browse_select_colormap_label);
        gtk_widget_show(browse_select_image_data_type_optionmenu);
        gtk_widget_show(browse_select_image_data_type_label);
        gtk_widget_set_sensitive(ok_button, FALSE);	
        init_image_data_type_combobox();
        polsarpro_image_data_type_changed();
        break;
      default:
        put_string_to_label("add_with_ancillary_format_label", "Unknown");
        break;
    }
    gtk_window_set_transient_for(ancillary_dialog, main_window);
    gtk_widget_show(GTK_WIDGET(ancillary_dialog));
    return;
  }

  // normal case -- not requiring ancillary files

#ifdef win32
    OPENFILENAME of;
    int retval;
    char fname[1024];

    fname[0] = '\0';

    memset(&of, 0, sizeof(of));

#ifdef OPENFILENAME_SIZE_VERSION_400
    of.lStructSize = OPENFILENAME_SIZE_VERSION_400;
#else
    of.lStructSize = sizeof(of);
#endif

    of.hwndOwner = NULL;

    switch (sel) {
      case FORMAT_CEOS:
        of.lpstrFilter =
            "CEOS Level 1 Files\0*.L;LED-*;*.LEA;*.lea;LEA_*;lea_*;*.ldr;*.sarl\0"
            "RSAT/ERS CEOS L1 (*.L)\0*.L\0"
            "ALOS Files (LED-*)\0LED-*\0"
            "LEA Leader Files (LEA_*, lea_*, *.lea, *.LEA)\0LEA_*;lea_*;*.lea;*.LEA\0"
            "LDR Leader Files (*.ldr)\0*.ldr\0"
            "SARL Leader Files (*.sarl)\0*.sarl\0"
            "All Files\0*\0";
        break;

      case FORMAT_AIRSAR:
        of.lpstrFilter =
            "AirSAR Files (*.airsar)\0*.airsar\0"
            "All Files\0*\0";
        break;

      case FORMAT_UAVSAR:
        of.lpstrFilter =
            "UAVSAR Files (*.ann)\0*.ann\0"
            "All Files\0*\0";
        break;

      case FORMAT_TERRASARX:
        of.lpstrFilter =
            "TerraSAR-X Metadata Files (*.xml)\0*.xml\0"
            "All Files\0*\0";
        break;

      case FORMAT_RADARSAT2:
        of.lpstrFilter =
            "Radarsat-2 Metadata Files (*.xml)\0*.xml\0"
            "All Files\0*\0";
        break;

      case FORMAT_ROIPAC:
        of.lpstrFilter =
            "ROI_PAC Metadata Files (*.rsc)\0*.rsc\0"
            "All Files\0*\0";
        break;

      case FORMAT_ALOS_MOSAIC:
        of.lpstrFilter =
            "ALOS mosaic Metadata Files (*HDR.txt, *HDR.txt)\0*HDR.txt;*HDR\0"
            "All Files\0*\0";
        break;

      case FORMAT_GEOTIFF:
        of.lpstrFilter =
            "GeoTIFF Files (*.tif, *.tiff)\0*.tif;*.tiff\0"
            "All Files\0*\0";
        break;

      case FORMAT_ASF_INTERNAL:
        of.lpstrFilter =
            "ASF Internal Files (*.img)\0*.img\0"
            "All Files\0*\0";
        break;
    }

    of.lpstrCustomFilter = NULL;
    of.nFilterIndex = 1;
    of.lpstrFile = fname;
    of.nMaxFile = sizeof(fname);
    of.lpstrFileTitle = NULL;
    of.lpstrInitialDir = ".";
    of.lpstrTitle = "Select File";
    of.lpstrDefExt = NULL;
    of.Flags = OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_EXPLORER;

    retval = GetOpenFileName(&of);

    if (!retval) {
        if (CommDlgExtendedError())
            message_box("File dialog box error");
        return;
    }

    /* the returned "fname" has the following form:            */
    /*   <directory>\0<first file>\0<second file>\0<third ...  */
    char * dir = STRDUP(fname);
    char * p = fname + strlen(dir) + 1;

    if (*p) {
        while (*p) {
            char * dir_and_file =
                malloc(sizeof(char)*(strlen(dir)+strlen(p)+5));
            sprintf(dir_and_file, "%s%c%s", dir, DIR_SEPARATOR, p);
            add_to_files_list(dir_and_file);
            p += strlen(p) + 1;
            free(dir_and_file);
        }
    }
    else {
        add_to_files_list(dir);
    }

    free(dir);

#else // #ifdef win32

    /* Linux version -- use GtkFileChooser if possible */

#ifdef USE_GTK_FILE_CHOOSER

    if (GTK_IS_WIDGET(browse_widget))
      gtk_widget_destroy(browse_widget);
    create_file_chooser_dialog(sel);

    gtk_widget_show(browse_widget);

#else // #ifdef USE_GTK_FILE_CHOOSER

    GtkWidget *file_selection_dialog =
        get_widget_checked("input_file_selection");

    gtk_widget_show(file_selection_dialog);

#endif // #ifdef USE_GTK_FILE_CHOOSER
#endif // #ifdef win32
}