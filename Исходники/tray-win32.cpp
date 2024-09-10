static void cb_popup_state(GtkStatusIcon *status_icon, guint button, guint activate_time, gpointer user_data)
{
  switch (button) {

    case 1:
#if UNIX
      toggle_im_enabled();
      break;
    case 2:
#endif
      kbm_toggle();
      break;
    case 3:
    {
      char bak[512], cur[512];
      get_gcin_conf_fstr(PHONETIC_KEYBOARD, cur, "");
      get_gcin_conf_fstr(PHONETIC_KEYBOARD_BAK, bak, "");
      if (bak[0] && strcmp(bak, cur)) {
        char kbm[512];

        strcpy(kbm, bak);
        char *p=strchr(kbm, ' ');

        if (p) {
          *(p++)=0;
          int i;
          for(i=0;kbm_sel[i].name;i++)
            if (!strcmp(kbm_sel[i].kbm, kbm)) {
              break;
            }

          if (kbm_sel[i].kbm) {
            unich_t tt[128];
            if (mitems_state[0].name)
              free(mitems_state[0].name);
#if UNIX
            sprintf(tt, "注音換 %s %s", kbm_sel[i].name, p);
            mitems_state[0].name = strdup(tt);
#else
            swprintf(tt, L"注音換 %s %S", kbm_sel[i].name, p);
            mitems_state[0].name = wcsdup(tt);
#endif
          }
        }

//        dbg("hhhhhhhhhhhh %x\n", tray_menu_state);
        if (tray_menu_state) {
          gtk_widget_destroy(tray_menu_state);
          tray_menu_state = NULL;
        }
      }

      if (!tray_menu_state)
        tray_menu_state = create_tray_menu(mitems_state);

      gtk_menu_popup(GTK_MENU(tray_menu_state), NULL, NULL, NULL, NULL, button, activate_time);
      break;
    }
  }

//  dbg("zzzzzzzzzzzzz\n");
}