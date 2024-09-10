/** MAIN NODE **/
int
main (int argc, char** argv)
{
        // Initialize ROS
        ros::init (argc, argv, "comau_tf_follower");
        ros::NodeHandle nh;
        listener = new tf::TransformListener ();
        tf_broadcaster = new tf::TransformBroadcaster();

        // PUB & SUB
        ros::Subscriber comau_tf_follower = nh.subscribe( "lar_visionsystem/comau_tf_follower",1,parseCommand );
        ros::Subscriber joy_sub = nh.subscribe ("joy", 1, joy_cb);
        ros::Subscriber markers_list_sub = nh.subscribe ("lar_visionsystem/markers_list", 1, markers_list_cb);
        ros::Subscriber comau_sub = nh.subscribe ("lar_comau/comau_full_state_publisher", 1, comau_cb);
        ros::Publisher comau_cartesian_controller = nh.advertise<lar_comau::ComauCommand>("lar_comau/comau_cartesian_controller", 1);
        ros::Publisher marker_approach = nh.advertise<lar_visionsystem::MarkerApproachCommand>("lar_visionsystem/marker_approach", 1);




        //Initialize Joystick
        {
                joystick_speed_max.x = joystick_speed_max.y = joystick_speed_max.z =  0.5f;
                joystick_speed.x = joystick_speed.y = joystick_speed.z = 0.0f;

                joystick_angular_speed_max.x = joystick_angular_speed_max.y = joystick_angular_speed_max.z =  M_PI/1000.0f;
                joystick_angular_speed.x = joystick_angular_speed.y = joystick_angular_speed.z = 0.0f;

                joystick_set_point.position.x = 1000.0f;
                joystick_set_point.position.y = 0.0f;
                joystick_set_point.position.z = 0.0f;

                KDL::Rotation joystick_rotation;
                MathUtils::getRotationsByName("",joystick_rotation);
                MathUtils::poseToKDLRotation(joystick_set_point,joystick_rotation,true);
        }
        //END Initialize Joystick


        //Initialize Marker Approach Pose
        {
                follow_target_approach_pose.position.x =-0.025f;
                follow_target_approach_pose.position.y = -0.085f;
                follow_target_approach_pose.position.z = 0.7f;
                KDL::Rotation follow_rotation;
                MathUtils::getRotationsByName("down_x",follow_rotation);
                MathUtils::poseToKDLRotation(follow_target_approach_pose,follow_rotation,true);
        }

        //Initialize Gripper
        gripper_serial = open(gripper_usb_name.c_str(), O_RDWR | O_NOCTTY |O_NDELAY );
        gripper_status =gripper_serial>=0;
        tcgetattr(gripper_serial, &gripper_serial_cfg);
        cfsetospeed(&gripper_serial_cfg, BAUDRATE); /* baud rate */
        tcsetattr(gripper_serial, TCSANOW, &gripper_serial_cfg); /* apply the settings */
        tcflush(gripper_serial, TCOFLUSH);
        //End Initialize Gripper

        tf::StampedTransform transform;
        tf::Transform current_position;
        lar_comau::ComauCommand comau_command;
        comau_command.command = "joint";


        boost::thread updateTFsThread(updateTFs);

        // Spin
        while( ros::ok() && GLOBAL_NODE_ACTIVE_STATUS ) {

                if(gripper_serial) {
                        std::cout << "*** GRIPPER ONLINE! ***" << std::endl;
                        std::cout << "  -- Closure angle: "<<gripper_closure_angle<<std::endl;
                        gripper_closure_angle += gripper_closure_speed;
                }else{
                        std::cout << "*** GRIPPER OFFLINE! ***" <<std::endl;
                }

                if(comau_sync) {
                        std::cout << "*** SYNC WITH COMAU ACTIVE! ***"<<std::endl;
                }

                /** MODE JOYSTICK CONTROL */
                if(current_mode==JOYSTICK_CONTROL) {
                        std::cout << "Mode: Joystick Control"<<std::endl;
                        std::cout << joystick_angular_speed<<std::endl;

                        joystick_set_point.position.x +=  joystick_speed.x;
                        joystick_set_point.position.y +=  joystick_speed.y;
                        joystick_set_point.position.z +=  joystick_speed.z;

                        KDL::Rotation joystick_rotation;
                        MathUtils::poseToKDLRotation(joystick_set_point,joystick_rotation);
                        joystick_rotation.DoRotX(joystick_angular_speed.x);
                        joystick_rotation.DoRotY(joystick_angular_speed.y);
                        joystick_rotation.DoRotZ(joystick_angular_speed.z);
                        MathUtils::poseToKDLRotation(joystick_set_point,joystick_rotation,true);

                        MathUtils::poseToTF(joystick_set_point,current_position);
                }

                /** MODE FOLLOW TARGET */
                if(current_mode==FOLLOW_TARGET) {
                        std::cout << "Mode: Follow Target"<<std::endl;

                        if(markers_current_list.size()<=0) {
                                std::cout << "NO TARGET ARE YOU CRAZY!!! "<<follow_target_id<<std::endl;
                        }else{
                                std::cout << "Following target: "<<follow_target_id<<std::endl;

                                follow_target_approach_pose.position.z +=  joystick_speed.z/100.0f;
                                if(follow_target_approach_pose.position.z<0.05f) {
                                        follow_target_approach_pose.position.z=0.025f;
                                }
                                KDL::Rotation approach_rotation;
                                MathUtils::poseToKDLRotation(follow_target_approach_pose,approach_rotation);
                                approach_rotation.DoRotZ(joystick_angular_speed.z/100.0f);
                                MathUtils::poseToKDLRotation(follow_target_approach_pose,approach_rotation,true);

                                current_position = target_approach;

                        }
                }




                if(GLOBAL_CALIBRATION_ACTIVE) {
                        try{
                                listener->lookupTransform("camera_rgb_frame", calibration_marker_name, ros::Time(0), t_cam_marker);
                                listener->lookupTransform("base", "comau_base_marker",ros::Time(0), t_0_marker);

                                t_6_0 = t_0_6.inverse();
                                t_marker_cam = t_cam_marker.inverse();
                                t_6_cam = t_6_0 * t_0_marker;
                                t_6_cam = t_6_cam * t_marker_cam;

                                tf_broadcaster->sendTransform(tf::StampedTransform(t_6_cam, ros::Time::now(), "comau_t0U", "comau_t0CAM"));

                                tf::Transform full = t_0_6*t_6_cam;
                                tf_broadcaster->sendTransform(tf::StampedTransform(full, ros::Time::now(), "base", "comau_t0CAM_full"));

                                //tf_broadcaster->sendTransform(tf::StampedTransform(t_0_6, ros::Time(0), "base", "camera_rgb_frame"));
                        }
                        catch (tf::TransformException ex) {
                                ROS_ERROR("%s",ex.what());
                        }
                }else{
                        listener->lookupTransform("base", "comau_t0U",ros::Time(0), t_0_6);
                        //tf_broadcaster->sendTransform(tf::StampedTransform(t_0_6, ros::Time(0), "base", "camera_rgb_frame"));
                }

                /** TARGET SELECTION */
                lar_visionsystem::MarkerApproachCommand target_approach_command;
                target_approach_command.marker_id = follow_target_id;
                target_approach_command.update_target_only = true;
                marker_approach.publish(target_approach_command);
                std::cout << markers_current_list.size() <<std::endl;

                /** BROACAST COMAU TF TARGET */
                tf_broadcaster->sendTransform(tf::StampedTransform(current_position, ros::Time(0), "base", "comau_tf_target"));
                std::cout << "Sending "<<current_position.getOrigin()[0]<<std::endl;

                /** SEND DATA TO COMAU */
                MathUtils::poseToTF(comau_command.pose,current_position,true);
                std::cout << comau_command<<std::endl;
                comau_cartesian_controller.publish(comau_command);

                ros::spinOnce();
                std::system("clear");
        }

        updateTFsThread.join();
}