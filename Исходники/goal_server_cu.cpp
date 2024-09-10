int main(int argc, char** argv) 
{
    ros::init(argc, argv, "goal_server_cu");
    ros::NodeHandle nh;
    ros::Rate loop_rate(100);
    
     // load globals from parameter server
    double param_input;
    bool given_goal = false;
    if(ros::param::get("goal_server_cu/goal_pose_x_init", param_input)) 
    {
      goal_pose_x_init = (float)param_input;
      given_goal = true;
    }
    if(ros::param::get("goal_server_cu/goal_pose_y_init", param_input)) 
    {
      goal_pose_y_init = (float)param_input;
      given_goal = true;
    }
    if(ros::param::get("goal_server_cu/goal_pose_z_init", param_input)) 
    {
      goal_pose_z_init = (float)param_input;                                 // z is basically unused
      given_goal = true;
    }
    if(ros::param::get("goal_server_cu/goal_pose_theta_init", param_input)) 
    {
      goal_pose_theta_init = (float)param_input;
      given_goal = true;
    }
    
    // if the goal was sent in, then init goal pose
    if(given_goal)
    {
      printf("goal recieved at startup: [%f %f %f] \n", goal_pose_x_init, goal_pose_y_init, goal_pose_theta_init);
      goal = make_pose(goal_pose_x_init, goal_pose_y_init, goal_pose_z_init, goal_pose_theta_init);
    }
    
    // set up publisher
    goal_pub = nh.advertise<geometry_msgs::PoseStamped>("/cu/goal_cu", 1);
    
    // set up subscribers
    reset_goal_sub = nh.subscribe("/cu/reset_goal_cu", 1, reset_goal_callback);
    
    // set up service servers
    get_goal_srv = nh.advertiseService("/cu/get_goal_cu", get_goal_callback);
    
    while (ros::ok()) 
    {
      //printf(" This is the goal server \n");
      //print_pose(goal);
        
      publish_goal();
        
      ros::spinOnce();
      loop_rate.sleep();
    }
    
    
    // destroy publisher
    goal_pub.shutdown();
    reset_goal_sub.shutdown();
    get_goal_srv.shutdown();
        
    destroy_pose(goal);
}