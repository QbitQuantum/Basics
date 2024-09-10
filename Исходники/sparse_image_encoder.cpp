 void unsubscribe() {
   NODELET_DEBUG("Unsubscribing from image topic.");
   _img_sub.shutdown();
 }