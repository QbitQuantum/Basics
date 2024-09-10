void VRayCamera::buildMesh(void) {
  if (meshBuilt) return;

  int nverts = 16;
  int nfaces = 24;
  mesh.setNumVerts(nverts);
  mesh.setNumFaces(nfaces);
  float len = (float)5.0;
  float w = (float)8.0;
  float d = w*(float).8;
  float e = d*(float).5;
  float f = d*(float).8;
  float l = w*(float).8;

  mesh.setVert(0, Point3( -d, -d, -len));
  mesh.setVert(1, Point3(  d, -d, -len));
  mesh.setVert(2, Point3( -d,  d, -len));
  mesh.setVert(3, Point3(  d,  d, -len));
  mesh.setVert(4, Point3( -d, -d,  len));
  mesh.setVert(5, Point3(  d, -d,  len));
  mesh.setVert(6, Point3( -d,  d,  len));
  mesh.setVert(7, Point3(  d,  d,  len));
  MakeQuad(&(mesh.faces[ 0]), 0,2,3,1,  1);
  MakeQuad(&(mesh.faces[ 2]), 2,0,4,6,  2);
  MakeQuad(&(mesh.faces[ 4]), 3,2,6,7,  4);
  MakeQuad(&(mesh.faces[ 6]), 1,3,7,5,  8);
  MakeQuad(&(mesh.faces[ 8]), 0,1,5,4, 16);
  MakeQuad(&(mesh.faces[10]), 4,5,7,6, 32);

  mesh.setVert(8+0, Point3( -e, -e, len));
  mesh.setVert(8+1, Point3(  e, -e, len));
  mesh.setVert(8+2, Point3( -e,  e, len));
  mesh.setVert(8+3, Point3(  e,  e, len));
  mesh.setVert(8+4, Point3( -f, -f, len+l));
  mesh.setVert(8+5, Point3(  f, -f, len+l));
  mesh.setVert(8+6, Point3( -f,  f, len+l));
  mesh.setVert(8+7, Point3(  f,  f, len+l));

  Face* fbase = &mesh.faces[12];
  MakeQuad(&fbase[0], 0,2,3,1,  1, 8);
  MakeQuad(&fbase[2], 2,0,4,6,  2, 8);
  MakeQuad(&fbase[4], 3,2,6,7,  4, 8);
  MakeQuad(&fbase[6], 1,3,7,5,  8, 8);
  MakeQuad(&fbase[8], 0,1,5,4, 16, 8);
  MakeQuad(&fbase[10],4,5,7,6, 32, 8);

  // whoops- rotate 180 about x to get it facing the right way
  Matrix3 mat;
  mat.IdentityMatrix();
  mat.RotateX(DegToRad(180.0));
  for (int i=0; i<nverts; i++) mesh.getVert(i)=mat*mesh.getVert(i);
  mesh.buildNormals();
  mesh.EnableEdgeList(1);
  meshBuilt = true;
}