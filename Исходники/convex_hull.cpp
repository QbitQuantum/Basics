void
  pcl_ros::ConvexHull2D::input_indices_callback (const PointCloudConstPtr &cloud, 
                                                 const PointIndicesConstPtr &indices)
{
  // No subscribers, no work
  if (pub_output_.getNumSubscribers () <= 0 && pub_plane_.getNumSubscribers () <= 0)
    return;

  PointCloud output;

  // If cloud is given, check if it's valid
  if (!isValid (cloud))
  {
    NODELET_ERROR ("[%s::input_indices_callback] Invalid input!", getName ().c_str ());
    // Publish an empty message
    output.header = cloud->header;
    pub_output_.publish (output.makeShared ());
    return;
  }
  // If indices are given, check if they are valid
  if (indices && !isValid (indices, "indices"))
  {
    NODELET_ERROR ("[%s::input_indices_callback] Invalid indices!", getName ().c_str ());
    // Publish an empty message
    output.header = cloud->header;
    pub_output_.publish (output.makeShared ());
    return;
  }

  /// DEBUG
  if (indices)
    NODELET_DEBUG ("[%s::input_indices_model_callback]\n"
                   "                                 - PointCloud with %d data points (%s), stamp %f, and frame %s on topic %s received.\n"
                   "                                 - PointIndices with %zu values, stamp %f, and frame %s on topic %s received.",
                   getName ().c_str (),
                   cloud->width * cloud->height, pcl::getFieldsList (*cloud).c_str (), cloud->header.stamp.toSec (), cloud->header.frame_id.c_str (), getMTPrivateNodeHandle ().resolveName ("input").c_str (),
                   indices->indices.size (), indices->header.stamp.toSec (), indices->header.frame_id.c_str (), getMTPrivateNodeHandle ().resolveName ("indices").c_str ());
  else
    NODELET_DEBUG ("[%s::input_indices_callback] PointCloud with %d data points, stamp %f, and frame %s on topic %s received.", getName ().c_str (), cloud->width * cloud->height, cloud->header.stamp.toSec (), cloud->header.frame_id.c_str (), getMTPrivateNodeHandle ().resolveName ("input").c_str ());

  // Reset the indices and surface pointers
  IndicesPtr indices_ptr;
  if (indices)
    indices_ptr.reset (new std::vector<int> (indices->indices));

  impl_.setInputCloud (cloud);
  impl_.setIndices (indices_ptr);

  // Estimate the feature
  impl_.reconstruct (output);

  // If more than 3 points are present, send a PolygonStamped hull too
  if (output.points.size () >= 3)
  {
    geometry_msgs::PolygonStamped poly;
    poly.header = output.header;
    poly.polygon.points.resize (output.points.size ());
    // Get three consecutive points (without copying)
    pcl::Vector4fMap O = output.points[1].getVector4fMap ();
    pcl::Vector4fMap B = output.points[0].getVector4fMap ();
    pcl::Vector4fMap A = output.points[2].getVector4fMap ();
    // Check the direction of points -- polygon must have CCW direction
    Eigen::Vector4f OA = A - O;
    Eigen::Vector4f OB = B - O;
    Eigen::Vector4f N = OA.cross3 (OB);
    double theta = N.dot (O);
    bool reversed = false;
    if (theta < (M_PI / 2.0))
      reversed = true;
    for (size_t i = 0; i < output.points.size (); ++i)
    {
      if (reversed)
      {
        size_t j = output.points.size () - i - 1;
        poly.polygon.points[i].x = output.points[j].x;
        poly.polygon.points[i].y = output.points[j].y;
        poly.polygon.points[i].z = output.points[j].z;
      }
      else
      {
        poly.polygon.points[i].x = output.points[i].x;
        poly.polygon.points[i].y = output.points[i].y;
        poly.polygon.points[i].z = output.points[i].z;
      }
    }
    pub_plane_.publish (boost::make_shared<const geometry_msgs::PolygonStamped> (poly));
  }
  // Publish a Boost shared ptr const data
  output.header = cloud->header;
  pub_output_.publish (output.makeShared ());
}