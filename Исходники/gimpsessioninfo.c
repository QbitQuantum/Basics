/**
 * gimp_session_info_apply_geometry:
 * @info:
 * @screen:
 * @current_monitor:
 *
 * Apply the geometry stored in the session info object to the
 * associated widget.
 **/
void
gimp_session_info_apply_geometry (GimpSessionInfo *info,
                                  GdkScreen       *screen,
                                  gint             current_monitor,
                                  gboolean         apply_stored_monitor)
{
  GdkRectangle rect;
  GdkRectangle work_rect;
  gchar        geom[32];
  gint         monitor;
  gint         width;
  gint         height;

  g_return_if_fail (GIMP_IS_SESSION_INFO (info));
  g_return_if_fail (GTK_IS_WINDOW (info->p->widget));
  g_return_if_fail (GDK_IS_SCREEN (screen));

  monitor = current_monitor;

  if (apply_stored_monitor)
    {
      gint n_monitors;

      n_monitors = gdk_screen_get_n_monitors (screen);

      if (info->p->monitor != DEFAULT_MONITOR &&
          info->p->monitor < n_monitors)
        {
          monitor = info->p->monitor;
        }
      else
        {
          monitor = gdk_screen_get_primary_monitor (screen);
        }
    }

  gdk_screen_get_monitor_geometry (screen, monitor, &rect);
  gdk_screen_get_monitor_workarea (screen, monitor, &work_rect);

  info->p->x += rect.x;
  info->p->y += rect.y;

  if (gimp_session_info_get_remember_size (info) &&
      info->p->width  > 0 &&
      info->p->height > 0)
    {
      width  = info->p->width;
      height = info->p->height;
    }
  else
    {
      GtkRequisition requisition;

      gtk_widget_size_request (info->p->widget, &requisition);

      width  = requisition.width;
      height = requisition.height;
    }

  info->p->x = CLAMP (info->p->x,
                      work_rect.x,
                      work_rect.x + work_rect.width  - width);
  info->p->y = CLAMP (info->p->y,
                      work_rect.y,
                      work_rect.y + work_rect.height - height);

  if (info->p->right_align && info->p->bottom_align)
    {
      g_strlcpy (geom, "-0-0", sizeof (geom));
    }
  else if (info->p->right_align)
    {
      g_snprintf (geom, sizeof (geom), "-0%+d", info->p->y);
    }
  else if (info->p->bottom_align)
    {
      g_snprintf (geom, sizeof (geom), "%+d-0", info->p->x);
    }
  else
    {
      g_snprintf (geom, sizeof (geom), "%+d%+d", info->p->x, info->p->y);
    }

  gtk_window_parse_geometry (GTK_WINDOW (info->p->widget), geom);

  if (gimp_session_info_get_remember_size (info) &&
      info->p->width  > 0 &&
      info->p->height > 0)
    {
      gtk_window_set_default_size (GTK_WINDOW (info->p->widget),
                                   info->p->width, info->p->height);
    }

  /*  Window managers and windowing systems suck. They have their own
   *  ideas about WM standards and when it's appropriate to honor
   *  user/application-set window positions and when not. Therefore,
   *  use brute force and "manually" position dialogs whenever they
   *  are shown. This is important especially for transient dialogs,
   *  because window managers behave even "smarter" then...
   */
  if (GTK_IS_DIALOG (info->p->widget))
    g_signal_connect (info->p->widget, "show",
                      G_CALLBACK (gimp_session_info_dialog_show),
                      info);
}