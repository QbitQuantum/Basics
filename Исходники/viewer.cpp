bool Viewer::on_expose_event(GdkEventExpose* event)
{
  Glib::RefPtr<Gdk::GL::Drawable> gldrawable = get_gl_drawable();

  if (!gldrawable) return false;

  if (!gldrawable->gl_begin(get_gl_context()))
    return false;

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_FRONT);

// blending
  glEnable (GL_BLEND);
glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Set up for perspective drawing 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, get_width(), get_height());
  gluPerspective(40.0, (GLfloat)get_width()/(GLfloat)get_height(), 0.1, 1000.0);

  // change to model view for drawing
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Clear framebuffer{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // Set up lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // put light behind camera
  GLfloat lightpos[] = {0.5f, 1.f, 10.f, 0.f};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.f};
  GLfloat diffuse[] = {0.8f, 0.8, 0.8f, 1.f};
  GLfloat specular[] = {1.f, 1.f, 1.f, 1.f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

  glEnable(GL_NORMALIZE);

  // toogle options
  DEBUG_MSG("Front/Back Cull " << m_frontCull << "/" << m_backCull << " Zbuf " << m_zBuffer);
  if (m_frontCull || m_backCull) {
    glEnable(GL_CULL_FACE);
    if (m_backCull && m_frontCull) {
      glCullFace(GL_FRONT_AND_BACK);
    }
    else if (m_frontCull) {
      glCullFace(GL_FRONT);
    }
    else {
      glCullFace(GL_BACK);
    }
  }
  else {
    glDisable(GL_CULL_FACE);
  }
  if (m_zBuffer) {
    glEnable(GL_DEPTH_TEST);
    glDepthMask(true);
  }
  else {
    glDisable(GL_DEPTH_TEST);
    glDepthMask(false);
  }


  glPushMatrix();

    //Matrix4x4 daT = translation(Vector3D(5.0, 0.0, 0.0));
    //glMultMatrixd(daT.transpose().begin());

    // gl use column order matrix, m4x4 is row order
    Matrix4x4 trackballM = m_trackballTranslation * m_trackballRotation;
    glMultMatrixd(trackballM.transpose().begin());

      // draw model
    m_root->walk_gl(false);


    // glPushMatrix();

    //   // push keep into screen
    //   //glTranslated(0.0, 0.0, -10.0);

    //   //glTranslated(0.0, 0.0, -20.0);
    //   GLUquadricObj * quadric = gluNewQuadric();
    //   gluSphere(quadric, 1.f, 10, 10);

    // glPopMatrix();

  glPopMatrix();



  if (m_drawCircle) {
    draw_trackball_circle();
  }

  // Swap the contents of the front and back buffers so we see what we
  // just drew. This should only be done if double buffering is enabled.
  gldrawable->swap_buffers();

  gldrawable->gl_end();

  return true;
}