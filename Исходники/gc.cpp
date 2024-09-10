Vector4d gc_av_to_aid(Vector6d av) {

  Vector4d aid;
  Vector3d a = av.head(3);
  Vector3d x = av.tail(3);  // v
  Vector3d y = a.cross(x);  // n
  aid(3) = x.norm() / y.norm();
  x /= x.norm();
  y /= y.norm();
  Vector3d z = x.cross(y);

  Matrix3d R;
  R.col(0) = x;
  R.col(1) = y;
  R.col(2) = z;

  Vector3d aa = gc_Rodriguez(R);

  aid(0) = aa(0);
  aid(1) = aa(1);
  aid(2) = aa(2);

//  Vector4d aid;
//  Vector3d a = av.head(3);
//  Vector3d v = av.tail(3);  // v
//  Vector3d n = a.cross(v);  // n
//
//  aid(3) = v.norm() / n.norm();
//
//  Vector3d x = n / n.norm();
//  Vector3d y = v / v.norm();
//  Vector3d z = x.cross(y);
//
//  aid[0] = atan2( y(2), z(2) );
//  aid[1] = asin( - x(2) );
//  aid[2] = atan2( x(1), x(0) );

  return aid;
}