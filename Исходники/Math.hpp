Eigen::Matrix4f rotate(float angle,Eigen::Vector3f v)
{
  float c = cosf(angle);
  float s = sinf(angle);
  v.normalize();
  float x = v.x();
  float y = v.y();
  float z = v.z();
  const float vals[] = 
  {
    x*x*(1-c)+c  ,x*y*(1-c)-z*s,x*z*(1-c)+y*s,0,
    y*x*(1-c)+z*s,y*y*(1-c)+c  ,y*z*(1-c)-x*s,0,
    x*z*(1-c)-y*s,y*z*(1-c)+x*s,z*z*(1-c)+c  ,0,
    0            ,0            ,0            ,1
  };
  return Eigen::Matrix4f(vals).transpose();
}