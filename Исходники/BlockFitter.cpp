BlockFitter::Result BlockFitter::
go() {
  Result result;
  result.mSuccess = false;

  if (mCloud->size() < 100) return result;

  // voxelize
  LabeledCloud::Ptr cloud(new LabeledCloud());
  pcl::VoxelGrid<pcl::PointXYZL> voxelGrid;
  voxelGrid.setInputCloud(mCloud);
  voxelGrid.setLeafSize(mDownsampleResolution, mDownsampleResolution,
                        mDownsampleResolution);
  voxelGrid.filter(*cloud);
  for (int i = 0; i < (int)cloud->size(); ++i) cloud->points[i].label = i;

  if (mDebug) {
    std::cout << "Original cloud size " << mCloud->size() << std::endl;
    std::cout << "Voxelized cloud size " << cloud->size() << std::endl;
    pcl::io::savePCDFileBinary("cloud_full.pcd", *cloud);
  }

  if (cloud->size() < 100) return result;

  // pose
  cloud->sensor_origin_.head<3>() = mOrigin;
  cloud->sensor_origin_[3] = 1;
  Eigen::Vector3f rz = mLookDir;
  Eigen::Vector3f rx = rz.cross(Eigen::Vector3f::UnitZ());
  Eigen::Vector3f ry = rz.cross(rx);
  Eigen::Matrix3f rotation;
  rotation.col(0) = rx.normalized();
  rotation.col(1) = ry.normalized();
  rotation.col(2) = rz.normalized();
  Eigen::Isometry3f pose = Eigen::Isometry3f::Identity();
  pose.linear() = rotation;
  pose.translation() = mOrigin;

  // ground removal
  if (mRemoveGround) {
    Eigen::Vector4f groundPlane;

    // filter points
    float minZ = mMinGroundZ;
    float maxZ = mMaxGroundZ;
    if ((minZ > 10000) && (maxZ > 10000)) {
      std::vector<float> zVals(cloud->size());
      for (int i = 0; i < (int)cloud->size(); ++i) {
        zVals[i] = cloud->points[i].z;
      }
      std::sort(zVals.begin(), zVals.end());
      minZ = zVals[0]-0.1;
      maxZ = minZ + 0.5;
    }
    LabeledCloud::Ptr tempCloud(new LabeledCloud());
    for (int i = 0; i < (int)cloud->size(); ++i) {
      const Eigen::Vector3f& p = cloud->points[i].getVector3fMap();
      if ((p[2] < minZ) || (p[2] > maxZ)) continue;
      tempCloud->push_back(cloud->points[i]);
    }

    // downsample
    voxelGrid.setInputCloud(tempCloud);
    voxelGrid.setLeafSize(0.1, 0.1, 0.1);
    voxelGrid.filter(*tempCloud);

    if (tempCloud->size() < 100) return result;

    // find ground plane
    std::vector<Eigen::Vector3f> pts(tempCloud->size());
    for (int i = 0; i < (int)tempCloud->size(); ++i) {
      pts[i] = tempCloud->points[i].getVector3fMap();
    }
    const float kGroundPlaneDistanceThresh = 0.01; // TODO: param
    PlaneFitter planeFitter;
    planeFitter.setMaxDistance(kGroundPlaneDistanceThresh);
    planeFitter.setRefineUsingInliers(true);
    auto res = planeFitter.go(pts);
    groundPlane = res.mPlane;
    if (groundPlane[2] < 0) groundPlane = -groundPlane;
    if (mDebug) {
      std::cout << "dominant plane: " << groundPlane.transpose() << std::endl;
      std::cout << "  inliers: " << res.mInliers.size() << std::endl;
    }

    if (std::acos(groundPlane[2]) > 30*M_PI/180) {
      std::cout << "error: ground plane not found!" << std::endl;
      std::cout << "proceeding with full segmentation (may take a while)..." <<
        std::endl;
    }

    else {
      // compute convex hull
      result.mGroundPlane = groundPlane;
      {
        tempCloud.reset(new LabeledCloud());
        for (int i = 0; i < (int)cloud->size(); ++i) {
          Eigen::Vector3f p = cloud->points[i].getVector3fMap();
          float dist = groundPlane.head<3>().dot(p) + groundPlane[3];
          if (std::abs(dist) > kGroundPlaneDistanceThresh) continue;
          p -= (groundPlane.head<3>()*dist);
          pcl::PointXYZL cloudPt;
          cloudPt.getVector3fMap() = p;
          tempCloud->push_back(cloudPt);
        }
        pcl::ConvexHull<pcl::PointXYZL> chull;
        pcl::PointCloud<pcl::PointXYZL> hull;
        chull.setInputCloud(tempCloud);
        chull.reconstruct(hull);
        result.mGroundPolygon.resize(hull.size());
        for (int i = 0; i < (int)hull.size(); ++i) {
          result.mGroundPolygon[i] = hull[i].getVector3fMap();
        }
      }

      // remove points below or near ground
      tempCloud.reset(new LabeledCloud());
      for (int i = 0; i < (int)cloud->size(); ++i) {
        Eigen::Vector3f p = cloud->points[i].getVector3fMap();
        float dist = p.dot(groundPlane.head<3>()) + groundPlane[3];
        if ((dist < mMinHeightAboveGround) ||
            (dist > mMaxHeightAboveGround)) continue;
        float range = (p-mOrigin).norm();
        if (range > mMaxRange) continue;
        tempCloud->push_back(cloud->points[i]);
      }
      std::swap(tempCloud, cloud);
      if (mDebug) {
        std::cout << "Filtered cloud size " << cloud->size() << std::endl;
      }
    }
  }

  // normal estimation
  auto t0 = std::chrono::high_resolution_clock::now();
  if (mDebug) {
    std::cout << "computing normals..." << std::flush;
  }
  RobustNormalEstimator normalEstimator;
  normalEstimator.setMaxEstimationError(0.01);
  normalEstimator.setRadius(0.1);
  normalEstimator.setMaxCenterError(0.02);
  normalEstimator.setMaxIterations(100);
  NormalCloud::Ptr normals(new NormalCloud());
  normalEstimator.go(cloud, *normals);
  if (mDebug) {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
    std::cout << "finished in " << dt.count()/1e3 << " sec" << std::endl;
  }

  // filter non-horizontal points
  const float maxNormalAngle = mMaxAngleFromHorizontal*M_PI/180;
  LabeledCloud::Ptr tempCloud(new LabeledCloud());
  NormalCloud::Ptr tempNormals(new NormalCloud());
  for (int i = 0; i < (int)normals->size(); ++i) {
    const auto& norm = normals->points[i];
    Eigen::Vector3f normal(norm.normal_x, norm.normal_y, norm.normal_z);
    float angle = std::acos(normal[2]);
    if (angle > maxNormalAngle) continue;
    tempCloud->push_back(cloud->points[i]);
    tempNormals->push_back(normals->points[i]);
  }
  std::swap(tempCloud, cloud);
  std::swap(tempNormals, normals);

  if (mDebug) {
    std::cout << "Horizontal points remaining " << cloud->size() << std::endl;
    pcl::io::savePCDFileBinary("cloud.pcd", *cloud);
    pcl::io::savePCDFileBinary("robust_normals.pcd", *normals);
  }

  // plane segmentation
  t0 = std::chrono::high_resolution_clock::now();
  if (mDebug) {
    std::cout << "segmenting planes..." << std::flush;
  }
  PlaneSegmenter segmenter;
  segmenter.setData(cloud, normals);
  segmenter.setMaxError(0.05);
  segmenter.setMaxAngle(5);
  segmenter.setMinPoints(100);
  PlaneSegmenter::Result segmenterResult = segmenter.go();
  if (mDebug) {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0);
    std::cout << "finished in " << dt.count()/1e3 << " sec" << std::endl;

    std::ofstream ofs("labels.txt");
    for (const int lab : segmenterResult.mLabels) {
      ofs << lab << std::endl;
    }
    ofs.close();

    ofs.open("planes.txt");
    for (auto it : segmenterResult.mPlanes) {
      auto& plane = it.second;
      ofs << it.first << " " << plane.transpose() << std::endl;
    }
    ofs.close();
  }

  // create point clouds
  std::unordered_map<int,std::vector<Eigen::Vector3f>> cloudMap;
  for (int i = 0; i < (int)segmenterResult.mLabels.size(); ++i) {
    int label = segmenterResult.mLabels[i];
    if (label <= 0) continue;
    cloudMap[label].push_back(cloud->points[i].getVector3fMap());
  }
  struct Plane {
    MatrixX3f mPoints;
    Eigen::Vector4f mPlane;
  };
  std::vector<Plane> planes;
  planes.reserve(cloudMap.size());
  for (auto it : cloudMap) {
    int n = it.second.size();
    Plane plane;
    plane.mPoints.resize(n,3);
    for (int i = 0; i < n; ++i) plane.mPoints.row(i) = it.second[i];
    plane.mPlane = segmenterResult.mPlanes[it.first];
    planes.push_back(plane);
  }

  std::vector<RectangleFitter::Result> results;
  for (auto& plane : planes) {
    RectangleFitter fitter;
    fitter.setDimensions(mBlockDimensions.head<2>());
    fitter.setAlgorithm((RectangleFitter::Algorithm)mRectangleFitAlgorithm);
    fitter.setData(plane.mPoints, plane.mPlane);
    auto result = fitter.go();
    results.push_back(result);
  }

  if (mDebug) {
    std::ofstream ofs("boxes.txt");
    for (int i = 0; i < (int)results.size(); ++i) {
      auto& res = results[i];
      for (auto& p : res.mPolygon) {
        ofs << i << " " << p.transpose() << std::endl;
      }
    }
    ofs.close();

    ofs.open("hulls.txt");
    for (int i = 0; i < (int)results.size(); ++i) {
      auto& res = results[i];
      for (auto& p : res.mConvexHull) {
        ofs << i << " " << p.transpose() << std::endl;
      }
    }
    ofs.close();

    ofs.open("poses.txt");
    for (int i = 0; i < (int)results.size(); ++i) {
      auto& res = results[i];
      auto transform = res.mPose;
      ofs << transform.matrix() << std::endl;
    }
    ofs.close();
  }

  for (int i = 0; i < (int)results.size(); ++i) {
    const auto& res = results[i];
    if (mBlockDimensions.head<2>().norm() > 1e-5) {
      float areaRatio = mBlockDimensions.head<2>().prod()/res.mConvexArea;
      if ((areaRatio < mAreaThreshMin) ||
          (areaRatio > mAreaThreshMax)) continue;
    }

    Block block;
    block.mSize << res.mSize[0], res.mSize[1], mBlockDimensions[2];
    block.mPose = res.mPose;
    block.mPose.translation() -=
      block.mPose.rotation().col(2)*mBlockDimensions[2]/2;
    block.mHull = res.mConvexHull;
    result.mBlocks.push_back(block);
  }
  if (mDebug) {
    std::cout << "Surviving blocks: " << result.mBlocks.size() << std::endl;
  }

  result.mSuccess = true;
  return result;
}