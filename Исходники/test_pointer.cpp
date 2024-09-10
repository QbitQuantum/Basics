int do_inits() {
    Eigen::Matrix3d R;
    Eigen::Vector3d nvec, tvec, bvec, tip_pos;
    bvec << 0, 0, 1; //default for testing: gripper points "down"
    nvec << 1, 0, 0;
    tvec = bvec.cross(nvec);
    R.col(0) = nvec;
    R.col(1) = tvec;
    R.col(2) = bvec;
    g_des_gripper_affine1.linear() = R;
    tip_pos << -0.15, -0.03, 0.07;
    g_des_gripper_affine1.translation() = tip_pos; //will change this, but start w/ something legal

    //hard-coded camera-to-base transform, useful for simple testing/debugging
    g_affine_lcamera_to_psm_one.translation() << -0.155, -0.03265, 0.0;
    nvec << -1, 0, 0;
    tvec << 0, 1, 0;
    bvec << 0, 0, -1;
    //Eigen::Matrix3d R;
    R.col(0) = nvec;
    R.col(1) = tvec;
    R.col(2) = bvec;
    g_affine_lcamera_to_psm_one.linear() = R;

    g_q_vec1_start.resize(7);
    g_q_vec1_goal.resize(7);
    g_q_vec2_start.resize(7);
    g_q_vec2_goal.resize(7);

    g_des_gripper1_wrt_base = g_affine_lcamera_to_psm_one.inverse() * g_des_gripper_affine1;
    g_ik_solver.ik_solve(g_des_gripper1_wrt_base); // compute IK:
    g_q_vec1_goal = g_ik_solver.get_soln();
    g_q_vec1_start = g_q_vec1_goal;
    g_q_vec2_start << 0, 0, 0, 0, 0, 0, 0; //just put gripper 2 at home position
    g_q_vec2_goal << 0, 0, 0, 0, 0, 0, 0;
    //repackage q's into a trajectory;
    //populate a goal message for action server; 
    // initialize with 2 poses that are identical
    g_trajectory_point1.positions.clear();
    g_trajectory_point2.positions.clear();
    //resize these:
    for (int i=0;i<14;i++)  {
        g_trajectory_point1.positions.push_back(0.0); 
        g_trajectory_point2.positions.push_back(0.0); 
    }
        
    for (int i = 0; i < 7; i++) { 
        g_trajectory_point1.positions[i] = g_q_vec1_start[i];
        g_trajectory_point1.positions[i + 7] = g_q_vec2_start[i];
        //should fix up jaw-opening values...do this later
    }

    g_trajectory_point1.time_from_start = ros::Duration(0.0);
    g_trajectory_point2.time_from_start = ros::Duration(2.0);


    g_des_trajectory.points.clear(); // can clear components, but not entire trajectory_msgs
    g_des_trajectory.joint_names.clear();
    //    des_trajectory.joint_names.push_back("right_s0"); //yada-yada should fill in names
    g_des_trajectory.header.stamp = ros::Time::now();

    g_des_trajectory.points.push_back(g_trajectory_point1); // first point of the trajectory 
    g_des_trajectory.points.push_back(g_trajectory_point2);

    // copy traj to goal:
    g_goal.trajectory = g_des_trajectory;
    g_got_new_pose = true; //send robot to start pose
    
     ROS_INFO("getting transforms from camera to PSMs");
    tf::TransformListener tfListener;
    tf::StampedTransform tfResult_one, tfResult_two;
    bool tferr = true;
    int ntries = 0;
    ROS_INFO("waiting for tf between base and right_hand...");
    while (tferr) {
        if (ntries > 5) break; //give up and accept default after this many tries
        tferr = false;
        try {
            //The direction of the transform returned will be from the target_frame to the source_frame. 
            //Which if applied to data, will transform data in the source_frame into the target_frame. See tf/CoordinateFrameConventions#Transform_Direction
            tfListener.lookupTransform("left_camera_optical_frame", "one_psm_base_link", ros::Time(0), tfResult_one);
            //tfListener.lookupTransform("left_camera_optical_frame", "two_psm_base_link", ros::Time(0), tfResult_two);
        } catch (tf::TransformException &exception) {
            ROS_WARN("%s", exception.what());
            tferr = true;
            ros::Duration(0.5).sleep(); // sleep for half a second
            ros::spinOnce();
            ntries++;
        }
    }
    //default transform: need to match this up to camera calibration!
    if (tferr) {
        g_affine_lcamera_to_psm_one.translation() << -0.155, -0.03265, 0.0;
        Eigen::Vector3d nvec, tvec, bvec;
        nvec << -1, 0, 0;
        tvec << 0, 1, 0;
        bvec << 0, 0, -1;
        Eigen::Matrix3d R;
        R.col(0) = nvec;
        R.col(1) = tvec;
        R.col(2) = bvec;
        g_affine_lcamera_to_psm_one.linear() = R;
        g_affine_lcamera_to_psm_one.linear() = R;
        g_affine_lcamera_to_psm_one.translation() << 0.145, -0.03265, 0.0;
        ROS_WARN("using default transform");
    } else {

        ROS_INFO("tf is good");

        //affine_lcamera_to_psm_one is the position/orientation of psm1 base frame w/rt left camera link frame
        // need to extend this to camera optical frame
        g_affine_lcamera_to_psm_one = transformTFToEigen(tfResult_one);
        //affine_lcamera_to_psm_two = transformTFToEigen(tfResult_two);
    }
    ROS_INFO("transform from left camera to psm one:");
    cout << g_affine_lcamera_to_psm_one.linear() << endl;
    cout << g_affine_lcamera_to_psm_one.translation().transpose() << endl;
    //ROS_INFO("transform from left camera to psm two:");
    //cout << affine_lcamera_to_psm_two.linear() << endl;
    //cout << affine_lcamera_to_psm_two.translation().transpose() << endl;    
    
    
    ROS_INFO("done w/ inits");

    return 0;
    
}