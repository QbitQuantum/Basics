template <typename PointT, typename NormalT> bool
cpu_tsdf::TSDFVolumeOctree::integrateCloud (
  const pcl::PointCloud<PointT> &cloud, 
  const pcl::PointCloud<NormalT> &normals,
  const Eigen::Affine3d &trans)
{
  Eigen::Affine3f trans_inv = trans.inverse ().cast<float> ();

  // First, sample a few points and force their containing voxels to split
  int px_step = 1;
  int nsplit = 0;
  for (size_t u = 0; u < cloud.width; u += px_step)
  {
    for (size_t v = 0; v < cloud.height; v += px_step)
    {
      const PointT &pt_surface_orig = cloud (u, v);
      if (pcl_isnan (pt_surface_orig.z))
        continue;
      // Look at surroundings
      int nstep = 0;
      Eigen::Vector3f ray = pt_surface_orig.getVector3fMap ().normalized ();
      for (int perm = 0; perm < num_random_splits_; perm++)
      {
        // Get containing voxels
        PointT pt_trans; 
        float scale = (float)rand () / (float)RAND_MAX * 0.03;
        Eigen::Vector3f noise = Eigen::Vector3f::Random ().normalized () * scale;;
        if (perm == 0) noise *= 0;
        pt_trans.getVector3fMap () = trans.cast<float> () * (pt_surface_orig.getVector3fMap ()+ noise);
        OctreeNode* voxel = octree_->getContainingVoxel (pt_trans.x, pt_trans.y, pt_trans.z);
        if (voxel != NULL)
        {
          while (voxel->getMinSize () > xsize_ / xres_)
          {
            nsplit++;
            voxel->split ();
            voxel = voxel->getContainingVoxel (pt_trans.x, pt_trans.y, pt_trans.z);
            
          }
        }
      }
    }
  }
  
  // Do Frustum Culling to get rid of unseen voxels
  std::vector<cpu_tsdf::OctreeNode::Ptr> voxels_culled;
  getFrustumCulledVoxels(trans, voxels_culled);
#pragma omp parallel for
  for (size_t i = 0; i < voxels_culled.size (); i++)
  {
    updateVoxel (voxels_culled[i], cloud, normals, trans_inv);
  }
  // Cloud is no longer empty
  is_empty_ = false;
  return (true);
}