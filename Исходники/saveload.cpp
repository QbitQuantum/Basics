void LoadPoint(FILE *f, vcg::Point2f &p){
  LoadFloat(f,  p.X() ); 
  LoadFloat(f,  p.Y() ); 
  //printf("(%f,%f) ",p[0],p[1]);
}