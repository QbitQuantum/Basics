  //Integrate pointcloud after transforming to target frame
  void Chisel::IntegratePointCloud(const ProjectionIntegrator& integrator, const PointCloud& cloud, const Transform& extrinsic, float minDist, float maxDist)
  {
    ChunkVoxelMap updatedVoxels;
    const Vec3& start = extrinsic.translation();

    //TODO: parallelize
    for (const Vec3& point : cloud.GetPoints())
    {
        Vec3 point_transformed = extrinsic * point;
        IntegrateRay(integrator, updatedVoxels, start, point_transformed, minDist, maxDist);
    }

    DetermineUpdatedChunks(updatedVoxels);
  }