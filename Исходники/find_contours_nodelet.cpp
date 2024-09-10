 void unsubscribe()
 {
   NODELET_DEBUG("Unsubscribing from image topic.");
   img_sub_.shutdown();
   cam_sub_.shutdown();
 }