  static bool colorize(const drc::map_image_t& iDepthMap,
                       const bot_core::image_t& iImage,
                       typename pcl::PointCloud<T>::Ptr& oCloud) {
    int w(iDepthMap.width), h(iDepthMap.height);
    if ((w != iImage.width) || (h != iImage.height)) {
      return false;
    }

    // TODO: for now, reject compressed depth maps
    if (iDepthMap.compression != drc::map_image_t::COMPRESSION_NONE) {
      return false;
    }

    // TODO: for now, only accept rgb3 images
    if (iImage.pixelformat != PIXEL_FORMAT_RGB) {
      return false;
    }

    if (oCloud == NULL) {
      oCloud.reset(new pcl::PointCloud<T>());
    }
    oCloud->points.clear();

    Eigen::Matrix4d xform;
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        xform(i,j) = iDepthMap.transform[i][j];
      }
    }
    xform = xform.inverse();

    for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
        double z;
        if (iDepthMap.format == drc::map_image_t::FORMAT_GRAY_FLOAT32) {
          z = ((float*)(&iDepthMap.data[0] + i*iDepthMap.row_bytes))[j];
          if (z < -1e10) {
            continue;
          }
        }
        else if (iDepthMap.format == drc::map_image_t::FORMAT_GRAY_UINT8) {
          uint8_t val = iDepthMap.data[i*iDepthMap.row_bytes + j];
          if (val == 0) {
            continue;
          }
          z = val;
        }
        else {
          continue;
        }

        Eigen::Vector4d pt = xform*Eigen::Vector4d(j,i,z,1);
        T newPoint;
        newPoint.x = pt(0)/pt(3);
        newPoint.y = pt(1)/pt(3);
        newPoint.z = pt(2)/pt(3);
        int imageIndex = i*iImage.row_stride + 3*j;
        newPoint.r = iImage.data[imageIndex+0];
        newPoint.g = iImage.data[imageIndex+1];
        newPoint.b = iImage.data[imageIndex+2];
        oCloud->points.push_back(newPoint);
      }
    }
    oCloud->width = oCloud->points.size();
    oCloud->height = 1;
    oCloud->is_dense = false;

    return true;
  }