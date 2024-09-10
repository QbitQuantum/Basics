int ShapeGraspPlanner::createGrasp(const geometry_msgs::PoseStamped& pose,
                                   double gripper_opening,
                                   double gripper_pitch,
                                   double x_offset,
                                   double z_offset,
                                   double quality)
{
  moveit_msgs::Grasp grasp;
  grasp.grasp_pose = pose;

  // defaults
  grasp.pre_grasp_posture = makeGraspPosture(gripper_opening);
  grasp.grasp_posture = makeGraspPosture(0.0);
  grasp.pre_grasp_approach = makeGripperTranslation(approach_frame_,
                                                    approach_min_translation_,
                                                    approach_desired_translation_);
  grasp.post_grasp_retreat = makeGripperTranslation(retreat_frame_,
                                                    retreat_min_translation_,
                                                    retreat_desired_translation_,
                                                    -1.0);  // retreat is in negative x direction

  // initial pose
  Eigen::Affine3d p = Eigen::Translation3d(pose.pose.position.x,
                                           pose.pose.position.y,
                                           pose.pose.position.z) *
                        Eigen::Quaterniond(pose.pose.orientation.w,
                                           pose.pose.orientation.x,
                                           pose.pose.orientation.y,
                                           pose.pose.orientation.z);
  // translate by x_offset, 0, z_offset
  p = p * Eigen::Translation3d(x_offset, 0, z_offset);
  // rotate by 0, pitch, 0
  p = p * quaternionFromEuler(0.0, gripper_pitch, 0.0);
  // apply grasp point -> planning frame offset
  p = p * Eigen::Translation3d(-tool_offset_, 0, 0);

  grasp.grasp_pose.pose.position.x = p.translation().x();
  grasp.grasp_pose.pose.position.y = p.translation().y();
  grasp.grasp_pose.pose.position.z = p.translation().z();
  Eigen::Quaterniond q = (Eigen::Quaterniond)p.linear();
  grasp.grasp_pose.pose.orientation.x = q.x();
  grasp.grasp_pose.pose.orientation.y = q.y();
  grasp.grasp_pose.pose.orientation.z = q.z();
  grasp.grasp_pose.pose.orientation.w = q.w();

  grasp.grasp_quality = quality;

  grasps_.push_back(grasp);
  return 1;
}