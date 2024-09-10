void publish_faro_transform(tf::Transform faro_base)
{
  static tf::TransformBroadcaster br;

  //tf::Transform faro_base;

  //base_at_table - Actual,Circle,-291.052543573765,-100.393272630778,213.8235
  tf::Vector3 faro_origin(213.8235, 291.052543573765, -100.393272630778);
  faro_origin = faro_origin / 1000;
  faro_origin.setZ(faro_origin.z() + 0.10);
  faro_base.setOrigin(faro_origin);

  //+X_Coordinate System 1.i;0.9495;+Y_Coordinate System 1.i;0.3139;+Z_Coordinate System 1.i;-0.0008;
  //+X_Coordinate System 1.j;0.0007;+Y_Coordinate System 1.j;0.0005;+Z_Coordinate System 1.j;1.0000;
  //+X_Coordinate System 1.k;0.3139;+Y_Coordinate System 1.k-0.9495;+Z_Coordinate System 1.k;0.0002;
  tf::Matrix3x3 faro_rot;
  //faro_rot.setValue(0.9495, 0.3139, -0.0008, 0.0007, 0.0005, 1.0000, 0.3139, -0.9495, 0.0002);
  faro_rot.setValue(0.9495, 0.0007, 0.3139, 0.3139, 0.0005, -0.9495, -0.0008, 1.0000, 0.0002);
  tf::Quaternion faro_quat;
  double roll, pitch, yaw;
  faro_rot.getEulerYPR(yaw, pitch, roll);
  faro_quat.setRPY(roll, pitch, yaw);

  faro_base.setRotation(faro_quat);

  br.sendTransform(tf::StampedTransform(faro_base, ros::Time::now(), world_frame_, "faro_base"));

}