/**
 * gimp_int_adjustment_update:
 * @adjustment: A #GtkAdjustment.
 * @data:       A pointer to a #gint variable which will store the
 *              @adjustment's value.
 *
 * Note that the #GtkAdjustment's value (which is a #gdouble) will be
 * rounded with RINT().
 **/
void
gimp_int_adjustment_update (GtkAdjustment *adjustment,
                            gpointer       data)
{
  gint *val = (gint *) data;

  *val = RINT (gtk_adjustment_get_value (adjustment));
}