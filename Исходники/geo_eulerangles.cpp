template<typename Scalar> void eulerangles()
{
  typedef Matrix<Scalar,3,3> Matrix3;
  typedef Matrix<Scalar,3,1> Vector3;
  typedef Array<Scalar,3,1> Array3;
  typedef Quaternion<Scalar> Quaternionx;
  typedef AngleAxis<Scalar> AngleAxisx;

  Scalar a = internal::random<Scalar>(-Scalar(M_PI), Scalar(M_PI));
  Quaternionx q1;
  q1 = AngleAxisx(a, Vector3::Random().normalized());
  Matrix3 m;
  m = q1;
  
  Vector3 ea = m.eulerAngles(0,1,2);
  check_all_var(ea);
  ea = m.eulerAngles(0,1,0);
  check_all_var(ea);
  
  ea = (Array3::Random() + Array3(1,1,0))*Scalar(M_PI)*Array3(0.5,0.5,1);
  check_all_var(ea);
  
  ea[2] = ea[0] = internal::random<Scalar>(0,Scalar(M_PI));
  check_all_var(ea);
  
  ea[0] = ea[1] = internal::random<Scalar>(0,Scalar(M_PI));
  check_all_var(ea);
  
  ea[1] = 0;
  check_all_var(ea);
  
  ea.head(2).setZero();
  check_all_var(ea);
  
  ea.setZero();
  check_all_var(ea);
}