Distance3f distance_trianglef(const float3 p, const float3* poly) {
  const float3 normal = normalize(cross(poly[1]-poly[0], poly[2]-poly[0]));

  // Degenerate triangle
  if (normal.x != normal.x) {
    // Hack to safely fail if triangle is degenerate
    float max_d = length2(poly[1]-poly[0]);
    float3 a = poly[1];
    float3 b = poly[0];
    if (length2(poly[2]-poly[1]) > max_d) {
      max_d = length2(poly[2]-poly[1]);
      a = poly[2];
      b = poly[1];
    }
    if (length2(poly[2]-poly[0]) > max_d) {
      // No need to reset max_d
      a = poly[2];
      b = poly[0];
    }
    return distance_line3(p, a, b);
  }

  const float proj_dist = dot((p - poly[0]), normal);

  const float3 proj_pnt = p - (normal * proj_dist);
  float dist = fabs(proj_dist);

  int drop_dim = 0;
  float drop_dim_val = fabs(normal.x);
  if (fabs(normal.y) > drop_dim_val) {
    drop_dim = 1;
    drop_dim_val = fabs(normal.y);
  }
  if (fabs(normal.z) > drop_dim_val) {
    drop_dim = 2;
    drop_dim_val = fabs(normal.z);
  }

  float2 poly_proj[3];
  float2 proj_proj_pnt;

#ifdef OPEN_CL
  for (int i = 0; i < 3; ++i) {
    if (drop_dim == 0) {
      poly_proj[i] = poly[i].yz;
    } else if (drop_dim == 1) {
      poly_proj[i] = poly[i].xz;
    } else {
      poly_proj[i] = poly[i].xy;
    }
  }
  if (drop_dim == 0) {
    proj_proj_pnt = proj_pnt.yz;
  } else if (drop_dim == 1) {
    proj_proj_pnt = proj_pnt.xz;
  } else {
    proj_proj_pnt = proj_pnt.xy;
  }
#else
  for (int i = 0; i < 3; ++i) {
    if (drop_dim == 0) {
      poly_proj[i] = make_float2(poly[i].y, poly[i].z);
    } else if (drop_dim == 1) {
      poly_proj[i] = make_float2(poly[i].x, poly[i].z);
    } else {
      poly_proj[i] = make_float2(poly[i].x, poly[i].y);
    }
  }
  if (drop_dim == 0) {
    proj_proj_pnt = make_float2(proj_pnt.y, proj_pnt.z);
  } else if (drop_dim == 1) {
    proj_proj_pnt = make_float2(proj_pnt.x, proj_pnt.z);
  } else {
    proj_proj_pnt = make_float2(proj_pnt.x, proj_pnt.y);
  }
#endif

  float2 poly_shift[3];
  for (int i = 0; i < 3; ++i) {
    poly_shift[i] = poly_proj[i] - proj_proj_pnt;
  }

  bool test_val;
  bool first_time = true;
  bool inside = true;
  for (int i = 0; i < 3; ++i) {
    float2 v = poly_shift[i];
    float2 vn = poly_shift[(i+1) % 3];
    float area = vn.x*v.y - v.x*vn.y;  // actually is twice area
    if (first_time) {
      test_val = area > 0;
      first_time = false;
    } else {
      if (test_val != area > 0) {
        inside = false;
        break;
      }
    }
  }

  if (inside) {
    // nan!
    /* assert(dist == dist); */

    // dist is set at start of function to be proj distance
    Distance3f d = { dist, proj_pnt };
    return d;
  } else {
    bool unset = true;
    Distance3f best;
    for (int i = 0; i < 3; ++i) {
      if (unset) {
        best = distance_line3(p, poly[i], poly[(i+1)%3]);
        unset = false;
      } else {
        Distance3f dist = distance_line3(p, poly[i], poly[(i+1)%3]);
        best = min_pair3f(best, dist);
      }
    }
    // nan!
    /* assert(best.d == best.d) { */
    return best;
  }
}