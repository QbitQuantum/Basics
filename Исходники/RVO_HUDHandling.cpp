void RV_Orientation::DrawArrow(oapi::Sketchpad *skp, bool fill, bool straight, int x, int y, int scale, VECTOR3 drot) {
  const int si = scale / 4;
  const double s = (double) si;
  int ptn = 12;
  VECTOR3 rot = {drot.x*PI/180,drot.y*PI/180,drot.z*PI/180};
  const VECTOR3 e = {0,0,500};
  VECTOR3 pt[24];
  const VECTOR3 straightArrow[8] = {
      {   s, -2*s, 0},
      {   s, -6*s, 0},
      { 4*s, -6*s, 0},
      {   0,-10*s, 0},
      {-4*s, -6*s, 0},
      {-1*s, -6*s, 0},
      {  -s, -2*s, 0},
      {   s, -2*s, 0}
  };
  const VECTOR3 curveArrow[24] = {
      {-1.000*s, -2.000*s, 0},
      {-1.076*s, -2.868*s, 0},
      {-1.302*s, -3.710*s, 0},
      {-1.670*s, -4.500*s, 0},
      {-2.170*s, -5.214*s, 0},
      {-2.786*s, -5.830*s, 0},
      {-3.500*s, -6.330*s, 0},
      {-4.290*s, -6.698*s, 0},
      {-5.132*s, -6.924*s, 0},
      {-6.000*s, -7.000*s, 0},
      {-6.000*s, -10.000*s, 0},
      {-8.000*s, -6.000*s, 0},
      {-6.000*s, -2.000*s, 0},
      {-6.000*s, -5.000*s, 0},
      {-5.479*s, -4.954*s, 0},
      {-4.974*s, -4.819*s, 0},
      {-4.500*s, -4.598*s, 0},
      {-4.072*s, -4.298*s, 0},
      {-3.702*s, -3.928*s, 0},
      {-3.402*s, -3.500*s, 0},
      {-3.181*s, -3.026*s, 0},
      {-3.046*s, -2.521*s, 0},
      {-3.000*s, -2.000*s, 0},
      {-1.000*s, -2.000*s, 0}
  };

  if (straight) {
    ptn=8;
    for (int i=0;i<ptn;i++) pt[i] = straightArrow[i];
  } else {
    ptn=24;
    for (int i=0;i<ptn;i++) pt[i] = curveArrow[i];
  }

  oapi::IVECTOR2 rpt[24];

  const MATRIX3 Xrot = {1,0,0,0,cos(rot.x),-sin(rot.x),0,sin(rot.x),cos(rot.x)};
  const MATRIX3 Yrot = {cos(rot.y),0,sin(rot.y),0,1,0,-sin(rot.y),0,cos(rot.y)};
  const MATRIX3 Zrot = {cos(rot.z),-sin(rot.z),0,sin(rot.z),cos(rot.z),0,0,0,1};
  const MATRIX3 Trot = mul(Xrot,mul(Yrot,Zrot));

  for (int i=0; i<ptn; i++) {
//    pt[i] = mul(Zrot,pt[i]);
//    pt[i] = mul(Yrot,pt[i]);
//    pt[i] = mul(Xrot,pt[i]);
    pt[i] = mul(Trot,pt[i]);
    rpt[i].x = (long) ((pt[i].x - e.x) * ((e.z - pt[i].z)/e.z) + x);
    rpt[i].y = (long) ((pt[i].y - e.y) * ((e.z - pt[i].z)/e.z) + y);
  }
 
  if (fill) {
    skp->Polygon(rpt,ptn); 
  } else {
    skp->Polyline(rpt,ptn); 
  }
  return;
}