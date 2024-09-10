void CartMoveActionServer::executeCB(const actionlib::SimpleActionServer<cwru_action::cart_moveAction>::GoalConstPtr& goal) {

    ROS_INFO("in executeCB of CartMoveActionServer");
   cart_result_.err_code=0;
   cart_move_as_.isActive();
   //unpack the necessary info:
   gripper_ang1_ = goal->gripper_jaw_angle1;
   gripper_ang2_ = goal->gripper_jaw_angle2;
   arrival_time_ = goal->move_time;
   // interpret the desired gripper poses:
   geometry_msgs::PoseStamped des_pose_gripper1 = goal->des_pose_gripper1;
   geometry_msgs::PoseStamped des_pose_gripper2 = goal->des_pose_gripper2;
   // convert the above to affine objects:
   des_gripper1_affine_wrt_lcamera_ = transformPoseToEigenAffine3d(des_pose_gripper1.pose);
   cout<<"gripper1 desired pose;  "<<endl;
   cout<<des_gripper1_affine_wrt_lcamera_.linear()<<endl;
   cout<<"origin: "<<des_gripper1_affine_wrt_lcamera_.translation().transpose()<<endl;

   des_gripper2_affine_wrt_lcamera_ = transformPoseToEigenAffine3d(des_pose_gripper2.pose);
   cout<<"gripper2 desired pose;  "<<endl;
   cout<<des_gripper2_affine_wrt_lcamera_.linear()<<endl;
   cout<<"origin: "<<des_gripper2_affine_wrt_lcamera_.translation().transpose()<<endl;

   //do IK to convert these to joint angles:
    //Eigen::VectorXd q_vec1,q_vec2;
    Vectorq7x1 q_vec1,q_vec2;
    q_vec1.resize(7);
    q_vec2.resize(7);

    
    trajectory_msgs::JointTrajectory des_trajectory; // an empty trajectory 
    des_trajectory.points.clear(); // can clear components, but not entire trajectory_msgs
    des_trajectory.joint_names.clear(); //could put joint names in...but I assume a fixed order and fixed size, so this is unnecessary
    // if using wsn's trajectory streamer action server
    des_trajectory.header.stamp = ros::Time::now();

    trajectory_msgs::JointTrajectoryPoint trajectory_point; //,trajectory_point2; 
    trajectory_point.positions.resize(14);
    
    ROS_INFO("\n");
    ROS_INFO("stored previous command to gripper one: ");
    cout<<gripper1_affine_last_commanded_pose_.linear()<<endl;
    cout<<"origin: "<<gripper1_affine_last_commanded_pose_.translation().transpose()<<endl;
   

    // first, reiterate previous command:
    // this could be easier, if saved previous joint-space trajectory point...
    des_gripper_affine1_ = affine_lcamera_to_psm_one_.inverse()*gripper1_affine_last_commanded_pose_; //previous pose
    ik_solver_.ik_solve(des_gripper_affine1_); //convert desired pose into equiv joint displacements
    q_vec1 = ik_solver_.get_soln(); 
    q_vec1(6) = last_gripper_ang1_; // include desired gripper opening angle
    
    
    des_gripper_affine2_ = affine_lcamera_to_psm_two_.inverse()*gripper2_affine_last_commanded_pose_; //previous pose
    ik_solver_.ik_solve(des_gripper_affine2_); //convert desired pose into equiv joint displacements
    q_vec2 = ik_solver_.get_soln(); 
    cout<<"q_vec1 of stored pose: "<<endl;
    for (int i=0;i<6;i++) {
        cout<<q_vec1[i]<<", ";
    }
    cout<<endl;
    q_vec2(6) = last_gripper_ang2_; // include desired gripper opening angle
    
       for (int i=0;i<7;i++) {
            trajectory_point.positions[i] = q_vec1(i);
            trajectory_point.positions[i+7] = q_vec2(i);  
        }
    cout<<"start traj pt: "<<endl;
    for (int i=0;i<14;i++) {
        cout<<trajectory_point.positions[i]<<", ";
    }
    cout<<endl;
      trajectory_point.time_from_start = ros::Duration(0.0); // start time set to 0
    // PUSH IN THE START POINT:
      des_trajectory.points.push_back(trajectory_point);            

    // compute and append the goal point, in joint space trajectory:
    des_gripper_affine1_ = affine_lcamera_to_psm_one_.inverse()*des_gripper1_affine_wrt_lcamera_;
    ROS_INFO("desired gripper one location in base frame: ");
    cout<<"gripper1 desired pose;  "<<endl;
    cout<<des_gripper_affine1_.linear()<<endl;
    cout<<"origin: "<<des_gripper_affine1_.translation().transpose()<<endl;

    ik_solver_.ik_solve(des_gripper_affine1_); //convert desired pose into equiv joint displacements
    q_vec1 = ik_solver_.get_soln(); 
    q_vec1(6) = gripper_ang1_; // include desired gripper opening angle

    des_gripper_affine2_ = affine_lcamera_to_psm_two_.inverse()*des_gripper2_affine_wrt_lcamera_;
    ik_solver_.ik_solve(des_gripper_affine2_); //convert desired pose into equiv joint displacements
    q_vec2 = ik_solver_.get_soln();  
    cout<<"q_vec1 of goal pose: "<<endl;
    for (int i=0;i<6;i++) {
        cout<<q_vec1[i]<<", ";
    }
    cout<<endl;
    q_vec2(6) = gripper_ang2_;
        for (int i=0;i<7;i++) {
            trajectory_point.positions[i] = q_vec1(i);
            trajectory_point.positions[i+7] = q_vec2(i);  
        }
      trajectory_point.time_from_start = ros::Duration(arrival_time_);
   cout<<"goal traj pt: "<<endl;
    for (int i=0;i<14;i++) {
        cout<<trajectory_point.positions[i]<<", ";
    }
    cout<<endl;
      des_trajectory.points.push_back(trajectory_point);

    js_goal_.trajectory = des_trajectory;

    // Need boost::bind to pass in the 'this' pointer
  // see example: http://library.isr.ist.utl.pt/docs/roswiki/actionlib_tutorials%282f%29Tutorials%282f%29Writing%2820%29a%2820%29Callback%2820%29Based%2820%29Simple%2820%29Action%2820%29Client.html
  //  ac.sendGoal(goal,
  //              boost::bind(&MyNode::doneCb, this, _1, _2),
  //              Client::SimpleActiveCallback(),
  //              Client::SimpleFeedbackCallback());

    js_action_client_.sendGoal(js_goal_, boost::bind(&CartMoveActionServer::js_doneCb_,this,_1,_2)); // we could also name additional callback functions here, if desired
    //    action_client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb); //alt--more callback funcs possible
    
    double t_timeout=arrival_time_+2.0; //wait 2 sec longer than expected duration of move
    
    bool finished_before_timeout = js_action_client_.waitForResult(ros::Duration(t_timeout));
    //bool finished_before_timeout = action_client.waitForResult(); // wait forever...
    if (!finished_before_timeout) {
        ROS_WARN("joint-space interpolation result is overdue ");
    } else {
        ROS_INFO("finished before timeout");
    }

    ROS_INFO("completed callback" );
    cart_move_as_.setSucceeded(cart_result_); // tell the client that we were successful acting on the request, and return the "result" message 
    
    //let's remember the last pose commanded, so we can use it as start pose for next move
    gripper1_affine_last_commanded_pose_ = des_gripper1_affine_wrt_lcamera_;
    gripper2_affine_last_commanded_pose_ = des_gripper2_affine_wrt_lcamera_;    
    //and the jaw opening angles:
    last_gripper_ang1_=gripper_ang1_;
    last_gripper_ang2_=gripper_ang2_;
}