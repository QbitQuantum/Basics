Vector6d bodySpatialMotionPD(RigidBodyManipulator *r, DrakeRobotState &robot_state, const int body_index, const Isometry3d &body_pose_des, const Ref<const Vector6d> &body_v_des, const Ref<const Vector6d> &body_vdot_des, const Ref<const Vector6d> &Kp, const Ref<const Vector6d> &Kd, const Isometry3d &T_task_to_world)
{
  // @param body_pose_des  desired pose in the task frame, this is the homogeneous transformation from desired body frame to task frame 
  // @param body_v_des    desired [xyzdot;angular_velocity] in task frame
  // @param body_vdot_des    desired [xyzddot;angular_acceleration] in task frame
  // @param Kp     The gain in task frame
  // @param Kd     The gain in task frame 
  // @param T_task_to_world  The homogeneous transform from task to world
  // @retval twist_dot, [angular_acceleration, xyz_acceleration] in body frame

  if(!r->getUseNewKinsol())
  {
    throw std::runtime_error("bodySpatialMotionPD requires new kinsol format");
  }
  Isometry3d T_world_to_task = T_task_to_world.inverse();
  r->doKinematicsNew(robot_state.q,robot_state.qd,false);

  Vector3d origin = Vector3d::Zero();
  auto body_pose = r->forwardKinNew(origin,body_index,0,2,0);
  Vector3d body_xyz = body_pose.value().head<3>();
  Vector3d body_xyz_task = T_world_to_task * body_xyz.colwise().homogeneous();
  Vector4d body_quat = body_pose.value().tail<4>();
  std::vector<int> v_indices;
  auto J_geometric = r->geometricJacobian<double>(0,body_index,body_index,0,true,&v_indices);
  VectorXd v_compact(v_indices.size());
  for(size_t i = 0;i<v_indices.size();i++)
  {
    v_compact(i) = robot_state.qd(v_indices[i]);
  }
  Vector6d body_twist = J_geometric.value() * v_compact;
  Matrix3d R_body_to_world = quat2rotmat(body_quat);
  Matrix3d R_world_to_body = R_body_to_world.transpose();
  Matrix3d R_body_to_task = T_world_to_task.linear() * R_body_to_world;
  Vector3d body_angular_vel = R_body_to_world * body_twist.head<3>();// body_angular velocity in world frame
  Vector3d body_xyzdot = R_body_to_world * body_twist.tail<3>();// body_xyzdot in world frame
  Vector3d body_angular_vel_task = T_world_to_task.linear() * body_angular_vel;
  Vector3d body_xyzdot_task = T_world_to_task.linear() * body_xyzdot;

  Vector3d body_xyz_des = body_pose_des.translation();
  Vector3d body_angular_vel_des = body_v_des.tail<3>();
  Vector3d body_angular_vel_dot_des = body_vdot_des.tail<3>();

  Vector3d xyz_err_task = body_xyz_des-body_xyz_task;

  Matrix3d R_des = body_pose_des.linear();
  Matrix3d R_err_task = R_des * R_body_to_task.transpose();
  Vector4d angleAxis_err_task = rotmat2axis(R_err_task); 
  Vector3d angular_err_task = angleAxis_err_task.head<3>() * angleAxis_err_task(3);

  Vector3d xyzdot_err_task = body_v_des.head<3>() - body_xyzdot_task;
  Vector3d angular_vel_err_task = body_angular_vel_des - body_angular_vel_task;

  Vector3d Kp_xyz = Kp.head<3>();
  Vector3d Kd_xyz = Kd.head<3>();
  Vector3d Kp_angular = Kp.tail<3>();
  Vector3d Kd_angular = Kd.tail<3>();
  Vector3d body_xyzddot_task = (Kp_xyz.array() * xyz_err_task.array()).matrix() + (Kd_xyz.array() * xyzdot_err_task.array()).matrix() + body_vdot_des.head<3>();
  Vector3d body_angular_vel_dot_task = (Kp_angular.array() * angular_err_task.array()).matrix() + (Kd_angular.array() * angular_vel_err_task.array()).matrix() + body_angular_vel_dot_des;
  
  Vector6d twist_dot = Vector6d::Zero();
  Vector3d body_xyzddot = T_task_to_world.linear() * body_xyzddot_task;
  Vector3d body_angular_vel_dot = T_task_to_world.linear() * body_angular_vel_dot_task;
  twist_dot.head<3>() = R_world_to_body * body_angular_vel_dot;
  twist_dot.tail<3>() = R_world_to_body * body_xyzddot - body_twist.head<3>().cross(body_twist.tail<3>());
  return twist_dot;
}