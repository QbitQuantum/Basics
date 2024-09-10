/*
 * This function is called if the user clicks and releases the left
 * button without moving it.  There are the things we might want
 * to do here:
 * 1) If there is an existing rectangle and we are inside it, we
 *    convert it into a selection.
 * 2) If there is an existing rectangle and we are outside it, we
 *    clear it.
 * 3) If there is no rectangle and there is a floating selection,
 *    we anchor it.
 * 4) If there is no rectangle and we are inside the selection, we
 *    create a rectangle from the selection bounds.
 * 5) If there is no rectangle and we are outside the selection,
 *    we clear the selection.
 */
static gboolean
gimp_rectangle_select_tool_execute (GimpRectangleTool *rectangle,
                                    gint               x,
                                    gint               y,
                                    gint               w,
                                    gint               h)
{
  GimpTool                       *tool = GIMP_TOOL (rectangle);
  GimpRectangleSelectTool        *rect_sel_tool;
  GimpRectangleSelectToolPrivate *priv;

  rect_sel_tool = GIMP_RECTANGLE_SELECT_TOOL (rectangle);
  priv          = GIMP_RECTANGLE_SELECT_TOOL_GET_PRIVATE (rect_sel_tool);

  if (w == 0 && h == 0 && tool->display != NULL)
    {
      GimpImage   *image     = gimp_display_get_image (tool->display);
      GimpChannel *selection = gimp_image_get_mask (image);
      gint         pressx;
      gint         pressy;

      if (gimp_image_get_floating_selection (image))
        {
          floating_sel_anchor (gimp_image_get_floating_selection (image));
          gimp_image_flush (image);
          return TRUE;
        }

      pressx = ROUND (priv->press_x);
      pressy = ROUND (priv->press_y);

      /*  if the click was inside the marching ants  */
      if (gimp_pickable_get_opacity_at (GIMP_PICKABLE (selection),
                                        pressx, pressy) > 0.5)
        {
          gint x, y, w, h;

          if (gimp_item_bounds (GIMP_ITEM (selection), &x, &y, &w, &h))
            {
              g_object_set (rectangle,
                            "x1", x,
                            "y1", y,
                            "x2", x + w,
                            "y2", y + h,
                            NULL);
            }

          gimp_rectangle_tool_set_function (rectangle,
                                            GIMP_RECTANGLE_TOOL_MOVING);
          gimp_rectangle_select_tool_update_option_defaults (rect_sel_tool,
                                                             FALSE);

          return FALSE;
        }
      else
        {
          GimpTool       *tool = GIMP_TOOL (rectangle);
          GimpChannelOps  operation;

          /* prevent this change from halting the tool */
          gimp_tool_control_push_preserve (tool->control, TRUE);

          /* We can conceptually think of a click outside of the
           * selection as adding a 0px selection. Behave intuitivly
           * for the current selection mode
           */
          operation = gimp_rectangle_select_tool_get_operation (rect_sel_tool);
          switch (operation)
            {
            case GIMP_CHANNEL_OP_REPLACE:
            case GIMP_CHANNEL_OP_INTERSECT:
              gimp_channel_clear (selection, NULL, TRUE);
              gimp_image_flush (image);
              break;

            case GIMP_CHANNEL_OP_ADD:
            case GIMP_CHANNEL_OP_SUBTRACT:
            default:
              /* Do nothing */
              break;
            }

          gimp_tool_control_pop_preserve (tool->control);
        }
    }

  gimp_rectangle_select_tool_update_option_defaults (rect_sel_tool, FALSE);

  /* Reset the automatic undo/redo mechanism */
  priv->undo = NULL;
  priv->redo = NULL;

  return TRUE;
}