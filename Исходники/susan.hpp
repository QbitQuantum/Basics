template <typename PointInT, typename PointOutT, typename NormalT, typename IntensityT> bool
pcl::SUSANKeypoint<PointInT, PointOutT, NormalT, IntensityT>::isWithinNucleusCentroid (const Eigen::Vector3f& nucleus,
                                                                                       const Eigen::Vector3f& centroid,
                                                                                       const Eigen::Vector3f& nc,
                                                                                       const PointInT& point) const
{
  Eigen::Vector3f pc = centroid - point.getVector3fMap ();
  Eigen::Vector3f pn = nucleus - point.getVector3fMap ();
  Eigen::Vector3f pc_cross_nc = pc.cross (nc);
  return ((pc_cross_nc.norm () <= tolerance_) && (pc.dot (nc) >= 0) && (pn.dot (nc) <= 0));
}