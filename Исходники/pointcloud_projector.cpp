void
PointCloudProjector::synchronized_callback(const sensor_msgs::PointCloud2ConstPtr& points_msg,
        const samplereturn_msgs::PatchArrayConstPtr& patches_msg)
{
    // create patch output message
    samplereturn_msgs::PatchArray positioned_patches;
    positioned_patches.header = patches_msg->header;
    positioned_patches.cam_info = patches_msg->cam_info;

    // create marker array debug message
    visualization_msgs::MarkerArray vis_markers;

    // create camera model object
    image_geometry::PinholeCameraModel model;
    model.fromCameraInfo(patches_msg->cam_info);

    // ensure tf is ready
    if(!listener_.canTransform(clipping_frame_id_, patches_msg->header.frame_id,
                patches_msg->header.stamp))
    {
        patches_out.publish( positioned_patches );
        return;
    }

    // get camera origin in clipping frame
    tf::StampedTransform camera;
    listener_.lookupTransform(clipping_frame_id_, patches_msg->header.frame_id,
            patches_msg->header.stamp, camera);
    Eigen::Vector3d camera_origin;
    tf::vectorTFToEigen(camera.getOrigin(), camera_origin);

    // scale and transform pointcloud into clipping frame
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr colorpoints(new pcl::PointCloud<pcl::PointXYZRGB>),
        points_native(new pcl::PointCloud<pcl::PointXYZRGB>),
        points_scaled(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::fromROSMsg(*points_msg, *points_native);
    // this scale is a horible hack to fix the manipulator point clouds
    Eigen::Transform<float, 3, Eigen::Affine> trans;
    trans.setIdentity();
    trans.scale(config_.pointcloud_scale);
    pcl::transformPointCloud(*points_native, *points_scaled, trans);
    pcl_ros::transformPointCloud(clipping_frame_id_, *points_scaled, *colorpoints, listener_);

    // id counter for debug markers
    int mid = 0;
    for(const auto& patch : patches_msg->patch_array)
    {
        samplereturn_msgs::Patch positioned_patch(patch);
        cv_bridge::CvImagePtr cv_ptr_mask;
        try {
            cv_ptr_mask = cv_bridge::toCvCopy(patch.mask, "mono8");
        }
        catch (cv_bridge::Exception& e) {
            ROS_ERROR("cv_bridge mask exception: %s", e.what());
            continue;
        }

        cv::Point2f roi_offset(patch.image_roi.x_offset, patch.image_roi.x_offset);
        Eigen::Vector4d ground_plane;
        // assume ground plane at z=0, in base_link xy plane for manipulators
        ground_plane << 0,0,1,0;
        float dimension, angle;
        tf::Stamped<tf::Point> world_point;
        if(samplereturn::computeMaskPositionAndSize(listener_,
                    cv_ptr_mask->image, roi_offset,
                    model, patches_msg->header.stamp, patches_msg->header.frame_id,
                    ground_plane, "base_link",
                    &dimension, &angle, &world_point,
                    NULL))
        {
            // if sample size is outside bounds, skip this patch
            if ((dimension > config_.max_major_axis) ||
                    (dimension < config_.min_major_axis)) {
                continue;
            }
        }


        // find bounding box of mask
        cv::Rect rect;
        samplereturn::computeBoundingBox(cv_ptr_mask->image, &rect);

        // turn image space bounding box into 4 3d rays
        cv::Point2d patch_origin(patch.image_roi.x_offset,
                patch.image_roi.y_offset);
        std::vector<cv::Point2d> rpoints;
        rpoints.push_back(cv::Point2d(rect.x,            rect.y) +
                patch_origin);
        rpoints.push_back(cv::Point2d(rect.x,            rect.y+rect.height) +
                patch_origin);
        rpoints.push_back(cv::Point2d(rect.x+rect.width, rect.y+rect.height) +
                patch_origin);
        rpoints.push_back(cv::Point2d(rect.x+rect.width, rect.y) +
                patch_origin);
        std::vector<Eigen::Vector3d> rays;
        rays.resize(rpoints.size());
        std::transform(rpoints.begin(), rpoints.end(), rays.begin(),
                [model, patches_msg, this](cv::Point2d uv) -> Eigen::Vector3d
                {
                    cv::Point3d xyz = model.projectPixelTo3dRay(uv);
                    tf::Stamped<tf::Vector3> vect(tf::Vector3(xyz.x, xyz.y, xyz.z),
                        patches_msg->header.stamp,
                        patches_msg->header.frame_id);
                    tf::Stamped<tf::Vector3> vect_t;
                    listener_.transformVector(clipping_frame_id_, vect, vect_t);
                    Eigen::Vector3d ray;
                    tf::vectorTFToEigen(vect_t, ray);
                    return ray;
                });

        // clip point cloud by the planes of the bounding volume
        // described by the rays above
        // Add one more clipping plane at z=0 in the clipping frame
        // to remove noise points below the ground
        pcl::PointIndices::Ptr clipped(new pcl::PointIndices);
        for(size_t i=0;i<rays.size()+1;i++)
        {
            Eigen::Vector4f plane;
            if(i<rays.size())
            {
                plane.segment<3>(0) = -rays[i].cross(rays[(i+1)%4]).cast<float>();
                plane[3] = -plane.segment<3>(0).dot(camera_origin.cast<float>());
            }
            else
            {
                plane << 0,0,1, config_.bottom_clipping_depth;
            }
            pcl::PlaneClipper3D<pcl::PointXYZRGB> clip(plane);
            std::vector<int> newclipped;
            clip.clipPointCloud3D(*colorpoints,  newclipped, clipped->indices);
            clipped->indices.resize(newclipped.size());
            std::copy(newclipped.begin(), newclipped.end(),
                    clipped->indices.begin());
        }

        // bail if the clipped pointcloud is empty
        if(clipped->indices.size() == 0)
        {
            continue;
        }

        // publish clipped pointcloud if anybody is listening
        if(debug_points_out.getNumSubscribers()>0)
        {
            pcl::PointCloud<pcl::PointXYZRGB> clipped_pts;
            pcl::ExtractIndices<pcl::PointXYZRGB> extract;
            extract.setInputCloud(colorpoints);
            extract.setIndices(clipped);
            extract.filter(clipped_pts);
            sensor_msgs::PointCloud2 clipped_msg;
            pcl::toROSMsg(clipped_pts, clipped_msg);
            debug_points_out.publish( clipped_msg );
        }

        // compute suitable z value for this patch
        // First, find min, max and sum
        typedef std::tuple<float, float, float> stats_tuple;
        stats_tuple z_stats = std::accumulate(
                clipped->indices.begin(), clipped->indices.end(),
                std::make_tuple(std::numeric_limits<float>().max(),
                                std::numeric_limits<float>().min(),
                                0.0f),
                [colorpoints](stats_tuple sum, int idx) -> stats_tuple
                {
                    return std::make_tuple(
                        std::min(std::get<0>(sum), colorpoints->points[idx].z),
                        std::max(std::get<1>(sum), colorpoints->points[idx].z),
                        std::get<2>(sum) + colorpoints->points[idx].z);
                });
        // use sum to find mean
        float z_min = std::get<0>(z_stats);
        float z_max = std::get<1>(z_stats);
        float z_mean = std::get<2>(z_stats)/float(clipped->indices.size());
        // build histogram of values larger than mean
        float hist_min = z_min + (z_mean-z_min)*config_.hist_min_scale;
        ROS_DEBUG("z_min: %04.3f z_mean: %04.3f z_max: %04.3f z_sum: %4.2f hist_min:%04.3f",
                z_min, z_mean, z_max, std::get<2>(z_stats), hist_min);
        const int NHIST = 20;
        int z_hist[NHIST];
        bzero(z_hist, NHIST*sizeof(int));
        std::accumulate(clipped->indices.begin(), clipped->indices.end(), z_hist,
                [colorpoints, hist_min, z_max](int *z_hist, int idx) -> int *
                {
                    float z = colorpoints->points[idx].z;
                    if(z>hist_min)
                    {
                        int zidx = floor((z-hist_min)*NHIST/(z_max-hist_min));
                        z_hist[zidx] ++;
                    }
                    return z_hist;
                });
        char debughist[2048];
        int pos=0;
        for(int i=0;i<NHIST;i++)
        {
            pos += snprintf(debughist+pos, 2048-pos, "%d, ", z_hist[i]);
        }
        debughist[pos] = '\x00';
        ROS_DEBUG("hist: %s", debughist);
        // select the most common value larger than the mean
        int * argmax = std::max_element( z_hist, z_hist + NHIST );
        ROS_DEBUG("argmax: %d", int(argmax - z_hist));
        float z_peak = (argmax - z_hist)*(z_max - hist_min)/NHIST + hist_min;
        if(z_peak>config_.maximum_patch_height)
        {
            ROS_INFO("Clipping z to max, was %f", z_peak);
            z_peak = config_.maximum_patch_height;
        }

        // project center of patch until it hits z_peak
        cv::Point2d uv = cv::Point2d(rect.x + rect.width/2, rect.y + rect.height/2) + patch_origin;
        cv::Point3d cvxyz = model.projectPixelTo3dRay(uv);
        tf::Stamped<tf::Vector3> patch_ray(
                tf::Vector3(
                    cvxyz.x,
                    cvxyz.y,
                    cvxyz.z),
                patches_msg->header.stamp,
                patches_msg->header.frame_id);
        tf::Stamped<tf::Vector3> clipping_ray;
        listener_.transformVector( clipping_frame_id_, patch_ray, clipping_ray);
        clipping_ray.normalize();
        double r = (z_peak - camera_origin.z())/clipping_ray.z();
        // finally, compute expected object position
        tf::Stamped<tf::Vector3> stamped_camera_origin(
                tf::Vector3(camera_origin.x(),
                    camera_origin.y(),
                    camera_origin.z()),
                patches_msg->header.stamp,
                clipping_frame_id_);

        tf::Vector3 object_position = stamped_camera_origin + r*clipping_ray;

        ROS_DEBUG_STREAM("patch_ray: (" <<
                patch_ray.x() << ", " << patch_ray.y() << ", " << patch_ray.z() << ") ");
        ROS_DEBUG_STREAM("clipping_ray: (" <<
                clipping_ray.x() << ", " << clipping_ray.y() << ", " << clipping_ray.z() << ") " << " z_peak: " << z_peak << " r: " << r);

        // put corresponding point_stamped in output message
        tf::Stamped<tf::Vector3> point(
                object_position,
                patches_msg->header.stamp,
                clipping_frame_id_);
        if(listener_.canTransform(output_frame_id_, point.frame_id_, point.stamp_))
        {
            tf::Stamped<tf::Vector3> output_point;
            listener_.transformPoint(output_frame_id_, point, output_point);
            tf::pointStampedTFToMsg(output_point, positioned_patch.world_point);
        }
        else
        {
            tf::pointStampedTFToMsg(point, positioned_patch.world_point);
        }
        positioned_patches.patch_array.push_back(positioned_patch);

        if(debug_marker_out.getNumSubscribers()>0)
        {
            visualization_msgs::Marker marker;
            marker.id = mid++;
            marker.type = visualization_msgs::Marker::SPHERE;
            marker.action = visualization_msgs::Marker::ADD;
            marker.header = positioned_patch.world_point.header;
            marker.pose.position = positioned_patch.world_point.point;
            marker.scale.x = 0.02;
            marker.scale.y = 0.02;
            marker.scale.z = 0.02;
            marker.color.r = 0.0;
            marker.color.g = 0.0;
            marker.color.b = 1.0;
            marker.color.a = 1.0;
            vis_markers.markers.push_back(marker);
        }
    }

    patches_out.publish( positioned_patches );

    if(debug_marker_out.getNumSubscribers()>0)
    {
        debug_marker_out.publish(vis_markers);
    }
}