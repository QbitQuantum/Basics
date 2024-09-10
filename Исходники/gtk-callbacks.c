void my_float_listener (PluginParam *param) {
  GtkProgressBar *progress;

  if (sdlGoom->config_win == 0) return;
  progress = GTK_PROGRESS_BAR(param->user_data);

  if (progress) {
    if (FVAL(*param)<FMIN(*param))
      FVAL(*param) = FMIN(*param);
    if (FVAL(*param)>FMAX(*param))
      FVAL(*param) = FMAX(*param);
    gtk_progress_bar_update (progress, FVAL(*param));
  }
}