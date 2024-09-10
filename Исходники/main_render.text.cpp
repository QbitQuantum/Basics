  void output(vsx_module_param_abs* param)
  {
    VSX_UNUSED(param);
    if (text_in->updates)
    {
      if (process_lines())
      text_in->updates = 0;
    }
    if (text_alpha->get() <= 0)
      return;

    if (!ftfont)
    {
      user_message = "module||error loading font "+cur_font;
      return;
    }

    if (text_in->get() == "_")
      return;


    float obj_size = size->get();

    gl_state->matrix_mode (VSX_GL_MODELVIEW_MATRIX );
    gl_state->matrix_push();

    gl_state->matrix_rotate_f( (float)angle->get()*360, rotation_axis->get(0), rotation_axis->get(1), rotation_axis->get(2) );

    if (obj_size < 0)
      obj_size = 0;

    gl_state->matrix_scale_f( obj_size*0.8*0.01, obj_size*0.01, obj_size*0.01 );

    int l_align = align->get();
    float l_leading = leading->get();
    float ypos = 0;

    if (cur_render_type == 0)
      glEnable(GL_TEXTURE_2D);

    glColor4f(red->get(),green->get(),blue->get(),text_alpha->get());

    for (unsigned long i = 0; i < lines.size(); ++i)
    {
      float ll = limit_line->get();
      if (ll != -1.0f)
      {
        if (trunc(ll) != i) continue;
      }
      gl_state->matrix_push();
      if (l_align == 0)
      {
        gl_state->matrix_translate_f( 0, ypos, 0 );
      } else
      if (l_align == 1)
      {
        gl_state->matrix_translate_f( -lines[i].size_x*0.5f,ypos,0 );
      }
      if (l_align == 2)
      {
        gl_state->matrix_translate_f( -lines[i].size_x,ypos,0 );
      }

      if (cur_render_type == 1)
      {
        if (outline_alpha->get() > 0.0f && ftfont2) {
          float pre_linew;
          pre_linew = gl_state->line_width_get();
          gl_state->line_width_set( outline_thickness->get() );
          glColor4f(outline_color->get(0),outline_color->get(1),outline_color->get(2),outline_alpha->get()*outline_color->get(3));
          ftfont2->Render(lines[i].string.c_str());
          gl_state->line_width_set( pre_linew );
        }
        glColor4f(red->get(),green->get(),blue->get(),text_alpha->get());
      }

      ftfont->Render(lines[i].string.c_str());
      gl_state->matrix_pop();
      ypos += l_leading;
    }

    if (cur_render_type == 0)
      glDisable(GL_TEXTURE_2D);


    gl_state->matrix_pop();

    render_result->set(1);
    loading_done = true;
  }