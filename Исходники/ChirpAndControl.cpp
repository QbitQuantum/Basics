void PositionCommand::control()
{
    geometry_msgs::Twist        vel_cmd_msg;
    geometry_msgs::Pose         current_error_msg ;

    Eigen::Matrix<double,6,1>   current_error;

    if (control_)
    {
        current_error= goal_pose_ - current_pose_;

        // if the error is less than epsilon goal is reached
        if(current_error.norm() < .1)
        {
            ROS_INFO("Reached goal!");
        }

        accum_error_ = accum_error_+ period_*(current_error + previous_error_)/2.0;

        Eigen::Matrix<double,6,6> Cp = Kp * current_error.transpose();
        Eigen::Matrix<double,6,6> Ci = Ki * accum_error_.transpose();
        Eigen::Matrix<double,6,6> Cd = Kd * (current_error - previous_error_).transpose()/period_;

        //std::cout << "Cp ="  <<  Cp << std::endl;
        //std::cout << "Ci ="  <<  Ci << std::endl;
        //std::cout << "Cd ="  <<  Cd << std::endl;

        Eigen::Matrix<double,6,6> vel_cmd_current = Cp + Ci + Cd ;
        Eigen::Matrix<double,3,1> linear_vel_cmd_l_frame;

        linear_vel_cmd_l_frame << vel_cmd_current(0,0),
                vel_cmd_current(1,1),
                vel_cmd_current(2,2);

        Eigen::Matrix<double,3,1> linear_vel_cmd_g_frame = rot_matrix_.inverse() * linear_vel_cmd_l_frame;

        if (chirp_enable_)
        {
            linear_vel_cmd_g_frame(0,0) = linear_vel_cmd_g_frame(0,0) + chirp_command();
        }

        vel_cmd_msg.linear.x  = Sat(linear_vel_cmd_g_frame(0,0),1,-1);
        vel_cmd_msg.linear.y  = Sat(linear_vel_cmd_g_frame(1,0),1,-1);
        vel_cmd_msg.linear.z  = Sat(linear_vel_cmd_g_frame(2,0),1,-1);
        vel_cmd_msg.angular.z = Sat(vel_cmd_current(5,5),1,-1);

        previous_error_     = current_error;
        control_            = false;

        current_error_pub.publish(current_error_msg);

        std::cout << "CE: x ="  <<  current_error(0,0)
                  << " y = "    <<  current_error(1,0)
                  << " z = "    <<  current_error(2,0)
                  << " w = "    <<  current_error(5,0)
                  << std::endl;
    }

    current_error_msg.position.x    = current_error(0,0);
    current_error_msg.position.y    = current_error(1,0);
    current_error_msg.position.z    = current_error(2,0);
    current_error_msg.orientation.x = current_error(0,0);
    current_error_msg.orientation.y = current_error(1,0);
    current_error_msg.orientation.z = current_error(2,0);

    vel_cmd.publish(vel_cmd_msg);

    //    std::cout << "AE: x ="  <<  accum_error_(0,0)
    //              << " y = "    <<  accum_error_(1,0)
    //              << " z = "    <<  accum_error_(2,0)
    //             << " w = "    <<  accum_error_(5,0)
    //              << std::endl;

    std::cout << "Kp = "  << Kp.transpose()<< std::endl;
    std::cout << "Ki = "  << Ki.transpose()<< std::endl;
    std::cout << "Kd = "  << Kd.transpose()<< std::endl;

    std::cout << "vel: x =" <<  vel_cmd_msg.linear.x
              << " y = "    <<  vel_cmd_msg.linear.y
              << " z = "    <<  vel_cmd_msg.linear.z
              << " w = "    <<  vel_cmd_msg.angular.z
              << std::endl;

}