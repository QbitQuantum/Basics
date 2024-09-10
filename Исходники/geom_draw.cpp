void DebugHooks::drawFaceLoopWireframe(const std::vector<const carve::geom3d::Vector *> &face_loop,
                                       const carve::geom3d::Vector &normal,
                                       float r, float g, float b, float a,
                                       bool inset) {
  glDisable(GL_DEPTH_TEST);

  const size_t S = face_loop.size();

  double INSET = 0.005;

  if (inset) {
    glColor4f(r, g, b, a / 2.0);
    glBegin(GL_LINE_LOOP);

    for (size_t i = 0; i < S; ++i) {
      size_t i_pre = (i + S - 1) % S;
      size_t i_post = (i + 1) % S;

      carve::geom3d::Vector v1 = (*face_loop[i] - *face_loop[i_pre]).normalized();
      carve::geom3d::Vector v2 = (*face_loop[i] - *face_loop[i_post]).normalized();

      carve::geom3d::Vector n1 = cross(normal, v1);
      carve::geom3d::Vector n2 = cross(v2, normal);

      carve::geom3d::Vector v = *face_loop[i];

      carve::geom3d::Vector p1 = v + INSET * n1;
      carve::geom3d::Vector p2 = v + INSET * n2;

      carve::geom3d::Vector i1 , i2;
      double mu1, mu2;

      carve::geom3d::Vector p;

      if (carve::geom3d::rayRayIntersection(carve::geom3d::Ray(v1, p1), carve::geom3d::Ray(v2, p2), i1, i2, mu1, mu2)) {
        p = (i1 + i2) / 2;
      } else {
        p = (p1 + p2) / 2;
      }

      glVertex(&p);
    }

    glEnd();
  }

  glColor4f(r, g, b, a);

  glBegin(GL_LINE_LOOP);

  for (unsigned i = 0; i < S; ++i) {
    glVertex(face_loop[i]);
  }

  glEnd();

  glColor4f(r, g, b, a);
  glPointSize(3.0);
  glBegin(GL_POINTS);

  for (unsigned i = 0; i < S; ++i) {
    carve::geom3d::Vector p = *face_loop[i];
    glVertex(face_loop[i]);
  }

  glEnd();

  glEnable(GL_DEPTH_TEST);
}