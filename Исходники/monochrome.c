static gboolean dt_iop_monochrome_draw(GtkWidget *widget, cairo_t *crf, gpointer user_data)
{
  dt_iop_module_t *self = (dt_iop_module_t *)user_data;
  dt_iop_monochrome_gui_data_t *g = (dt_iop_monochrome_gui_data_t *)self->gui_data;
  dt_iop_monochrome_params_t *p = (dt_iop_monochrome_params_t *)self->params;

  if(self->request_color_pick == DT_REQUEST_COLORPICK_MODULE)
  {
    p->a = self->picked_color[1];
    p->b = self->picked_color[2];
    float da = self->picked_color_max[1] - self->picked_color_min[1];
    float db = self->picked_color_max[2] - self->picked_color_min[2];
    p->size = CLAMP((da + db)/128.0, .5, 3.0);
  }

  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(g->colorpicker),
                               (self->request_color_pick == DT_REQUEST_COLORPICK_MODULE ? 1 : 0));

  const int inset = DT_COLORCORRECTION_INSET;
  GtkAllocation allocation;
  gtk_widget_get_allocation(widget, &allocation);
  int width = allocation.width, height = allocation.height;
  cairo_surface_t *cst = dt_cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  cairo_t *cr = cairo_create(cst);
  // clear bg
  cairo_set_source_rgb(cr, .2, .2, .2);
  cairo_paint(cr);

  cairo_translate(cr, inset, inset);
  cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);
  width -= 2 * inset;
  height -= 2 * inset;
  // clip region to inside:
  cairo_rectangle(cr, 0, 0, width, height);
  cairo_clip(cr);
  // flip y:
  cairo_translate(cr, 0, height);
  cairo_scale(cr, 1., -1.);
  const int cells = 8;
  for(int j = 0; j < cells; j++)
    for(int i = 0; i < cells; i++)
    {
      double rgb[3] = { 0.5, 0.5, 0.5 };
      cmsCIELab Lab;
      Lab.L = 53.390011;
      Lab.a = Lab.b = 0; // grey
      // dt_iop_sRGB_to_Lab(rgb, Lab, 0, 0, 1.0, 1, 1); // get grey in Lab
      Lab.a = PANEL_WIDTH * (i / (cells - 1.0) - .5);
      Lab.b = PANEL_WIDTH * (j / (cells - 1.0) - .5);
      const float f = color_filter(Lab.a, Lab.b, p->a, p->b, 40 * 40 * p->size * p->size);
      Lab.L *= f * f; // exaggerate filter a little
      cmsDoTransform(g->xform, &Lab, rgb, 1);
      cairo_set_source_rgb(cr, rgb[0], rgb[1], rgb[2]);
      cairo_rectangle(cr, width * i / (float)cells, height * j / (float)cells,
                      width / (float)cells - DT_PIXEL_APPLY_DPI(1),
                      height / (float)cells - DT_PIXEL_APPLY_DPI(1));
      cairo_fill(cr);
    }
  cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
  cairo_set_source_rgb(cr, .7, .7, .7);
  cairo_set_line_width(cr, DT_PIXEL_APPLY_DPI(2.0));
  const float x = p->a * width / PANEL_WIDTH + width * .5f, y = p->b * height / PANEL_WIDTH + height * .5f;
  cairo_arc(cr, x, y, width * .22f * p->size, 0, 2.0 * M_PI);
  cairo_stroke(cr);

  cairo_destroy(cr);
  cairo_set_source_surface(crf, cst, 0, 0);
  cairo_paint(crf);
  cairo_surface_destroy(cst);
  return TRUE;
}