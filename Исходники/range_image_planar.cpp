  void
  RangeImagePlanar::setDepthImage (const unsigned short* depth_image, int di_width, int di_height,
                                   float di_center_x, float di_center_y,
                                   float di_focal_length_x, float di_focal_length_y,
                                   float desired_angular_resolution)
  {
    //MEASURE_FUNCTION_TIME;
    reset ();
    
    float original_angular_resolution = asinf (0.5f*static_cast<float> (di_width)/static_cast<float> (di_focal_length_x)) / (0.5f*static_cast<float> (di_width));
    int skip = 1;
    if (desired_angular_resolution >= 2.0f*original_angular_resolution)
      skip = static_cast<int> (pcl_lrint (floor (desired_angular_resolution/original_angular_resolution)));

    setAngularResolution (original_angular_resolution * static_cast<float> (skip));
    width  = di_width / skip;
    height = di_height / skip;
    focal_length_x_ = di_focal_length_x / static_cast<float> (skip);
    focal_length_x_reciprocal_ = 1.0f / focal_length_x_;
    focal_length_y_ = di_focal_length_y / static_cast<float> (skip);
    focal_length_y_reciprocal_ = 1.0f / focal_length_y_;
    center_x_ = static_cast<float> (di_center_x) / static_cast<float> (skip);
    center_y_ = static_cast<float> (di_center_y) / static_cast<float> (skip);
    points.resize (width * height);
    
    for (int y = 0; y < static_cast<int> (height); ++y)
    {
      for (int x = 0; x < static_cast<int> (width); ++x)
      {
        PointWithRange& point = getPointNoCheck (x, y);
        float depth = depth_image[ (y*skip)*di_width + x*skip] * 0.001f;
        if (depth <= 0.0f || !pcl_isfinite (depth))
        {
          point = unobserved_point;
          continue;
        }
        point.z = depth;
        point.x = (static_cast<float> (x) - center_x_) * point.z * focal_length_x_reciprocal_;
        point.y = (static_cast<float> (y) - center_y_) * point.z * focal_length_y_reciprocal_;
        point.range = point.getVector3fMap ().norm ();
      }
    }
  }