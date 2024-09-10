static void _relocateVertexOfPyramid(MVertex *ver,
                                     const std::vector<MElement *> &lt,
                                     double relax)
{
  if(ver->onWhat()->dim() != 3) return;
  double x = 0.0, y = 0.0, z = 0.0;
  int N = 0;
  MElement *pyramid = NULL;

  for(std::size_t i = 0; i < lt.size(); i++) {
    double XCG = 0.0, YCG = 0.0, ZCG = 0.0;
    if(lt[i]->getNumVertices() == 5)
      pyramid = lt[i];
    else {
      for(std::size_t j = 0; j < lt[i]->getNumVertices(); j++) {
        XCG += lt[i]->getVertex(j)->x();
        YCG += lt[i]->getVertex(j)->y();
        ZCG += lt[i]->getVertex(j)->z();
      }
      x += XCG;
      y += YCG;
      z += ZCG;
      N += lt[i]->getNumVertices();
    }
  }
  x /= N;
  y /= N;
  z /= N;

  if(pyramid) {
    MFace q = pyramid->getFace(4);
    double A = q.approximateArea();
    SVector3 n = q.normal();
    n.normalize();
    SPoint3 c = q.barycenter();
    SVector3 d(x - c.x(), y - c.y(), z - c.z());
    if(dot(n, d) < 0) n = n * (-1.0);
    double H = .5 * sqrt(fabs(A));
    double XOPT = c.x() + relax * H * n.x();
    double YOPT = c.y() + relax * H * n.y();
    double ZOPT = c.z() + relax * H * n.z();
    double FULL_MOVE_OBJ =
      objective_function(1.0, ver, XOPT, YOPT, ZOPT, lt, true);
    // printf("relax %g obj %g\n",relax,FULL_MOVE_OBJ);
    if(FULL_MOVE_OBJ > 0.1) {
      ver->x() = XOPT;
      ver->y() = YOPT;
      ver->z() = ZOPT;
      return;
    }
  }
}