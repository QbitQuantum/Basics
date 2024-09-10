  // run face recognition on the recieved image 
  void recognizeCb(const sensor_msgs::ImageConstPtr& msg) {
    // cout << "entering.. recognizeCb" << endl;

    _ph.getParam("algorithm", _recognitionAlgo);

    if (_as.isPreemptRequested() || !ros::ok()) {
      // std::cout << "preempt req or not ok" << std::endl;
      ROS_INFO("%s: Preempted", _action_name.c_str());
      // set the action state to preempted
      _as.setPreempted();
      // success = false;
      // break;
      // cout << "shutting down _image_sub" << endl;
      _image_sub.shutdown();
      Mat inactive(_window_rows, _window_cols, CV_8UC3, CV_RGB(20,20,20));
      appendStatusBar(inactive, "INACTIVE", "");
      cv::imshow(_windowName, inactive);
      cv::waitKey(3);
      return;
    }

    if (!_as.isActive()) {
      // std::cout << "not active" << std::endl;
      // cout << "shutting down _image_sub" << endl;
      _image_sub.shutdown();
      Mat inactive(_window_rows, _window_cols, CV_8UC3, CV_RGB(20,20,20));
      appendStatusBar(inactive, "INACTIVE", "");
      cv::imshow(_windowName, inactive);
      cv::waitKey(3);
      return;
    }

    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("%s: cv_bridge exception: %s", _action_name.c_str(), e.what());
      return;
    }

    if (_window_rows == 0) {
      _window_rows = cv_ptr->image.rows;
      _window_cols = cv_ptr->image.cols;
    }

    // clear previous feedback
    _feedback.names.clear();
    _feedback.confidence.clear();
    // _result.names.clear();
    // _result.confidence.clear();

    std::vector<cv::Rect> faces;
    std::vector<cv::Mat> faceImgs = _fd.getFaceImgs(cv_ptr->image, faces, true);
    std::map<string, std::pair<string, double> > results;
    
    for( size_t i = 0; i < faceImgs.size(); i++ ) {
      cv::resize(faceImgs[i], faceImgs[i], cv::Size(100.0, 100.0));
      cv::cvtColor( faceImgs[i], faceImgs[i], CV_BGR2GRAY );
      cv::equalizeHist( faceImgs[i], faceImgs[i] );

      // perform recognition
      results = _fr->recognize(faceImgs[i],
                                ("eigenfaces" == _recognitionAlgo),
                                ("fisherfaces" == _recognitionAlgo),
                                ("lbph" == _recognitionAlgo)
                              );

      ROS_INFO("Face %lu:", i);
      if ("eigenfaces" == _recognitionAlgo)
        ROS_INFO("\tEigenfaces: %s %f", results["eigenfaces"].first.c_str(), results["eigenfaces"].second);
      if ("fisherfaces" == _recognitionAlgo)
        ROS_INFO("\tFisherfaces: %s %f", results["fisherfaces"].first.c_str(), results["fisherfaces"].second);
      if ("lbph" == _recognitionAlgo)
        ROS_INFO("\tLBPH: %s %f", results["lbph"].first.c_str(), results["lbph"].second);
    }


    // update GUI window
    // TODO check gui parameter
    appendStatusBar(cv_ptr->image, "RECOGNITION", "");
    cv::imshow(_windowName, cv_ptr->image);
    cv::waitKey(3);

    // if faces were detected
    if (faceImgs.size() > 0) {
      // recognize only once
      if (_goal_id == 0) {
        // std::cout << "goal_id 0. setting succeeded." << std::endl;
        // cout << _recognitionAlgo << endl;
        _result.names.push_back(results[_recognitionAlgo].first);
        _result.confidence.push_back(results[_recognitionAlgo].second);
        _as.setSucceeded(_result);
      }
      // recognize continuously
      else {
        _feedback.names.push_back(results[_recognitionAlgo].first);
        _feedback.confidence.push_back(results[_recognitionAlgo].second);
        _as.publishFeedback(_feedback);
      }
    }
  } 