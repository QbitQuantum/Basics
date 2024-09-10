  UsbCamNode() :
    node_("~")
  {
    image_transport::ImageTransport it(node_);
    image_pub_ = it.advertiseCamera("image_raw", 1);

    node_.param("video_device", video_device_name_, std::string("/dev/video0"));
    node_.param("io_method", io_method_name_, std::string("mmap")); // possible values: mmap, read, userptr
    node_.param("image_width", image_width_, 640);
    node_.param("image_height", image_height_, 480);
    node_.param("framerate", framerate_, 30);
    node_.param("pixel_format", pixel_format_name_, std::string("mjpeg")); // possible values: yuyv, uyvy, mjpeg
    node_.param("autofocus", autofocus_, false); // enable/disable autofocus


    node_.param("camera_frame_id", img_.header.frame_id, std::string("head_camera"));
    node_.param("camera_name", camera_name_, std::string("head_camera"));
    node_.param("camera_info_url", camera_info_url_, std::string(""));
    cinfo_.reset(new camera_info_manager::CameraInfoManager(node_, camera_name_, camera_info_url_));

    ROS_INFO("Camera name: %s", camera_name_.c_str());
    ROS_INFO("Camera info url: %s", camera_info_url_.c_str());
    ROS_INFO("usb_cam video_device set to [%s]\n", video_device_name_.c_str());
    ROS_INFO("usb_cam io_method set to [%s]\n", io_method_name_.c_str());
    ROS_INFO("usb_cam image_width set to [%d]\n", image_width_);
    ROS_INFO("usb_cam image_height set to [%d]\n", image_height_);
    ROS_INFO("usb_cam pixel_format set to [%s]\n", pixel_format_name_.c_str());
    ROS_INFO("usb_cam auto_focus set to [%d]\n", autofocus_);

    usb_cam_io_method io_method;
    if(io_method_name_ == "mmap")
      io_method = IO_METHOD_MMAP;
    else if(io_method_name_ == "read")
      io_method = IO_METHOD_READ;
    else if(io_method_name_ == "userptr")
      io_method = IO_METHOD_USERPTR;
    else {
      ROS_FATAL("Unknown io method.");
      node_.shutdown();
      return;
    }

    usb_cam_pixel_format pixel_format;
    if(pixel_format_name_ == "yuyv")
      pixel_format = PIXEL_FORMAT_YUYV;
    else if(pixel_format_name_ == "uyvy")
      pixel_format = PIXEL_FORMAT_UYVY;
    else if(pixel_format_name_ == "mjpeg") {
      pixel_format = PIXEL_FORMAT_MJPEG;
    }
    else {
      ROS_FATAL("Unknown pixel format.");
      node_.shutdown();
      return;
    }

    camera_image_ = usb_cam_camera_start(video_device_name_.c_str(),
                                         io_method,
                                         pixel_format,
                                         image_width_,
                                         image_height_,
                                         framerate_);

    if(autofocus_) {
      usb_cam_camera_set_auto_focus(1);
    }

    next_time_ = ros::Time::now();
    count_ = 0;
  }