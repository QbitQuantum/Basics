  void draw(const std::shared_ptr<maps::ViewBase>& iView,
            const std::shared_ptr<MeshRenderer>& iMeshRenderer) {
    if (!mVisible) return;

    // set mesh properties
    iMeshRenderer->setRangeOrigin(mLatestTransform.translation());
    iMeshRenderer->setScaleRange(mAttributes.mMinZ, mAttributes.mMaxZ);
    iMeshRenderer->setPointSize(mAttributes.mPointSize);
    Eigen::Projective3f worldToMap = mUseTransform ? iView->getTransform() :
      Eigen::Projective3f::Identity();
    Eigen::Projective3f mapToWorld = worldToMap.inverse();
    Eigen::Matrix3f calib;
    Eigen::Isometry3f pose;
    bool ortho;
    maps::Utils::factorViewMatrix(worldToMap, calib, pose, ortho);
    iMeshRenderer->setNormalZero(-pose.linear().col(2));

    // see whether we need to (and can) get a mesh representation
    bool usePoints = false;
    maps::TriangleMesh::Ptr mesh;
    if (mAttributes.mMeshMode == MeshRenderer::MeshModePoints) {
      usePoints = true;
    }
    else {
      mesh = iView->getAsMesh(!mUseTransform);
      if (mesh == NULL) usePoints = true;
    }

    // just a point cloud
    if (usePoints) {
      mesh.reset(new maps::TriangleMesh());
      maps::PointCloud::Ptr cloud = iView->getAsPointCloud(!mUseTransform);
      mesh->mVertices.reserve(cloud->size());
      for (size_t i = 0; i < cloud->size(); ++i) {
        mesh->mVertices.push_back((*cloud)[i].getVector3fMap());
      }
    }

    // set up mesh renderer
    iMeshRenderer->setColor(mAttributes.mColor[0],
                            mAttributes.mColor[1],
                            mAttributes.mColor[2]);
    iMeshRenderer->setColorMode
      ((MeshRenderer::ColorMode)mAttributes.mColorMode);
    iMeshRenderer->setMeshMode
      ((MeshRenderer::MeshMode)mAttributes.mMeshMode);
    if (usePoints) iMeshRenderer->setMeshMode(MeshRenderer::MeshModePoints);
    iMeshRenderer->setData(mesh->mVertices, mesh->mNormals,
                           mesh->mFaces, mapToWorld);

    // draw this view's data
    iMeshRenderer->draw();
    drawBounds();
  }