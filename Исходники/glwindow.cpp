  void
  GLWindow::motion(int x, int y)
  {
    Mouse m = mouse_;
    float delta_x = m.beginx - x, delta_y = m.beginy - y;
    if (m.button == GLUT_LEFT_BUTTON && m.state == GLUT_DOWN)
    {
      if (m.modifiers & GLUT_ACTIVE_SHIFT)
      {
        //zoom in and out
        camera_.setFovY(camera_.fovY() * (1.0f + (delta_y / camera_.vpWidth())));
      }
      else
      {
        Eigen::AngleAxisf ry(-delta_x / camera_.vpWidth(), Eigen::Vector3f(0, 1, 0));
        Eigen::AngleAxisf rx(-delta_y / camera_.vpHeight(), Eigen::Vector3f(1, 0, 0));
        Eigen::Quaternionf qx(rx), qy(ry);
        camera_.rotateAroundTarget(qy);
        camera_.rotateAroundTarget(qx);
      }
    }
    else if (m.button == GLUT_MIDDLE_BUTTON && m.state == GLUT_DOWN)
    {

      Vector3f X = camera_.position();
      Eigen::Quaternionf q = camera_.orientation();
      float factor = 10;

      Vector3f dX;
      if (m.modifiers & GLUT_ACTIVE_SHIFT)
      {
        //move along the camera plane normal
        dX = q * Vector3f(factor * delta_x / camera_.vpWidth(), 0, factor * (-delta_y) / camera_.vpHeight());
      }
      else
      {
        //compute the delta x using the the camera orientation,
        //so that the motion is in the plane of the camera.
        dX = q * Vector3f(factor * delta_x / camera_.vpWidth(), factor * (-delta_y) / camera_.vpHeight(), 0);
      }
      camera_.setPosition(X + dX);
    }
    mouse_.beginx = x;
    mouse_.beginy = y;
  }