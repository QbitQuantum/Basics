/* -----------------------------
 * p_offset_update
 * -----------------------------
 */
static void
p_offset_update(GtkWidget *w, gpointer   data)
{
  GapResizePrivateType *res_private;
  gdouble ofs_x;
  gdouble ofs_y;

  res_private  = (GapResizePrivateType *) data;
  if(res_private == NULL) {return;}

  ofs_x = GTK_ADJUSTMENT(res_private->offset_x_adj)->value;
  ofs_y = GTK_ADJUSTMENT(res_private->offset_y_adj)->value;

  res_private->offset_x = p_resize_bound_off_x (res_private, RINT(ofs_x));

  res_private->offset_y = p_resize_bound_off_y (res_private, RINT(ofs_y));


  gimp_offset_area_set_offsets (GIMP_OFFSET_AREA (res_private->offset_area)
                                 , res_private->offset_x
                                 , res_private->offset_y);
}  /* end p_offset_update */