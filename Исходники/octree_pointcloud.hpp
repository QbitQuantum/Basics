template<typename PointT, typename LeafT, typename BranchT, typename OctreeT> int
pcl::octree::OctreePointCloud<PointT, LeafT, BranchT, OctreeT>::getApproxIntersectedVoxelCentersBySegment (
    const Eigen::Vector3f& origin,
    const Eigen::Vector3f& end,
    AlignedPointTVector &voxel_center_list,
    float precision)
{
  Eigen::Vector3f direction = end - origin;
  float norm = direction.norm ();
  direction.normalize ();

  const float step_size = static_cast<const float> (resolution_) * precision;
  // Ensure we get at least one step for the first voxel.
  const int nsteps = std::max (1, static_cast<int> (norm / step_size));

  OctreeKey prev_key;

  bool bkeyDefined = false;

  // Walk along the line segment with small steps.
  for (int i = 0; i < nsteps; ++i)
  {
    Eigen::Vector3f p = origin + (direction * step_size * static_cast<const float> (i));

    PointT octree_p;
    octree_p.x = p.x ();
    octree_p.y = p.y ();
    octree_p.z = p.z ();

    OctreeKey key;
    this->genOctreeKeyforPoint (octree_p, key);

    // Not a new key, still the same voxel.
    if ((key == prev_key) && (bkeyDefined) )
      continue;

    prev_key = key;
    bkeyDefined = true;

    PointT center;
    genLeafNodeCenterFromOctreeKey (key, center);
    voxel_center_list.push_back (center);
  }

  OctreeKey end_key;
  PointT end_p;
  end_p.x = end.x ();
  end_p.y = end.y ();
  end_p.z = end.z ();
  this->genOctreeKeyforPoint (end_p, end_key);
  if (!(end_key == prev_key))
  {
    PointT center;
    genLeafNodeCenterFromOctreeKey (end_key, center);
    voxel_center_list.push_back (center);
  }

  return (static_cast<int> (voxel_center_list.size ()));
}