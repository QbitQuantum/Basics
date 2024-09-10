  Point get_vec_line_intersect(Point& vec, Point& p1, Point& p2) {
    vec.normalize();
    int code = is_vec_line_intersect(vec,p1,p2);
    if( code == 0 )
      return Point(-1,-1);
    if( code == 1 )
      return p1;
    if( code == 2 )
      return p2;

    int init_sign = get_vectors_s(Point(

  }