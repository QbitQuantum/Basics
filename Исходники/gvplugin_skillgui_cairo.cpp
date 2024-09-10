static void
skillgui_cairo_render_ellipse(GVJ_t *job, pointf *A, int filled)
{
#ifdef USE_GVPLUGIN_TIMETRACKER
  __tt.ping_start(__ttc_ellipse);
  ++__num_ellipse;
#endif
  //printf("Render ellipse\n");
  SkillGuiCairoRenderInstructor *cri = (SkillGuiCairoRenderInstructor *)job->context;
  Cairo::RefPtr<Cairo::Context> cairo = cri->get_cairo();
  obj_state_t *obj = job->obj;

  Cairo::Matrix old_matrix;
  cairo->get_matrix(old_matrix);

  skillgui_cairo_set_penstyle(cairo, job);

  cairo->translate(A[0].x, -A[0].y);

  double rx = A[1].x - A[0].x;
  double ry = A[1].y - A[0].y;
  cairo->scale(1, ry / rx);
  cairo->move_to(rx, 0);
  cairo->arc(0, 0, rx, 0, 2 * M_PI);
  cairo->close_path();

  cairo->set_matrix(old_matrix);

  if (filled) {
    skillgui_cairo_set_color(cairo, &(obj->fillcolor));
    cairo->fill_preserve();
  }
  skillgui_cairo_set_color(cairo, &(obj->pencolor));
  cairo->stroke();

#ifdef USE_GVPLUGIN_TIMETRACKER
  __tt.ping_end(__ttc_ellipse);
#endif
}