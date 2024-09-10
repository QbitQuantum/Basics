  void stop ()
  {
    if (!running)
      return;

    cam_->stop ();              // Must stop camera before streaming_pub_.
    poll_srv_.shutdown ();
    streaming_pub_.shutdown ();

    running = false;
  }