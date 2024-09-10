// Construct polygon region
FXRegion::FXRegion(const FXPoint* points,FXuint npoints,FXbool winding){
#ifdef WIN32
  register FXuint i;
  POINT pts[1024];
  for(i=0; i<npoints; i++){
    pts[i].x=points[i].x;
    pts[i].y=points[i].y;
    }
  region=(void*)CreatePolygonRgn(pts,npoints,winding?WINDING:ALTERNATE);
#else
  region=XPolygonRegion((XPoint*)points,npoints,winding?WindingRule:EvenOddRule);
#endif
  }