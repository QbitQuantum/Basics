 void unsubscribe()
 {
     ROS_DEBUG("Unsubscribing from image topic.");
     img_sub_.shutdown();
 }