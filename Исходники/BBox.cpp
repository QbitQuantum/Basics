  bool BBox::ray_triangle(Vec3f &ray_start, Vec3f &ray_end, ISectTri &tri) 
  {
    Vec3f origin = ray_start;
    Vec3f direction = ray_end - ray_start;
    double dist = direction.length();
    direction.normalize();
    
    Vec3f p;
    Vec3f q;
    Vec3f s;
    double a, f, u, v, t;
    
    p = cross(direction, Vec3f(tri.edge1));
    a = dot(Vec3f(tri.edge0),p);
    if (a>-f_eps && a<f_eps)
      return false;
    f = 1/a;
    s = origin - Vec3f(tri.point0);
    u = f*dot(s,p);
    if (u<0.0 || u>1.0)
      return false;
    q = cross(s, Vec3f(tri.edge0));
    v = f * dot(direction, q);  
    if (v<0.0 || u+v>1.0)
      return false;
    t = f*dot(Vec3f(tri.edge1), q);
    if (t<0)
      return false;
//	if (t<eps)
//		return false;
    if (t>dist)
      return false;

    return true;
  }