void
AmclNode::laserReceived(const sensor_msgs::LaserScanConstPtr& laser_scan)
{
    last_laser_received_ts_ = ros::Time::now();
    if( map_ == NULL ) {
        return;
    }
    boost::recursive_mutex::scoped_lock lr(configuration_mutex_);
    int laser_index = -1;

    // Do we have the base->base_laser Tx yet?
    if(frame_to_laser_.find(laser_scan->header.frame_id) == frame_to_laser_.end())
    {
        ROS_DEBUG("Setting up laser %d (frame_id=%s)\n", (int)frame_to_laser_.size(), laser_scan->header.frame_id.c_str());
        lasers_.push_back(new AMCLLaser(*laser_));
        lasers_update_.push_back(true);
        laser_index = frame_to_laser_.size();

        tf::Stamped<tf::Pose> ident (tf::Transform(tf::createIdentityQuaternion(),
                                     tf::Vector3(0,0,0)),
                                     ros::Time(), laser_scan->header.frame_id);
        tf::Stamped<tf::Pose> laser_pose;
        try
        {
            this->tf_->transformPose(base_frame_id_, ident, laser_pose);
        }
        catch(tf::TransformException& e)
        {
            ROS_ERROR("Couldn't transform from %s to %s, "
                      "even though the message notifier is in use",
                      laser_scan->header.frame_id.c_str(),
                      base_frame_id_.c_str());
            return;
        }

        pf_vector_t laser_pose_v;
        laser_pose_v.v[0] = laser_pose.getOrigin().x();
        laser_pose_v.v[1] = laser_pose.getOrigin().y();
        // laser mounting angle gets computed later -> set to 0 here!
        laser_pose_v.v[2] = 0;
        lasers_[laser_index]->SetLaserPose(laser_pose_v);
        ROS_DEBUG("Received laser's pose wrt robot: %.3f %.3f %.3f",
                  laser_pose_v.v[0],
                  laser_pose_v.v[1],
                  laser_pose_v.v[2]);

        frame_to_laser_[laser_scan->header.frame_id] = laser_index;
    } else {
        // we have the laser pose, retrieve laser index
        laser_index = frame_to_laser_[laser_scan->header.frame_id];
    }

    // Where was the robot when this scan was taken?
    tf::Stamped<tf::Pose> odom_pose;
    pf_vector_t pose;
    if(!getOdomPose(odom_pose, pose.v[0], pose.v[1], pose.v[2],
                    laser_scan->header.stamp, base_frame_id_))
    {
        ROS_ERROR("Couldn't determine robot's pose associated with laser scan");
        return;
    }


    pf_vector_t delta = pf_vector_zero();

    if(pf_init_)
    {
        // Compute change in pose
        //delta = pf_vector_coord_sub(pose, pf_odom_pose_);
        delta.v[0] = pose.v[0] - pf_odom_pose_.v[0];
        delta.v[1] = pose.v[1] - pf_odom_pose_.v[1];
        delta.v[2] = angle_diff(pose.v[2], pf_odom_pose_.v[2]);

        // See if we should update the filter
        bool update = fabs(delta.v[0]) > d_thresh_ ||
                      fabs(delta.v[1]) > d_thresh_ ||
                      fabs(delta.v[2]) > a_thresh_;
        update = update || m_force_update;
        m_force_update=false;

        // Set the laser update flags
        if(update)
            for(unsigned int i=0; i < lasers_update_.size(); i++)
                lasers_update_[i] = true;
    }

    bool force_publication = false;
    if(!pf_init_)
    {
        // Pose at last filter update
        pf_odom_pose_ = pose;

        // Filter is now initialized
        pf_init_ = true;

        // Should update sensor data
        for(unsigned int i=0; i < lasers_update_.size(); i++)
            lasers_update_[i] = true;

        force_publication = true;

        resample_count_ = 0;
    }
    // If the robot has moved, update the filter
    else if(pf_init_ && lasers_update_[laser_index])
    {
        //printf("pose\n");
        //pf_vector_fprintf(pose, stdout, "%.3f");

        AMCLOdomData odata;
        odata.pose = pose;
        // HACK
        // Modify the delta in the action data so the filter gets
        // updated correctly
        odata.delta = delta;

        // Use the action data to update the filter
        odom_->UpdateAction(pf_, (AMCLSensorData*)&odata);

        // Pose at last filter update
        //this->pf_odom_pose = pose;
    }

    bool resampled = false;
    // If the robot has moved, update the filter
    if(lasers_update_[laser_index])
    {
        AMCLLaserData ldata;
        ldata.sensor = lasers_[laser_index];
        ldata.range_count = laser_scan->ranges.size();

        // To account for lasers that are mounted upside-down, we determine the
        // min, max, and increment angles of the laser in the base frame.
        //
        // Construct min and max angles of laser, in the base_link frame.
        tf::Quaternion q;
        q.setRPY(0.0, 0.0, laser_scan->angle_min);
        tf::Stamped<tf::Quaternion> min_q(q, laser_scan->header.stamp,
                                          laser_scan->header.frame_id);
        q.setRPY(0.0, 0.0, laser_scan->angle_min + laser_scan->angle_increment);
        tf::Stamped<tf::Quaternion> inc_q(q, laser_scan->header.stamp,
                                          laser_scan->header.frame_id);
        try
        {
            tf_->transformQuaternion(base_frame_id_, min_q, min_q);
            tf_->transformQuaternion(base_frame_id_, inc_q, inc_q);
        }
        catch(tf::TransformException& e)
        {
            ROS_WARN("Unable to transform min/max laser angles into base frame: %s",
                     e.what());
            return;
        }

        double angle_min = tf::getYaw(min_q);
        double angle_increment = tf::getYaw(inc_q) - angle_min;

        // wrapping angle to [-pi .. pi]
        angle_increment = fmod(angle_increment + 5*M_PI, 2*M_PI) - M_PI;

        ROS_DEBUG("Laser %d angles in base frame: min: %.3f inc: %.3f", laser_index, angle_min, angle_increment);

        // Apply range min/max thresholds, if the user supplied them
        if(laser_max_range_ > 0.0)
            ldata.range_max = std::min(laser_scan->range_max, (float)laser_max_range_);
        else
            ldata.range_max = laser_scan->range_max;
        double range_min;
        if(laser_min_range_ > 0.0)
            range_min = std::max(laser_scan->range_min, (float)laser_min_range_);
        else
            range_min = laser_scan->range_min;
        // The AMCLLaserData destructor will free this memory
        ldata.ranges = new double[ldata.range_count][2];
        ROS_ASSERT(ldata.ranges);
        for(int i=0; i<ldata.range_count; i++)
        {
            // amcl doesn't (yet) have a concept of min range.  So we'll map short
            // readings to max range.
            if(laser_scan->ranges[i] <= range_min)
                ldata.ranges[i][0] = ldata.range_max;
            else
                ldata.ranges[i][0] = laser_scan->ranges[i];
            // Compute bearing
            ldata.ranges[i][1] = angle_min +
                                 (i * angle_increment);
        }

        lasers_[laser_index]->UpdateSensor(pf_, (AMCLSensorData*)&ldata);

        lasers_update_[laser_index] = false;

        pf_odom_pose_ = pose;

        // Resample the particles
        if(!(++resample_count_ % resample_interval_))
        {
            pf_update_resample(pf_);
            resampled = true;
        }

        pf_sample_set_t* set = pf_->sets + pf_->current_set;
        ROS_DEBUG("Num samples: %d\n", set->sample_count);

        // Publish the resulting cloud
        // TODO: set maximum rate for publishing
        if (!m_force_update) {
            geometry_msgs::PoseArray cloud_msg;
            cloud_msg.header.stamp = ros::Time::now();
            cloud_msg.header.frame_id = global_frame_id_;
            cloud_msg.poses.resize(set->sample_count);
            for(int i=0; i<set->sample_count; i++)
            {
                tf::poseTFToMsg(tf::Pose(tf::createQuaternionFromYaw(set->samples[i].pose.v[2]),
                                         tf::Vector3(set->samples[i].pose.v[0],
                                                     set->samples[i].pose.v[1], 0)),
                                cloud_msg.poses[i]);
            }
            particlecloud_pub_.publish(cloud_msg);
        }
    }

    if(resampled || force_publication)
    {
        // Read out the current hypotheses
        double max_weight = 0.0;
        int max_weight_hyp = -1;
        std::vector<amcl_hyp_t> hyps;
        hyps.resize(pf_->sets[pf_->current_set].cluster_count);
        for(int hyp_count = 0;
                hyp_count < pf_->sets[pf_->current_set].cluster_count; hyp_count++)
        {
            double weight;
            pf_vector_t pose_mean;
            pf_matrix_t pose_cov;
            if (!pf_get_cluster_stats(pf_, hyp_count, &weight, &pose_mean, &pose_cov))
            {
                ROS_ERROR("Couldn't get stats on cluster %d", hyp_count);
                break;
            }

            hyps[hyp_count].weight = weight;
            hyps[hyp_count].pf_pose_mean = pose_mean;
            hyps[hyp_count].pf_pose_cov = pose_cov;

            if(hyps[hyp_count].weight > max_weight)
            {
                max_weight = hyps[hyp_count].weight;
                max_weight_hyp = hyp_count;
            }
        }

        if(max_weight > 0.0)
        {
            ROS_DEBUG("Max weight pose: %.3f %.3f %.3f",
                      hyps[max_weight_hyp].pf_pose_mean.v[0],
                      hyps[max_weight_hyp].pf_pose_mean.v[1],
                      hyps[max_weight_hyp].pf_pose_mean.v[2]);

            /*
               puts("");
               pf_matrix_fprintf(hyps[max_weight_hyp].pf_pose_cov, stdout, "%6.3f");
               puts("");
             */

            geometry_msgs::PoseWithCovarianceStamped p;
            // Fill in the header
            p.header.frame_id = global_frame_id_;
            p.header.stamp = laser_scan->header.stamp;
            // Copy in the pose
            p.pose.pose.position.x = hyps[max_weight_hyp].pf_pose_mean.v[0];
            p.pose.pose.position.y = hyps[max_weight_hyp].pf_pose_mean.v[1];
            tf::quaternionTFToMsg(tf::createQuaternionFromYaw(hyps[max_weight_hyp].pf_pose_mean.v[2]),
                                  p.pose.pose.orientation);
            // Copy in the covariance, converting from 3-D to 6-D
            pf_sample_set_t* set = pf_->sets + pf_->current_set;
            for(int i=0; i<2; i++)
            {
                for(int j=0; j<2; j++)
                {
                    // Report the overall filter covariance, rather than the
                    // covariance for the highest-weight cluster
                    //p.covariance[6*i+j] = hyps[max_weight_hyp].pf_pose_cov.m[i][j];
                    p.pose.covariance[6*i+j] = set->cov.m[i][j];
                }
            }
            // Report the overall filter covariance, rather than the
            // covariance for the highest-weight cluster
            //p.covariance[6*5+5] = hyps[max_weight_hyp].pf_pose_cov.m[2][2];
            p.pose.covariance[6*5+5] = set->cov.m[2][2];

            /*
               printf("cov:\n");
               for(int i=0; i<6; i++)
               {
               for(int j=0; j<6; j++)
               printf("%6.3f ", p.covariance[6*i+j]);
               puts("");
               }
             */

            pose_pub_.publish(p);
            last_published_pose = p;

            ROS_DEBUG("New pose: %6.3f %6.3f %6.3f",
                      hyps[max_weight_hyp].pf_pose_mean.v[0],
                      hyps[max_weight_hyp].pf_pose_mean.v[1],
                      hyps[max_weight_hyp].pf_pose_mean.v[2]);

            // subtracting base to odom from map to base and send map to odom instead
            tf::Stamped<tf::Pose> odom_to_map;
            try
            {
                tf::Transform tmp_tf(tf::createQuaternionFromYaw(hyps[max_weight_hyp].pf_pose_mean.v[2]),
                                     tf::Vector3(hyps[max_weight_hyp].pf_pose_mean.v[0],
                                                 hyps[max_weight_hyp].pf_pose_mean.v[1],
                                                 0.0));
                tf::Stamped<tf::Pose> tmp_tf_stamped (tmp_tf.inverse(),
                                                      laser_scan->header.stamp,
                                                      base_frame_id_);
                this->tf_->transformPose(odom_frame_id_,
                                         tmp_tf_stamped,
                                         odom_to_map);
            }
            catch(tf::TransformException)
            {
                ROS_DEBUG("Failed to subtract base to odom transform");
                return;
            }

            latest_tf_ = tf::Transform(tf::Quaternion(odom_to_map.getRotation()),
                                       tf::Point(odom_to_map.getOrigin()));
            latest_tf_valid_ = true;

            if (tf_broadcast_ == true)
            {
                // We want to send a transform that is good up until a
                // tolerance time so that odom can be used
                ros::Time transform_expiration = (laser_scan->header.stamp +
                                                  transform_tolerance_);
                tf::StampedTransform tmp_tf_stamped(latest_tf_.inverse(),
                                                    transform_expiration,
                                                    global_frame_id_, odom_frame_id_);
                this->tfb_->sendTransform(tmp_tf_stamped);
                sent_first_transform_ = true;
            }
        }
        else
        {
            ROS_ERROR("No pose!");
        }
    }
    else if(latest_tf_valid_)
    {
        if (tf_broadcast_ == true)
        {
            // Nothing changed, so we'll just republish the last transform, to keep
            // everybody happy.
            ros::Time transform_expiration = (laser_scan->header.stamp +
                                              transform_tolerance_);
            tf::StampedTransform tmp_tf_stamped(latest_tf_.inverse(),
                                                transform_expiration,
                                                global_frame_id_, odom_frame_id_);
            this->tfb_->sendTransform(tmp_tf_stamped);
        }

        // Is it time to save our last pose to the param server
        ros::Time now = ros::Time::now();
        if((save_pose_period.toSec() > 0.0) &&
                (now - save_pose_last_time) >= save_pose_period)
        {
            // We need to apply the last transform to the latest odom pose to get
            // the latest map pose to store.  We'll take the covariance from
            // last_published_pose.
            tf::Pose map_pose = latest_tf_.inverse() * odom_pose;
            double yaw,pitch,roll;
            map_pose.getBasis().getEulerYPR(yaw, pitch, roll);

            private_nh_.setParam("initial_pose_x", map_pose.getOrigin().x());
            private_nh_.setParam("initial_pose_y", map_pose.getOrigin().y());
            private_nh_.setParam("initial_pose_a", yaw);
            private_nh_.setParam("initial_cov_xx",
                                 last_published_pose.pose.covariance[6*0+0]);
            private_nh_.setParam("initial_cov_yy",
                                 last_published_pose.pose.covariance[6*1+1]);
            private_nh_.setParam("initial_cov_aa",
                                 last_published_pose.pose.covariance[6*5+5]);
            save_pose_last_time = now;
        }
    }

}