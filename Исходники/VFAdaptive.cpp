double VFAdaptive::getErr(Voronoi3D::Vertex *vert, const SEBase *eval, const MedialTester *mt, const Voronoi3D *vor){
  if (vert->err < 0){
    if (!eval){                 //  no evaluator - use convex approx
      //  get closest point
      Point3D pClose;
      mt->closestPoint(&pClose, vert);

      if (vert->flag == VOR_FLAG_UNKNOWN)
        OUTPUTINFO("GetErr : UNCATEGORISED POINT\n");

      //  evaluate fit
      float dSur = pClose.distance(vert->s.c);
      if (vert->flag == VOR_FLAG_COVER){
        vert->err = vert->s.r + dSur;    //  sphere center is outside surface 
        }
      else{
        vert->err = vert->s.r - dSur;    //  sphere center is inside surface
        if (vert->err < 0)
          vert->err = 0;
        }
      }
    else{
      vert->err = eval->evalSphere(vert->s);
      }
    }

  return vert->err;
}