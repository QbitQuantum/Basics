// Handles (un)subscribing when clients (un)subscribe
void CropDecimateNodelet::connectCb()
{
  boost::lock_guard<boost::mutex> lock(connect_mutex_);
  if (pub_.getNumSubscribers() == 0)
    sub_.shutdown();
  else if (!sub_)
  {
    image_transport::TransportHints hints("raw", ros::TransportHints(), getPrivateNodeHandle());
    sub_ = it_in_->subscribeCamera("image_raw", queue_size_, &CropDecimateNodelet::imageCb, this, hints);
  }
}