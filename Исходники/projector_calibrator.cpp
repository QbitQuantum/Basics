void computeTransformationFromYZVectorsAndOrigin(const Eigen::Vector3f& y_direction, const Eigen::Vector3f& z_axis,
  const Eigen::Vector3f& origin, Eigen::Affine3f& transformation){

 Eigen::Vector3f x = (y_direction.cross(z_axis)).normalized();
 Eigen::Vector3f y = y_direction.normalized();
 Eigen::Vector3f z = z_axis.normalized();

 Eigen::Affine3f sub = Eigen::Affine3f::Identity();
 sub(0,3) = -origin[0];
 sub(1,3) = -origin[1];
 sub(2,3) = -origin[2];


 transformation = Eigen::Affine3f::Identity();
 transformation(0,0)=x[0]; transformation(0,1)=x[1]; transformation(0,2)=x[2]; // x^t
 transformation(1,0)=y[0]; transformation(1,1)=y[1]; transformation(1,2)=y[2]; // y^t
 transformation(2,0)=z[0]; transformation(2,1)=z[1]; transformation(2,2)=z[2]; // z^t

 transformation = transformation*sub;
}