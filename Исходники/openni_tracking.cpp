 void
 cloud_cb (const CloudConstPtr &cloud)
 {
   boost::mutex::scoped_lock lock (mtx_);
   double start = pcl::getTime ();
   FPS_CALC_BEGIN;
   cloud_pass_.reset (new Cloud);
   cloud_pass_downsampled_.reset (new Cloud);
   pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients ());
   pcl::PointIndices::Ptr inliers (new pcl::PointIndices ());
   filterPassThrough (cloud, *cloud_pass_);
   if (counter_ < 10)
   {
     gridSample (cloud_pass_, *cloud_pass_downsampled_, downsampling_grid_size_);
   }
   else if (counter_ == 10)
   {
     //gridSample (cloud_pass_, *cloud_pass_downsampled_, 0.01);
     cloud_pass_downsampled_ = cloud_pass_;
     CloudPtr target_cloud;
     if (use_convex_hull_)
     {
       planeSegmentation (cloud_pass_downsampled_, *coefficients, *inliers);
       if (inliers->indices.size () > 3)
       {
         CloudPtr cloud_projected (new Cloud);
         cloud_hull_.reset (new Cloud);
         nonplane_cloud_.reset (new Cloud);
         
         planeProjection (cloud_pass_downsampled_, *cloud_projected, coefficients);
         convexHull (cloud_projected, *cloud_hull_, hull_vertices_);
         
         extractNonPlanePoints (cloud_pass_downsampled_, cloud_hull_, *nonplane_cloud_);
         target_cloud = nonplane_cloud_;
       }
       else
       {
         PCL_WARN ("cannot segment plane\n");
       }
     }
     else
     {
       PCL_WARN ("without plane segmentation\n");
       target_cloud = cloud_pass_downsampled_;
     }
     
     if (target_cloud != NULL)
     {
       PCL_INFO ("segmentation, please wait...\n");
       std::vector<pcl::PointIndices> cluster_indices;
       euclideanSegment (target_cloud, cluster_indices);
       if (cluster_indices.size () > 0)
       {
         // select the cluster to track
         CloudPtr temp_cloud (new Cloud);
         extractSegmentCluster (target_cloud, cluster_indices, 0, *temp_cloud);
         Eigen::Vector4f c;
         pcl::compute3DCentroid<RefPointType> (*temp_cloud, c);
         int segment_index = 0;
         double segment_distance = c[0] * c[0] + c[1] * c[1];
         for (size_t i = 1; i < cluster_indices.size (); i++)
         {
           temp_cloud.reset (new Cloud);
           extractSegmentCluster (target_cloud, cluster_indices, int (i), *temp_cloud);
           pcl::compute3DCentroid<RefPointType> (*temp_cloud, c);
           double distance = c[0] * c[0] + c[1] * c[1];
           if (distance < segment_distance)
           {
             segment_index = int (i);
             segment_distance = distance;
           }
         }
         
         segmented_cloud_.reset (new Cloud);
         extractSegmentCluster (target_cloud, cluster_indices, segment_index, *segmented_cloud_);
         //pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
         //normalEstimation (segmented_cloud_, *normals);
         RefCloudPtr ref_cloud (new RefCloud);
         //addNormalToCloud (segmented_cloud_, normals, *ref_cloud);
         ref_cloud = segmented_cloud_;
         RefCloudPtr nonzero_ref (new RefCloud);
         removeZeroPoints (ref_cloud, *nonzero_ref);
         
         PCL_INFO ("calculating cog\n");
         
         RefCloudPtr transed_ref (new RefCloud);
         pcl::compute3DCentroid<RefPointType> (*nonzero_ref, c);
         Eigen::Affine3f trans = Eigen::Affine3f::Identity ();
         trans.translation ().matrix () = Eigen::Vector3f (c[0], c[1], c[2]);
         //pcl::transformPointCloudWithNormals<RefPointType> (*ref_cloud, *transed_ref, trans.inverse());
         pcl::transformPointCloud<RefPointType> (*nonzero_ref, *transed_ref, trans.inverse());
         CloudPtr transed_ref_downsampled (new Cloud);
         gridSample (transed_ref, *transed_ref_downsampled, downsampling_grid_size_);
         tracker_->setReferenceCloud (transed_ref_downsampled);
         tracker_->setTrans (trans);
         reference_ = transed_ref;
         tracker_->setMinIndices (int (ref_cloud->points.size ()) / 2);
       }
       else
       {
         PCL_WARN ("euclidean segmentation failed\n");
       }
     }
   }
   else
   {
     //normals_.reset (new pcl::PointCloud<pcl::Normal>);
     //normalEstimation (cloud_pass_downsampled_, *normals_);
     //RefCloudPtr tracking_cloud (new RefCloud ());
     //addNormalToCloud (cloud_pass_downsampled_, normals_, *tracking_cloud);
     //tracking_cloud = cloud_pass_downsampled_;
     
     //*cloud_pass_downsampled_ = *cloud_pass_;
     //cloud_pass_downsampled_ = cloud_pass_;
     gridSampleApprox (cloud_pass_, *cloud_pass_downsampled_, downsampling_grid_size_);
     tracking (cloud_pass_downsampled_);
   }
   
   new_cloud_ = true;
   double end = pcl::getTime ();
   computation_time_ = end - start;
   FPS_CALC_END("computation");
   counter_++;
 }