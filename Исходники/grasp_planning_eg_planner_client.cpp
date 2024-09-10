int run(int argc, char **argv)
{
    if (argc < 3)
    {
        printHelp(argv[0]);
        return 0;
    }

    std::string output_path;
    if (argc >= 4)
    {
        output_path=std::string(argv[3]);    
        if (!makeDirectoryIfNeeded(output_path))
        {
            PRINTERROR("Could not create directory "<<output_path);
            return 0;
        }
    }
        
    if (output_path.empty())
    {
        PRINTWARN("No output path configured, will print results on screen only.");
        printHelp(argv[0]);
    }

    const std::string robotArg(argv[1]);
    const std::string objectArg(argv[2]);

    PRINTMSG("Planning for robot ID=" << robotArg << " to grasp object ID=" << objectArg);

    // TODO parameterize this
    std::string egPlanningTopic = "graspit_eg_planning";

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<manipulation_msgs::GraspPlanning>(egPlanningTopic);

    // Should use a client here to query the database for information about the
    // object type. For now, object type information is not used in the planning request,
    // as the service looks up the object type itself. So we can leave these on arbitrary values.
    object_recognition_msgs::ObjectType dbModelType;
    dbModelType.key =  "NotAvailabeYet";
    dbModelType.db = "SimpleGraspItDatabase";

    // Here we can set a different pose to put the object at in the current
    // graspit world. If this the reference frame is "0",
    // it uses the object's current pose in the world. If it is "1",
    // we will use the pose specified in the following field.
    geometry_msgs::PoseStamped modelPose;
    modelPose.header.frame_id = "0";

    /*    modelPose.header.frame_id="1";
          modelPose.pose.orientation.w=1;
          modelPose.pose.position.x=100;
     */

    household_objects_database_msgs::DatabaseModelPose dbModel;
    dbModel.model_id = atoi(objectArg.c_str());  // TODO move away from atoi at some stage
    dbModel.type = dbModelType;
    dbModel.pose = modelPose;
    dbModel.confidence = 1;
    dbModel.detector_name = "manual_detection";


    manipulation_msgs::GraspableObject obj;
    // the reference frame could be one that is relative to all fields (e.g. cluster and
    // all potential models). However at the moment, the graspit planner only supports
    // the global frame (the graspit origin). No tf transforms are considered in the
    // GraspIt planner service yet.
    obj.reference_frame_id = dbModel.pose.header.frame_id;
    obj.potential_models.push_back(dbModel);
    // obj.cluster = we will not provide a point cloud
    // obj.region = and not the SceneRegion along with it either.
    // obj.collision_name = could think about whether providing this as parameter too

    manipulation_msgs::GraspPlanning srv;
    srv.request.arm_name = robotArg;
    srv.request.target = obj;
    srv.request.collision_object_name = obj.collision_name;
    // srv.request.collision_support_surface_name = will not provide this here
    // srv.request.grasps_to_evaluate = no grasps to evaluate with this client
    // srv.request.movable_obstacles = this is not supported by this client

    if (!client.call(srv))
    {
        PRINTERROR("Failed to call service");
        return 1;
    }

    if (srv.response.error_code.value != manipulation_msgs::GraspPlanningErrorCode::SUCCESS)
    {
        PRINTERROR("Could do the grasp planning. Error code " << srv.response.error_code.value);
        return 1;
    }

    PRINTMSG("Successfully finished grasp planning. Have " << srv.response.grasps.size() << " resulting grasps.");
    std::vector<manipulation_msgs::Grasp>::iterator it;
    int i=1;
    for (it = srv.response.grasps.begin(); it != srv.response.grasps.end(); ++it)
    {
        if (!output_path.empty())
        {
            std::stringstream filename;
            filename<<output_path<<"/Grasp_"<<i<<".msg";
            std::stringstream filename_txt;
            filename_txt<<output_path<<"/Grasp_"<<i<<"_string.msg";
            ++i;
            if (!saveToFile(*it, filename.str(), true))
            {
                PRINTERROR("Could not save to file "<<filename.str());
                continue;
            }
            saveToFile(*it, filename_txt.str(), false);
        }
        else
        {
            PRINTMSG(*it);
        }
    }
    return 0;
}