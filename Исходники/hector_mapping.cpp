void Node::mapPublishThread(ros::Rate rate)
{
  while(ros::ok()) {
    {
#ifdef USE_HECTOR_TIMING
      hector_diagnostics::TimingSection section("map publish");
#endif
      publishMap();
    }
    rate.sleep();
  }
}