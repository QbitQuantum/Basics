//service callback:
//pause the topic model
void pause(bool p){
  if(p){
    ROS_INFO("stopped listening to words");
    word_sub.shutdown();
  }
  else{
    ROS_INFO("started listening to words");
    word_sub = nh->subscribe("words", 10, words_callback);
  }
  rost->pause(p);
  paused=p;
}