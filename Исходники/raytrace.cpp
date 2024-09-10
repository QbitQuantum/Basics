// compute intersection between a triangle face and a ray
R3Intersection ComputeIntersection(R3MeshFace *tri, R3Ray &ray, double min_t)
{
  assert (tri->vertices.size() == 3);

  R3Intersection i;

  R3Point t1 = tri->vertices[0]->position;
  R3Point t2 = tri->vertices[1]->position;
  R3Point t3 = tri->vertices[2]->position;

  // intersect ray with triangle's plane
  R3Plane plane = tri->plane;
  double t = -(ray.Start().Vector().Dot(plane.Normal()) + plane.D()) 
    / (ray.Vector().Dot(plane.Normal()));

  // early return if not closer than minimum intersection for the mesh
  if (t > min_t || t < 0)
  {
    i.hit = false;
    return i;
  }


  // check if intersection is within triangle using barycentric coordinate method
  R3Point p = ray.Point(t);

  R3Vector v;

  v = t2 - t1;
  v.Cross(t3 - t1);
  double area = v.Length() / 2;

  v = t2 - t1;
  v.Cross(p - t1);
  if (v.Dot(plane.Normal()) < 0)
  {
    i.hit = false;
    return i;
  }
  double a = v.Length() / (2 * area);

  v = p - t1;
  v.Cross(t3 - t1);
  if (v.Dot(plane.Normal()) < 0)
  {
    i.hit = false;
    return i;
  }
  double b = v.Length() / (2 * area);

  if (a <= 1 && a >= 0 && b <= 1 && b >= 0 && a + b <= 1)
  {
    i.hit = true;
    if (ray.Vector().Dot(plane.Normal()) < 0)
    {
      i.normal = plane.Normal();
    }
    else
    {
      i.normal = -plane.Normal();
    }
    i.position = p;
    i.t = t;
    return i;
  } 
  else
  {
    i.hit = false;
    return i;
  }
}