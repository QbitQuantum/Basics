 //----------------------------------------------------------------------------
 ~OculusDb()
 {
   ROS_ASSERT(shutdown_oculusdb());
   nh.shutdown();
 } 