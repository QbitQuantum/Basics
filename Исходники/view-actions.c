void
view_actions_update (GimpActionGroup *group,
                     gpointer         data)
{
  GimpDisplay        *display        = action_data_get_display (data);
  GimpImage          *image          = NULL;
  GimpDisplayShell   *shell          = NULL;
  GimpDisplayOptions *options        = NULL;
  gchar              *label          = NULL;
  gboolean            fullscreen     = FALSE;
  gboolean            revert_enabled = FALSE;   /* able to revert zoom? */

  if (display)
    {
      GimpImageWindow *window;

      image  = gimp_display_get_image (display);
      shell  = gimp_display_get_shell (display);
      window = gimp_display_shell_get_window (shell);

      if (window)
        fullscreen = gimp_image_window_get_fullscreen (window);

      options = (image ?
                 (fullscreen ? shell->fullscreen_options : shell->options) :
                 shell->no_image_options);

      revert_enabled = gimp_display_shell_scale_can_revert (shell);
    }

#define SET_ACTIVE(action,condition) \
        gimp_action_group_set_action_active (group, action, (condition) != 0)
#define SET_SENSITIVE(action,condition) \
        gimp_action_group_set_action_sensitive (group, action, (condition) != 0)
#define SET_COLOR(action,color) \
        gimp_action_group_set_action_color (group, action, color, FALSE)

  SET_SENSITIVE ("view-new",   image);
  SET_SENSITIVE ("view-close", image);

  SET_SENSITIVE ("view-dot-for-dot", image);
  SET_ACTIVE    ("view-dot-for-dot", display && shell->dot_for_dot);

  SET_SENSITIVE ("view-zoom-revert", revert_enabled);
  if (revert_enabled)
    {
      label = g_strdup_printf (_("Re_vert Zoom (%d%%)"),
                               ROUND (shell->last_scale * 100));
      gimp_action_group_set_action_label (group, "view-zoom-revert", label);
      g_free (label);
    }
  else
    {
      gimp_action_group_set_action_label (group, "view-zoom-revert",
                                          _("Re_vert Zoom"));
    }

  SET_SENSITIVE ("view-zoom-out",    image);
  SET_SENSITIVE ("view-zoom-in",     image);
  SET_SENSITIVE ("view-zoom-fit-in", image);
  SET_SENSITIVE ("view-zoom-fill",   image);

  SET_SENSITIVE ("view-zoom-16-1",  image);
  SET_SENSITIVE ("view-zoom-8-1",   image);
  SET_SENSITIVE ("view-zoom-4-1",   image);
  SET_SENSITIVE ("view-zoom-2-1",   image);
  SET_SENSITIVE ("view-zoom-1-1",   image);
  SET_SENSITIVE ("view-zoom-1-2",   image);
  SET_SENSITIVE ("view-zoom-1-4",   image);
  SET_SENSITIVE ("view-zoom-1-8",   image);
  SET_SENSITIVE ("view-zoom-1-16",  image);
  SET_SENSITIVE ("view-zoom-other", image);

  SET_SENSITIVE ("view-rotate-reset", image);
  SET_SENSITIVE ("view-rotate-90",    image);
  SET_SENSITIVE ("view-rotate-180",   image);
  SET_SENSITIVE ("view-rotate-270",   image);
  SET_SENSITIVE ("view-rotate-other", image);

  if (image)
    {
      view_actions_set_zoom (group, shell);
      view_actions_set_rotate (group, shell);
    }

  SET_SENSITIVE ("view-navigation-window", image);
  SET_SENSITIVE ("view-display-filters",   image);

  SET_SENSITIVE ("view-show-selection",      image);
  SET_ACTIVE    ("view-show-selection",      display && options->show_selection);
  SET_SENSITIVE ("view-show-layer-boundary", image);
  SET_ACTIVE    ("view-show-layer-boundary", display && options->show_layer_boundary);
  SET_SENSITIVE ("view-show-guides",         image);
  SET_ACTIVE    ("view-show-guides",         display && options->show_guides);
  SET_SENSITIVE ("view-show-grid",           image);
  SET_ACTIVE    ("view-show-grid",           display && options->show_grid);
  SET_SENSITIVE ("view-show-sample-points",  image);
  SET_ACTIVE    ("view-show-sample-points",  display && options->show_sample_points);

  SET_SENSITIVE ("view-snap-to-guides",      image);
  SET_ACTIVE    ("view-snap-to-guides",      display && options->snap_to_guides);
  SET_SENSITIVE ("view-snap-to-grid",        image);
  SET_ACTIVE    ("view-snap-to-grid",        display && options->snap_to_grid);
  SET_SENSITIVE ("view-snap-to-canvas",      image);
  SET_ACTIVE    ("view-snap-to-canvas",      display && options->snap_to_canvas);
  SET_SENSITIVE ("view-snap-to-vectors",     image);
  SET_ACTIVE    ("view-snap-to-vectors",     display && options->snap_to_path);

  SET_SENSITIVE ("view-padding-color-theme",       image);
  SET_SENSITIVE ("view-padding-color-light-check", image);
  SET_SENSITIVE ("view-padding-color-dark-check",  image);
  SET_SENSITIVE ("view-padding-color-custom",      image);
  SET_SENSITIVE ("view-padding-color-prefs",       image);

  if (display)
    {
      SET_COLOR ("view-padding-color-menu", &options->padding_color);

      if (shell->canvas)
        {
          GtkStyle *style = gtk_widget_get_style (shell->canvas);
          GimpRGB   color;

          gtk_widget_ensure_style (shell->canvas);
          gimp_rgb_set_gdk_color (&color, style->bg + GTK_STATE_NORMAL);
          gimp_rgb_set_alpha (&color, GIMP_OPACITY_OPAQUE);

          SET_COLOR ("view-padding-color-theme",  &color);
        }
    }

  SET_SENSITIVE ("view-show-menubar",    image);
  SET_ACTIVE    ("view-show-menubar",    display && options->show_menubar);
  SET_SENSITIVE ("view-show-rulers",     image);
  SET_ACTIVE    ("view-show-rulers",     display && options->show_rulers);
  SET_SENSITIVE ("view-show-scrollbars", image);
  SET_ACTIVE    ("view-show-scrollbars", display && options->show_scrollbars);
  SET_SENSITIVE ("view-show-statusbar",  image);
  SET_ACTIVE    ("view-show-statusbar",  display && options->show_statusbar);

  SET_SENSITIVE ("view-shrink-wrap", image);
  SET_ACTIVE    ("view-fullscreen",  display && fullscreen);

  if (GIMP_IS_IMAGE_WINDOW (group->user_data) ||
      GIMP_IS_GIMP (group->user_data))
    {
      GtkWidget *window = NULL;

      if (shell)
        window = gtk_widget_get_toplevel (GTK_WIDGET (shell));

      /*  see view_actions_setup()  */
      if (GTK_IS_WINDOW (window))
        window_actions_update (group, window);
    }

#undef SET_ACTIVE
#undef SET_SENSITIVE
#undef SET_COLOR
}