int main(int argc, char** argv) 
{
  ros::init(argc, argv, "base_planner_cu");
  ros::NodeHandle nh;
  ros::Rate loop_rate(100);
    
  // load globals from parameter server
  double param_input;
  bool bool_input;
  if(ros::param::get("base_planner_cu/obstacle_cost", param_input))
    OBSTACLE_COST = param_input;                                                   // the cost of an obstacle
  if(ros::param::get("base_planner_cu/robot_radius", param_input)) 
    robot_radius = param_input;                                                    //(m)
  if(ros::param::get("base_planner_cu/safety_distance", param_input)) 
    safety_distance = param_input;                                                 //(m), distance that must be maintained between robot and obstacles
  if(ros::param::get("base_planner_cu/better_path_ratio", param_input)) 
    old_path_discount = param_input;                                               // if (current path length)*old_path_discount < (old path length) < (current path length)/old_path_discount, then stick with the old path
  if(ros::param::get("base_planner_cu/replan_jump", param_input)) 
    MAX_POSE_JUMP = param_input;                                                   //(map grids) after which it is easer to replan from scratch
  if(ros::param::get("base_planner_cu/using_extra_safety_distance", bool_input)) 
    high_cost_safety_region = bool_input;                                          // true: dilate obstacles by an extra extra_dilation but instad of lethal, multiply existing cost by extra_dilation_mult
  if(ros::param::get("base_planner_cu/extra_safety_distance", param_input)) 
    extra_dilation = param_input;                                                  //(m)

  // print data about parameters
  printf("obstacle cost: %f, robot radius: %f, safety_distance: %f, extra_safety_distance: %f, \nbetter_path_ratio: %f, replan_jump: %f \n", OBSTACLE_COST, robot_radius, safety_distance, extra_dilation, old_path_discount, MAX_POSE_JUMP);
  if(high_cost_safety_region)
    printf("using extra safety distance \n");
  else
    printf("not using extra safety distance \n");
  
  // wait until the map service is provided (we need its tf /world_cu -> /map_cu to be broadcast)
  ros::service::waitForService("/cu/get_map_cu", -1);
  
  // set up ROS topic subscriber callbacks
  pose_sub = nh.subscribe("/cu/pose_cu", 1, pose_callback);
  goal_sub = nh.subscribe("/cu/goal_cu", 1, goal_callback);
  map_changes_sub = nh.subscribe("/cu/map_changes_cu", 10, map_changes_callback);
    
  // set up ROS topic publishers
  global_path_pub = nh.advertise<nav_msgs::Path>("/cu/global_path_cu", 1);
  system_update_pub = nh.advertise<std_msgs::Int32>("/cu/system_update_cu", 10);
  
  // spin ros once
  ros::spinOnce();
  loop_rate.sleep(); 
  
  // wait for a map
  while(!load_map() && ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep(); 
  }
  
  // init map
  buildGraphAndMap(raw_map->height, raw_map->width);
  populate_map_from_raw_map();
  
  // wait until we have a goal and a robot pose (these arrive via callbacks)
  while((goal_pose == NULL || robot_pose == NULL) && ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();    
  }
    
  // initialize search and related data structures (this calculates initial cost field)
  if(ros::ok())
  {
    initialize_search(true);  // true := use old map, (raw_map was populated in a pre-processing step)
    new_goal = false; 
    ros::spinOnce();  // check in on callbacks
    
    // added to give map changes a chance to propogate before first real search
    ros::Rate one_time_sleep(2);
    one_time_sleep.sleep();
    
    ros::spinOnce();  // check in on callbacks
  }
  
  // main planning loop
  int lr, ud;
  int time_counter = 0;
  MapPath* old_path = NULL;
  while (ros::ok()) 
  {
    while(change_token_used)
      {printf("change token used, main \n");}
    change_token_used = true;

    time_counter++;
    //printf(" This is the base planner %d\n", time_counter); // heartbeat for debugging

    load_goal();
    
    if(new_goal || reload_map)
    {  
      if(reload_map)
      {
        printf("reinitializing map and searchtree \n");
        
        change_token_used = false;
        // wait for a map
        while(!load_map() && ros::ok())
        {
          ros::spinOnce();
          loop_rate.sleep(); 
        }
        change_token_used = true;
        
        initialize_search(false); // false := reset map based in what is in raw_map (raw_map was just re-populated with info from the map server)
      }
      else // new_goal
      {
        printf("reinitializing search tree, reusing map \n");
        initialize_search(true); // true := reuse the old map
      }
      
      new_goal = false;   
      reload_map = false;
 
      if(old_path != NULL)
      {
        deleteMapPath(old_path);
        old_path = NULL;
      }
      
      // get best estimate of pose
      while(!load_pose())
      {
        // wait for most up to date pose
      }
      printf(" recieved pose via service \n");       
    }
    else
      load_pose(); // if services lag then this is a bad idea, but have had problems on netbooks never getting new pose
    
    // find the new exact coordinates of the robot 
    robot_pos_x = robot_pose->x/raw_map->resolution; // need to add global offset ability
    if(robot_pos_x > raw_map->width)
      robot_pos_x = raw_map->width;
    if(robot_pos_x < 0)
      robot_pos_x = 0;
   
    robot_pos_y = robot_pose->y/raw_map->resolution; // need to add global offset ability
    if(robot_pos_y > raw_map->width)
      robot_pos_y = raw_map->width;
    if(robot_pos_y < 0)
      robot_pos_y = 0;  
 
        
    // do replanning, note that we need to make sure that all neighboring nodes of the cell(s) containing the robot are updated 
    //printf("replanning %d \n", time_counter);
    if(robot_pos_x == (double)((int)robot_pos_x)) // then on a vertical edge, need to plan to nodes on cells to the left and right of the robot
      lr = -1;
    else //only need to plan to nodes on cells with x == int_pos_x
      lr = 0;
    
    while(lr < 2)
    { 
      if(robot_pos_y == (double)((int)robot_pos_y)) // then on a horizontal edge, need to plan to nodes on cells to the top and bottom of the robot
        ud = -1;
      else //only need to plan to nodes on cells with y == int_pos_y
        ud = 0;

      if((int)robot_pos_x + lr < 0 || (int)robot_pos_x + lr > WIDTH)
      {
        lr++;
        continue;
      }

      while(ud < 2)
      { 
        if((int)robot_pos_y + ud < 0 || (int)robot_pos_y + ud > HEIGHT)
        {
          ud++;
          continue;
        }

        s_start = &graph[(int)robot_pos_y + ud][(int)robot_pos_x + lr];
         
        computeShortestPath();  // this updates the cost field to this node
        ud++;  
      }
      lr++;
    }  
       
    // extract the path, this will be used to figure out where to move the robot  
    //printf("extract path1 %d \n", time_counter);
    MapPath* pathToGoalWithLookAhead = extractPathOneLookahead();
    double path1_max_single_grid;
    double path1_cost = calculatePathCost(pathToGoalWithLookAhead, path1_max_single_grid);

    //printf("extract path2 %d \n", time_counter);
    MapPath* pathToGoalMine = extractPathMine(0); // this uses gradient descent where possible
    double path2_max_single_grid;
    double path2_cost = calculatePathCost(pathToGoalMine, path2_max_single_grid);

    
    double old_path_cost = LARGE;
    double old_path_max_single_grid;
    if(old_path != NULL)
      old_path_cost = calculatePathCost(old_path, old_path_max_single_grid);
    
    change_token_used = false;

    // use better path of the two to move the robot (or retain the old path if it is still better)
    if(old_path != NULL && path1_cost*old_path_discount <= old_path_cost && old_path_cost <= path1_cost/old_path_discount
                        && path2_cost*old_path_discount <= old_path_cost && old_path_cost <= path2_cost/old_path_discount 
                        && old_path_max_single_grid < OBSTACLE_COST)
    {
      publish_global_path(old_path);
      //printf("old path is about the same or better %d [%f vs %f] %f \n", time_counter, old_path_cost, (path1_cost+path2_cost)/2, old_path_max_single_grid);   
        
      deleteMapPath(pathToGoalMine);  
      deleteMapPath(pathToGoalWithLookAhead);
    }
    else if(path1_cost < path2_cost && path1_max_single_grid < OBSTACLE_COST)
    {         
      publish_global_path(pathToGoalWithLookAhead); 
      //printf("path1 is better %d %f %f\n", time_counter, path1_cost, path1_max_single_grid);

      
      if(old_path != NULL)
      {
        deleteMapPath(old_path);
        old_path = NULL;
      }
      
      old_path = pathToGoalWithLookAhead;
      deleteMapPath(pathToGoalMine);
    }
    else if(path2_max_single_grid < OBSTACLE_COST)
    {
      publish_global_path(pathToGoalMine);  
      //printf("path2 is better %d %f %f\n", time_counter, path2_cost, path2_max_single_grid);
      
      if(old_path != NULL)
      {
        deleteMapPath(old_path);
        old_path = NULL;
      }
      
      old_path = pathToGoalMine;
      deleteMapPath(pathToGoalWithLookAhead);
    }
    else // all paths go through obstacles
    {
     printf("Base Planner: No safe path exists to goal %f %f %f\n", old_path_cost, path1_cost, path2_cost);   
     publish_system_update(1);   
     reload_map = true;
    }

    ros::spinOnce();
    loop_rate.sleep();
    
    //printf("done %d \n", time_counter);
  }
    
  if(old_path != NULL)
    deleteMapPath(old_path);
  
  pose_sub.shutdown();
  goal_sub.shutdown();
  map_changes_sub.shutdown();
  global_path_pub.shutdown();
  system_update_pub.shutdown();
    
  destroy_pose(robot_pose);
  destroy_pose(goal_pose);
    
  cpDeleteHeap(primaryCellPathHeap);
  cpDeleteHeap(secondaryCellPathHeap);
  deleteHeap();   
  deleteGraphAndMap();
}