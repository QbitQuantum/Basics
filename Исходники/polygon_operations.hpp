template<typename PointT> void
pcl16::approximatePolygon (const PlanarPolygon<PointT>& polygon, PlanarPolygon<PointT>& approx_polygon, float threshold, bool refine, bool closed)
{
  const Eigen::Vector4f& coefficients = polygon.getCoefficients ();
  const typename pcl16::PointCloud<PointT>::VectorType &contour = polygon.getContour ();
  
  Eigen::Vector3f rotation_axis (coefficients[1], -coefficients[0], 0.0f);
  rotation_axis.normalize ();

  float rotation_angle = acosf (coefficients [2]);
  Eigen::Affine3f transformation = Eigen::Translation3f (0, 0, coefficients [3]) * Eigen::AngleAxisf (rotation_angle, rotation_axis);

  typename pcl16::PointCloud<PointT>::VectorType polygon2D (contour.size ());
  for (unsigned pIdx = 0; pIdx < polygon2D.size (); ++pIdx)
    polygon2D [pIdx].getVector3fMap () = transformation * contour [pIdx].getVector3fMap ();

  typename pcl16::PointCloud<PointT>::VectorType approx_polygon2D;
  approximatePolygon2D<PointT> (polygon2D, approx_polygon2D, threshold, refine, closed);
  
  typename pcl16::PointCloud<PointT>::VectorType &approx_contour = approx_polygon.getContour ();
  approx_contour.resize (approx_polygon2D.size ());
  
  Eigen::Affine3f inv_transformation = transformation.inverse ();
  for (unsigned pIdx = 0; pIdx < approx_polygon2D.size (); ++pIdx)
    approx_contour [pIdx].getVector3fMap () = inv_transformation * approx_polygon2D [pIdx].getVector3fMap ();
}