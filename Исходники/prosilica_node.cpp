  void stop()
  {
    if (!running_) return;

    cam_->stop(); // Must stop camera before streaming_pub_.
    poll_srv_.shutdown();
    trigger_sub_.shutdown();
    streaming_pub_.shutdown();

    running_ = false;
  }