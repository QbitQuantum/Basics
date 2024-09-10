/**
 * gimp_display_shell_scroll_center_image_coordinate:
 * @shell:
 * @image_x:
 * @image_y:
 *
 * Center the viewport around the passed image coordinate
 *
 **/
void
gimp_display_shell_scroll_center_image_coordinate (GimpDisplayShell *shell,
                                                   gdouble           image_x,
                                                   gdouble           image_y)
{
  gint scaled_image_x;
  gint scaled_image_y;
  gint offset_to_apply_x;
  gint offset_to_apply_y;

  scaled_image_x = RINT (image_x * shell->scale_x);
  scaled_image_y = RINT (image_y * shell->scale_y);

  offset_to_apply_x = scaled_image_x - shell->disp_width  / 2 - shell->offset_x;
  offset_to_apply_y = scaled_image_y - shell->disp_height / 2 - shell->offset_y;

  gimp_display_shell_scroll (shell,
                             offset_to_apply_x,
                             offset_to_apply_y);
}