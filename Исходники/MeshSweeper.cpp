TriangleMesh*
MeshSweeper::makeBox(
  const vec3& center,
  const vec3& normal,
  const vec3& up,
  const vec3& size,
  const mat4& m)
//[]----------------------------------------------------[]
//|  Make box 1                                          |
//[]----------------------------------------------------[]
{
  Polyline poly;
  vec3 N(normal.versor());
  vec3 U(up.cross(normal).versor());
  vec3 V(N.cross(U));

  N *= size.z * (REAL)0.5;
  U *= size.x * (REAL)0.5;
  V *= size.y * (REAL)0.5;
  poly.mv(center - U - V - N);
  poly.mv(center + U - V - N);
  poly.mv(center + U + V - N);
  poly.mv(center - U + V - N);
  poly.close();
  return makeCylinder(poly, 2 * N, m);
}