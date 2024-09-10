static void calculateDirectedTransform(const Eigen::Vector3d& start,
                                       const Eigen::Vector3d& stop,
                                       const tf::Vector3 z_axis,
                                       tf::Transform& transform)
{
  tf::Vector3 origin;
  tf::Quaternion pose;

  origin.setX(start(1));
  origin.setY(start(0));
  origin.setZ(start(2) - 0.05);

  transform.setOrigin(origin);

  tf::Vector3 n = toTF(stop) - toTF(start);
  n.normalize();
  tf::Vector3 z = z_axis;
  tf::Vector3 y;
  y = n.cross(z);
  y.normalize();
  z = n.cross(y);

  tf::Matrix3x3 rotation(
       z.getX(), n.getX(), y.getX(),
       z.getY(), n.getY(), y.getY(),
       z.getZ(), n.getZ(), y.getZ());

  transform.setBasis(rotation);
}