void receive(ros::Rate & loop_rate) {
  for (unsigned i = 0u; i < 10u; i++){
    ros::spinOnce();
    loop_rate.sleep();
  }
}