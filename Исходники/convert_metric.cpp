// Handles (un)subscribing when clients (un)subscribe
void ConvertMetricNodelet::connectCb()
{
  boost::lock_guard<boost::mutex> lock(connect_mutex_);
  if (pub_depth_.getNumSubscribers() == 0)
  {
    sub_raw_.shutdown();
  }
  else if (!sub_raw_)
  {
    image_transport::TransportHints hints("raw", ros::TransportHints(), getPrivateNodeHandle());
    sub_raw_ = it_->subscribe("image_raw", 1, &ConvertMetricNodelet::depthCb, this, hints);
  }
}