/* some rather complex logic here.  If the user clicks without modifiers,
 * then we start a new list, and use the first object in it as reference.
 * If the user clicks using Shift, or draws a rubber-band box, then
 * we add objects to the list, but do not specify which one should
 * be used as reference.
 */
static void
gimp_align_tool_button_release (GimpTool              *tool,
                                const GimpCoords      *coords,
                                guint32                time,
                                GdkModifierType        state,
                                GimpButtonReleaseType  release_type,
                                GimpDisplay           *display)
{
  GimpAlignTool    *align_tool = GIMP_ALIGN_TOOL (tool);
  GimpAlignOptions *options    = GIMP_ALIGN_TOOL_GET_OPTIONS (tool);
  GimpDisplayShell *shell      = gimp_display_get_shell (display);
  GObject          *object     = NULL;
  GimpImage        *image      = gimp_display_get_image (display);
  GdkModifierType   extend_mask;
  gint              i;

  extend_mask = gimp_get_extend_selection_mask ();

  gimp_draw_tool_pause (GIMP_DRAW_TOOL (tool));

  gimp_tool_control_halt (tool->control);

  if (release_type == GIMP_BUTTON_RELEASE_CANCEL)
    {
      align_tool->x2 = align_tool->x1;
      align_tool->y2 = align_tool->y1;

      gimp_draw_tool_resume (GIMP_DRAW_TOOL (tool));
      return;
    }

  if (! (state & extend_mask)) /* start a new list */
    {
      gimp_align_tool_clear_selected (align_tool);
      align_tool->set_reference = FALSE;
    }

  /* if mouse has moved less than EPSILON pixels since button press,
   * select the nearest thing, otherwise make a rubber-band rectangle
   */
  if (hypot (coords->x - align_tool->x1,
             coords->y - align_tool->y1) < EPSILON)
    {
      GimpVectors *vectors;
      GimpGuide   *guide;
      GimpLayer   *layer;
      gint         snap_distance = display->config->snap_distance;

      if (gimp_draw_tool_on_vectors (GIMP_DRAW_TOOL (tool), display,
                                     coords, snap_distance, snap_distance,
                                     NULL, NULL, NULL, NULL, NULL,
                                     &vectors))
        {
          object = G_OBJECT (vectors);
        }
      else if (gimp_display_shell_get_show_guides (shell) &&
               (guide = gimp_image_find_guide (image,
                                               coords->x, coords->y,
                                               FUNSCALEX (shell, snap_distance),
                                               FUNSCALEY (shell, snap_distance))))
        {
          object = G_OBJECT (guide);
        }
      else
        {
          if ((layer = gimp_image_pick_layer_by_bounds (image,
                                                        coords->x, coords->y)))
            {
              object = G_OBJECT (layer);
            }
        }

      if (object)
        {
          if (! g_list_find (align_tool->selected_objects, object))
            {
              align_tool->selected_objects =
                g_list_append (align_tool->selected_objects, object);

              g_signal_connect (object, "removed",
                                G_CALLBACK (gimp_align_tool_object_removed),
                                align_tool);

              /* if an object has been selected using unmodified click,
               * it should be used as the reference
               */
              if (! (state & extend_mask))
                align_tool->set_reference = TRUE;
            }
        }
    }
  else  /* FIXME: look for vectors too */
    {
      gint   X0 = MIN (coords->x, align_tool->x1);
      gint   X1 = MAX (coords->x, align_tool->x1);
      gint   Y0 = MIN (coords->y, align_tool->y1);
      gint   Y1 = MAX (coords->y, align_tool->y1);
      GList *all_layers;
      GList *list;

      all_layers = gimp_image_get_layer_list (image);

      for (list = all_layers; list; list = g_list_next (list))
        {
          GimpLayer *layer = list->data;
          gint       x0, y0, x1, y1;

          if (! gimp_item_get_visible (GIMP_ITEM (layer)))
            continue;

          gimp_item_get_offset (GIMP_ITEM (layer), &x0, &y0);
          x1 = x0 + gimp_item_get_width  (GIMP_ITEM (layer));
          y1 = y0 + gimp_item_get_height (GIMP_ITEM (layer));

          if (x0 < X0 || y0 < Y0 || x1 > X1 || y1 > Y1)
            continue;

          if (g_list_find (align_tool->selected_objects, layer))
            continue;

          align_tool->selected_objects =
            g_list_append (align_tool->selected_objects, layer);

          g_signal_connect (layer, "removed",
                            G_CALLBACK (gimp_align_tool_object_removed),
                            align_tool);
        }

      g_list_free (all_layers);
    }

  for (i = 0; i < ALIGN_OPTIONS_N_BUTTONS; i++)
    {
      if (options->button[i])
        gtk_widget_set_sensitive (options->button[i],
                                  align_tool->selected_objects != NULL);
    }

  align_tool->x2 = align_tool->x1;
  align_tool->y2 = align_tool->y1;

  gimp_draw_tool_resume (GIMP_DRAW_TOOL (tool));
}