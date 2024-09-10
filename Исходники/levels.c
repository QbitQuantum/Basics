static gboolean dt_iop_levels_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer user_data)
{
  dt_iop_module_t *self = (dt_iop_module_t *)user_data;
  dt_iop_levels_gui_data_t *c = (dt_iop_levels_gui_data_t *)self->gui_data;
  dt_iop_levels_params_t *p = (dt_iop_levels_params_t *)self->params;
  const int inset = DT_GUI_CURVE_EDITOR_INSET;
  int height = widget->allocation.height - 2*inset, width = widget->allocation.width - 2*inset;
  if(!c->dragging)
  {
    c->mouse_x = CLAMP(event->x - inset, 0, width);
    c->drag_start_percentage = (p->levels[1] - p->levels[0])
                               / (p->levels[2] - p->levels[0]);
  }
  c->mouse_y = CLAMP(event->y - inset, 0, height);

  if(c->dragging)
  {
    if(c->handle_move >= 0 && c->handle_move < 3)
    {
      const float mx = (CLAMP(event->x - inset, 0, width)) / (float)width;

      float min_x = 0;
      float max_x = 1;

      // Determining the minimum and maximum bounds for the drag handles
      switch(c->handle_move)
      {
      case 0:
        max_x = fminf(p->levels[2] - (0.05 / c->drag_start_percentage),
                      1);
        max_x = fminf((p->levels[2] * (1 - c->drag_start_percentage) - 0.05)
                      / (1 - c->drag_start_percentage),
                      max_x);
        break;

      case 1:
        min_x = p->levels[0] + 0.05;
        max_x = p->levels[2] - 0.05;
        break;

      case 2:
        min_x = fmaxf((0.05 / c->drag_start_percentage) + p->levels[0],
                      0);
        min_x = fmaxf((p->levels[0] * (1 - c->drag_start_percentage) + 0.05)
                      / (1 - c->drag_start_percentage),
                      min_x);
        break;
      }

      p->levels[c->handle_move] =
          fminf(max_x, fmaxf(min_x, mx));

      if(c->handle_move != 1)
        p->levels[1] = p->levels[0] + (c->drag_start_percentage
                                       * (p->levels[2] - p->levels[0]));
    }
    dt_dev_add_history_item(darktable.develop, self, TRUE);
  }
  else
  {
    c->handle_move = 0;
    const float mx = CLAMP(event->x - inset, 0, width)/(float)width;
    float dist = fabsf(p->levels[0] - mx);
    for(int k=1; k<3; k++)
    {
      float d2 = fabsf(p->levels[k] - mx);
      if(d2 < dist)
      {
        c->handle_move = k;
        dist = d2;
      }
    }
  }
  gtk_widget_queue_draw(widget);

  gint x, y;
  gdk_window_get_pointer(event->window, &x, &y, NULL);
  return TRUE;
}