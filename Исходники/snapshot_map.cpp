	/*
	 * here comes the object cluster point cloud in camera frame of reference
	 */
	void dataCallback(const sensor_msgs::PointCloud2ConstPtr& point_cloud) {

		if( !create_map_ )
			return;

		ROS_INFO("creating map");
		object_mutex.lock();
		ROS_INFO("dataCallback got the mutex");


		pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointCloudIn = pcl::PointCloud<pcl::PointXYZRGB>::Ptr( new pcl::PointCloud<pcl::PointXYZRGB>() );
		pcl::fromROSMsg(*point_cloud, *pointCloudIn);

//		Eigen::Matrix4d objectTransform = Eigen::Matrix4d::Identity();

		// change reference frame of point cloud to point mean and oriented along principal axes
		Eigen::Vector4d mean;
		Eigen::Vector3d eigenvalues;
		Eigen::Matrix3d cov;
		Eigen::Matrix3d eigenvectors;
		pcl::computeMeanAndCovarianceMatrix( *pointCloudIn, cov, mean );
		pcl::eigen33( cov, eigenvectors, eigenvalues );





		/*
		 * Added comment to this misterious sign change:
		 * Assuming the eigenvectors of the object come in the camera frame of reference
		 * this means the unit vector along the Z axis (Eigen::Vector3d::UnitZ()) points away from the camera.
		 * The LAST eigenvector points upwards/downwards. If their dot product is positive
		 * means the eigenvector points downwards. This sign change would
		 * normalize it so that it always points downwards
		 *
		 */
		// z eigenvector
		if( Eigen::Vector3d(eigenvectors.col(0)).dot( Eigen::Vector3d::UnitZ() ) > 0.0 )
			eigenvectors.col(0) = (-eigenvectors.col(0)).eval();


		Eigen::Matrix4d objectTransform = Eigen::Matrix4d::Identity();
		objectTransform.block<3,1>(0,0) = eigenvectors.col(2);
		objectTransform.block<3,1>(0,1) = eigenvectors.col(1);
		objectTransform.block<3,1>(0,2) = eigenvectors.col(0);
		objectTransform.block<3,1>(0,3) = mean.block<3,1>(0,0);



		if( objectTransform.block<3,3>(0,0).determinant() < 0 ) {
			// x eigenvector (z axis)
			objectTransform.block<3,1>(0,0) = -objectTransform.block<3,1>(0,0);
		}

		/*
		 * -----------------------------
		 * set roll and pitch to 0,
		 * leave only the yaw as a free parameter
		 */
		//flatten_roll_pitch(objectTransform);
		/*
		 * ---------------------------
		 */


		eigenvectors.col(2) = objectTransform.block<3,1>(0,0); // x axis
		eigenvectors.col(1) = objectTransform.block<3,1>(0,1); // y axis
		eigenvectors.col(0) = objectTransform.block<3,1>(0,2); // z axis
		if(normalise_transform(eigenvectors,point_cloud)){
			// x eigenvector
			objectTransform.block<3,1>(0,0) = -objectTransform.block<3,1>(0,0);
			// y eigenvector
			objectTransform.block<3,1>(0,1) = -objectTransform.block<3,1>(0,1);
		}



		// transform from camera frame of reference to object's main axes frame of reference
		Eigen::Matrix4d objectTransformInv = objectTransform.inverse();

		//the MRSmap of the object is stored in the frame of reference of the objects' eigen axis
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr objectPointCloud = pcl::PointCloud<pcl::PointXYZRGB>::Ptr( new pcl::PointCloud<pcl::PointXYZRGB>() );
		pcl::transformPointCloud( *pointCloudIn, *objectPointCloud, (objectTransformInv).cast<float>() );

		objectPointCloud->sensor_origin_ = objectTransformInv.block<4,1>(0,3).cast<float>();
		objectPointCloud->sensor_orientation_ = Eigen::Quaternionf( objectTransformInv.block<3,3>(0,0).cast<float>() );
		
		treeNodeAllocator_->reset();
		map_ = boost::shared_ptr< MultiResolutionSurfelMap >( new MultiResolutionSurfelMap( max_resolution_, max_radius_, treeNodeAllocator_ ) );

		map_->params_.dist_dependency = dist_dep_;

		std::vector< int > pointIndices( objectPointCloud->points.size() );
		for( unsigned int i = 0; i < pointIndices.size(); i++ ) pointIndices[i] = i;
		map_->imageAllocator_ = imageAllocator_;
		map_->addPoints( *objectPointCloud, pointIndices );
		map_->octree_->root_->establishNeighbors();
		map_->evaluateSurfels();
		map_->buildShapeTextureFeatures();

		map_->save( map_folder_ + "/" + object_name_ + ".map" );

		if( init_frame_ != "" ) {

			ROS_INFO_STREAM( "Looking up transform to <init_frame>=" << init_frame_ <<" from <point_cloud->header.frame_id>="<<point_cloud->header.frame_id );

			try {

				tf::StampedTransform tf;
				tf_listener_->lookupTransform( init_frame_, point_cloud->header.frame_id, point_cloud->header.stamp, tf );
				Eigen::Affine3d init_frame_transform;
				tf::transformTFToEigen( tf, init_frame_transform );
				//obtains the transform of the object frame to the base_link frame of reference
				objectTransform = (init_frame_transform.matrix() * objectTransform).eval();


			}
				catch (tf::TransformException ex){
				ROS_ERROR("%s",ex.what());
			}


		}

		{

			Eigen::Quaterniond q( objectTransform.block<3,3>(0,0) );

			std::ofstream initPoseFile( map_folder_ + "/" + object_name_ + ".pose" );
			initPoseFile << "# x y z qx qy qz qw" << std::endl;
			initPoseFile << objectTransform(0,3) << " " << objectTransform(1,3) << " " << objectTransform(2,3) << " "
					 << q.x() << " " << q.y() << " " << q.z() << " "  << q.w() << std::endl;
			initPoseFile << "# init_pose: { position: { x: " << objectTransform(0,3) << ", y: " << objectTransform(1,3) << ", z: " << objectTransform(2,3)
					<< " }, orientation: { x: " << q.x() << ", y: " << q.y() << ", z: " << q.z() << ", w: " << q.w() << " } } }" << std::endl;
		}

		cloudv = pcl::PointCloud< pcl::PointXYZRGB >::Ptr( new pcl::PointCloud< pcl::PointXYZRGB >() );
		cloudv->header.frame_id = object_name_;
		map_->visualize3DColorDistribution( cloudv, -1, -1, false );


		Eigen::Quaterniond q( objectTransform.block<3,3>(0,0) );

		object_tf_.setIdentity();
		object_tf_.setRotation( tf::Quaternion( q.x(), q.y(), q.z(), q.w() ) );
		object_tf_.setOrigin( tf::Vector3( objectTransform(0,3), objectTransform(1,3), objectTransform(2,3) ) );

		//the object tf is from the camera frame of reference to the object's
		object_tf_.stamp_ = point_cloud->header.stamp;
		object_tf_.child_frame_id_ = object_name_;
		object_available = true; //the object_tf_ member variable now matches the last requested snapshot

		if( init_frame_ == "" ) {
			object_tf_.frame_id_ = point_cloud->header.frame_id;
		}
		else
			object_tf_.frame_id_ = init_frame_;

		first_publication_time = ros::Time::now();
		ROS_INFO_STREAM("first_publication_time="<<first_publication_time<<" do_publish_tf_="<<do_publish_tf_);
		if(do_publish_tf_){
			//ROS_INFO_STREAM("object_tf_.frame_id_="<<object_tf_.frame_id_);
			ROS_INFO_STREAM("> Snapshot map :dataCallback() publishing transform object_tf_.frame_id_ (init_frame_)=" << object_tf_.frame_id_ << " child="<< object_tf_.child_frame_id_<<std::endl);
//			std::cout <<"Press enter to continue..."<<std::endl;
//			std::cin.get();
			tf_broadcaster.sendTransform( object_tf_ );

		}

		sub_cloud_.shutdown();

		create_map_ = false;

		responseId_++;
		object_available = true;
		object_mutex.unlock();

		ROS_INFO("dataCallback released the mutex");

	}