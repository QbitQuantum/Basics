  void NICPQGLViewer::updateCameraPosition(Eigen::Isometry3f pose) {
    qglviewer::Camera *oldcam = camera();
    qglviewer::Camera *cam = new StandardCamera();
    setCamera(cam);

    Eigen::Vector3f position = pose*Vector3f(-2.0f, 0.0f, 1.0f);
    cam->setPosition(qglviewer::Vec(position[0], position[1], position[2]));
    Eigen::Vector3f upVector = pose.linear()*Vector3f(0.0f, 0.0f, 0.5f);
    upVector.normalize();
    cam->setUpVector(qglviewer::Vec(upVector[0], upVector[1], upVector[2]), true);
  
    Eigen::Vector3f lookAt = pose*Vector3f(4.0f, 0.0f, 0.0f);  
    cam->lookAt(qglviewer::Vec(lookAt[0], lookAt[1], lookAt[2]));  

    delete oldcam;
  }