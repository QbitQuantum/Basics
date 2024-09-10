static void
radius_callback (GtkWidget *slider, gpointer user_data)
{
  dt_iop_module_t *self = (dt_iop_module_t *)user_data;
  if(self->dt->gui->reset) return;
  dt_iop_lowpass_params_t *p = (dt_iop_lowpass_params_t *)self->params;
  p->radius = copysignf(dt_bauhaus_slider_get(slider), p->radius);
  dt_dev_add_history_item(darktable.develop, self, TRUE);
}