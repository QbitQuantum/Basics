void Visualizer::visualizeMarkers(
    const FramePtr& frame,
    const set<FramePtr>& core_kfs,
    const Map& map,
    bool inited,
    double svo_scale,
    double our_scale)
{
  if((frame == NULL) || !inited)
  {
      vk::output_helper::publishTfTransform(
//                  SE3(Matrix3d::Identity(), Vector3d::Zero()),
                  T_world_from_vision_,
                  ros::Time(frame->timestamp_), "odom", "cam_pos", br_);
      return;
  }

  SE3 temp = (frame->T_f_w_*T_world_from_vision_.inverse()).inverse();
  double scale = our_scale / svo_scale;
  temp.translation() = temp.translation()* scale;

  vk::output_helper::publishTfTransform(
      temp,
      ros::Time(frame->timestamp_), "odom", "cam_pos", br_);

  if(pub_frames_.getNumSubscribers() > 0 || pub_points_.getNumSubscribers() > 0)
  {
    vk::output_helper::publishHexacopterMarker(
        pub_frames_, "cam_pos", "cams", ros::Time(frame->timestamp_),
        1, 0, 0.3, Vector3d(0.,0.,1.));
    vk::output_helper::publishPointMarker(
        pub_points_, T_world_from_vision_*frame->pos(), "trajectory",
        ros::Time::now(), trace_id_, 0, 0.006, Vector3d(0.,0.,0.5));
    if(frame->isKeyframe() || publish_map_every_frame_)
      publishMapRegion(core_kfs);
    removeDeletedPts(map);
  }
}