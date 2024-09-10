void UrdfModelMarker::graspPointCB( const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback ){
  //linkMarkerMap[feedback->marker_name].gp.pose = feedback->pose;
  //publishMarkerPose(feedback);
  //publishMarkerMenu(feedback, jsk_interactive_marker::MarkerMenu::MOVE);

  KDL::Vector graspVec(feedback->mouse_point.x, feedback->mouse_point.y, feedback->mouse_point.z);
  KDL::Frame parentFrame;
  tf::poseMsgToKDL (linkMarkerMap[feedback->marker_name].pose, parentFrame);

  graspVec = parentFrame.Inverse(graspVec);

  geometry_msgs::Pose p;
  p.position.x = graspVec.x();
  p.position.y = graspVec.y();
  p.position.z = graspVec.z();
  p.orientation = linkMarkerMap[feedback->marker_name].gp.pose.orientation;
  linkMarkerMap[feedback->marker_name].gp.pose = p;
  
  linkMarkerMap[feedback->marker_name].gp.displayGraspPoint = true;
  addChildLinkNames(model->getRoot(), true, false);
  //addChildLinkNames(model->getRoot(), true, false, true, 0);
}