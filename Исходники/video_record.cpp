bool stopServiceCallBack(qbo_video_record::StopRecord::Request  &req,
         qbo_video_record::StopRecord::Response &res )
{
  ROS_INFO("Service Called");
  ROS_INFO("Recived:Stop");
//  cvReleaseVideoWriter(&writer);
  if (status==1)
  {
    status=0;
    kill( pID, SIGKILL );
    sub.shutdown();
    thread thread_1 = thread(combineAudioVideo);
    res.result=true;
  }
  else{
    res.result=false;
  }
  return true;
}