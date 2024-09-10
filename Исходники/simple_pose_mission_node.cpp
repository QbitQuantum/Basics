int main(int argc, char **argv)
{
    const double radius = 0.5; // 0.5
    const double pitch_step = 0.2;
    const int circle_points = 6; // 6
    const int circle_rings = 3; // 3
    const double plan_time = 5;
    const int plan_retry = 1;
    //const int pose_id_max = circle_points * 3;
    const ros::Duration wait_settle(1.0);
    const ros::Duration wait_camera(0.5);
    const ros::Duration wait_notreached(3.0);
    const ros::Duration wait_reset(30.0);

    const std::string planning_group = "bumblebee"; //robot, bumblebee
    const std::string end_effector = "tool_flange"; // bumblebee_cam1, tool_flange

    const std::string plannerId = "PRMkConfigDefault";
    const std::string frame_id = "base_link";

    ros::init (argc, argv, "simple_pose_mission");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle node_handle;
    ros::Publisher cameratate_pub = node_handle.advertise<group4_msgs::PointCloudPose>("/robot_rx60b/camerapose", 5);
    ros::Publisher markerPublisher = node_handle.advertise<visualization_msgs::MarkerArray>("/simple_pose_mission/poses", 10);

    tf::TransformListener listener;

    // Marker
    MarkerPose marker("object_center");
    addObjectCenterMarker(marker);

    // Robot and scene
    moveit::planning_interface::MoveGroup group(planning_group);
    group.setPlannerId(plannerId);
    group.setPoseReferenceFrame(frame_id);
    //group.setWorkspace(-1.5,-1.5,1.5,1.5,0,1);
    group.setGoalTolerance(0.01f);
    group.setPlanningTime(plan_time);

    group4_msgs::PointCloudPose msg;
    msg.header.frame_id = frame_id;

    tf::Pose object_center = marker.getPose("object_center");
    NumberedPoses poses = generatePoses(object_center, circle_points, circle_rings, pitch_step, radius);
    NumberedPoses::iterator poses_itt;
    bool poses_updated = true;


    while (ros::ok())
    {
        bool success;

        if (poses_updated || poses_itt == poses.end())
        {
            poses_itt = poses.begin();
            poses_updated = false;
        }

        NumberedPose numbered_pose = *poses_itt;

        visualizePoses(poses, frame_id,markerPublisher, numbered_pose.pose_id);


        ROS_INFO("Moving to pose %i of %i", numbered_pose.pose_id, numbered_pose.pose_id_max);



        tf::StampedTransform transform;
        try{
          listener.lookupTransform("/bumblebee_cam1", "/tool_flange",
                                   ros::Time(0), transform);
        }
        catch (tf::TransformException ex){
          ROS_ERROR("%s",ex.what());
        }

        tf::Pose p = numbered_pose.pose_tf * transform;
        geometry_msgs::Pose desired_pose = tfPoseToGeometryPose(p);
        group.setPoseTarget(desired_pose, end_effector);

        success = false;
        for (int itry = 0; itry < plan_retry; itry++)
        {

            group.setStartStateToCurrentState();
            wait_notreached.sleep();
            success = group.move();
            if (success)
                break;
            else
                ROS_INFO("Plan unsuccessfull.. Retrying! (%i)", itry);
        }

        if (true)
        {

            wait_settle.sleep();

            geometry_msgs::PoseStamped carmine_pose = group.getCurrentPose("camera_link");
            geometry_msgs::PoseStamped bumblebee_pose_left = group.getCurrentPose("bumblebee_cam1");
            geometry_msgs::PoseStamped bumblebee_pose_right = group.getCurrentPose("bumblebee_cam2");

            msg.header.stamp = ros::Time::now();
            msg.pose_id.data = numbered_pose.pose_id;
            msg.pose_id_max.data = numbered_pose.pose_id_max;
            msg.spin_center_pose = tfPoseToGeometryPose(object_center);
            msg.carmine_pose = carmine_pose.pose;
            msg.bumblebee_pose_left = bumblebee_pose_left.pose;
            msg.bumblebee_pose_right = bumblebee_pose_right.pose;

            cameratate_pub.publish(msg);

            ROS_INFO("Waiting %f seconds for camera.", wait_camera.toSec());
            wait_camera.sleep();
        }

        if (poses_itt == poses.end())
        {
            ROS_INFO("Last pose reached. Waiting %f seconds before resetting", wait_reset.toSec());
            poses_itt = poses.begin();
            wait_reset.sleep();
        }
        else
            poses_itt++;

    }
    group.stop();
    return 0;
}