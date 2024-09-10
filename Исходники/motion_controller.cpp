void
motion_controller::running(void)
{
    cycle_start = ros::Time::now();

//  receive path and when received block path receiver until mission completed
    if (m_path && !block_path_receiver)
    {
        nav_msgs::Path temp_path = *m_path;
        std::vector<geometry_msgs::PoseStamped> temp_path_vector;
        extracted_path.clear();
        for( std::vector<geometry_msgs::PoseStamped>::iterator itr = temp_path.poses.begin() ; itr != temp_path.poses.end(); ++itr)
        {
            temp_path_vector.push_back(*itr);
        }

        if(!temp_path_vector.empty())
        {
             ROS_INFO("Path Received!");
        }
        p_count++;

        while(!temp_path_vector.empty())
        {
            extracted_path.push_back(temp_path_vector.back());
            temp_path_vector.pop_back();
        }
        block_path_receiver = true;
    }

//  switch status according to the command
    switch (m_move)
    {
        // move forward 
        case FORWARD:
        {
            // v is linear speed and gain is angular velocity
            v =  sqrt(dist)*v_max/(1 + gamma*k*k)*10000/PI;

            gain = 0.3265*v*k;
            if (fabs(gain) > 600)
            {
                gain = boost::math::sign(gain) * 600;
            }

            if(fabs(v)>2000)
            {
                v = boost::math::sign(v)*2000;
            }
            // set motor rotation velocity
            locomotor->set_vel(floor(v)+floor(gain),-floor(v)+floor(gain));

            // when the euler distance is less than 100mm, achieved waypoint
            if (distance2d(m_state, m_cmd) < 0.09 && indicator(m_state[2],m_cmd[2],0.5))
            {
                m_move = IDLE;
            }
            break;
        }

        case BACKWARD:
        {
            v =  sqrt(dist) * 0.75/(1+0.2*k_back*k_back) *10000/3.1415926;

            gain = 0.3265*v*k_back;

            if (fabs(gain) > 600)
            {
                gain = boost::math::sign(gain) * 600;
            }

            if(fabs(v)>2000)
            {
                v = boost::math::sign(v)*2000;
            }
            
            locomotor->set_vel(-floor(v)+floor(gain),floor(v)+floor(gain));
            if (distance2d(m_state, m_cmd) < 0.09 && indicator(m_state[2],m_cmd[2],0.5))
            {
                m_move = IDLE;
            }
            break;
        }

        case LIFTFORK:
        {
            // TODO: Lift height should be determined, fork stroke should be determined
            printf("Lift and fork!\n");

            locomotor->set_vel(0, 0);
            sleep(3);
//            locomotor->shut_down();
            lift_motor->power_on();
            if ((fork_count%2) == 1)
//          change -243720 to be -223720, wants to liftfork a little bit lower
                lift_motor->set_pos(-223720);
            else
                lift_motor->set_pos(-293720);

            sleep(10);

           printf("Start Test\n");

            // pose correction code inserted here  first make sure tag is attached vertically, second camera has no pitch angle relative to the vehicle
            

            if ((fork_count%2) == 1)
            {
                printf("Start Correction!\n");
                int count_detect = 0;
                while(ros::ok())
                {
                    if(abs_pose1)
                    {
                        Eigen::Quaternion<float> quat;
                        quat.w() = abs_pose1->pose.pose.orientation.w;
                        quat.x() = abs_pose1->pose.pose.orientation.x;
                        quat.y() = abs_pose1->pose.pose.orientation.y;
                        quat.z() = abs_pose1->pose.pose.orientation.z;

                        Eigen::Matrix3f Rotation;

                        Rotation = qToRotation(quat);

                        Eigen::Matrix3f FixTF;
                        FixTF << 1, 0,  0,
                                 0, 0, -1,
                                 0, 1,  0;

                        Rotation = FixTF * Rotation.inverse();

                        float yaw_error;
                    
                        yaw_error = getYawFromMat(Rotation);
                    
                        gain = -3265*(k_angle*yaw_error)/3.1415926;
                        if(fabs(gain)>150)
                        {
                            gain = boost::math::sign(gain) * 150;
                        }
                        locomotor->set_vel(floor(gain), floor(gain));
                        if (fabs(yaw_error*180/3.1415926) < 0.5)
                        {
                            locomotor->set_vel(0,0);
                            printf("Yaw %f corrected!\n", yaw_error*180/3.1415926);
                            break;
                        }
                    }
                    else
                    {
                        locomotor->set_vel(0, 0);
                        usleep(10000);
                        count_detect++;
                    }
                    ros::spinOnce();

                    if (count_detect>1000)
                    {
                        ROS_WARN("No Tag detected when stoped");
                        ros::shutdown();
                        exit(1);
                    }
                }
 
                count_detect = 0;
                while(ros::ok())
                {
                    if(abs_pose1)
                    {

                        Eigen::Quaternion<float> quat;
                        quat.w() = abs_pose1->pose.pose.orientation.w;
                        quat.x() = abs_pose1->pose.pose.orientation.x;
                        quat.y() = abs_pose1->pose.pose.orientation.y;
                        quat.z() = abs_pose1->pose.pose.orientation.z;

                        Eigen::Matrix3f Rotation;
                        Eigen::Vector3f translation;
                        translation << abs_pose1->pose.pose.position.x,
                                       abs_pose1->pose.pose.position.y,
                                       abs_pose1->pose.pose.position.z;

                        Rotation = qToRotation(quat);

                        translation = translation;

                        float x_error;
                    
                        x_error = translation[0];
                    
                        v = 0.25*(x_error-0.003)*10000/3.1415926;
//                        printf("x is %f\n", x_error);
//                        printf("v is %f\n\n", floor(v));
                        if(fabs(v)>150)
                        {
                            v = boost::math::sign(v) * 150;
                        }
                        locomotor->set_vel(floor(v), -floor(v));
                        if (fabs(x_error-0.003) < 0.003)
                        {
                            locomotor->set_vel(0, 0);
                            printf("x %f corrected!\n", (x_error-0.006));
                            break;
                        }
                    }
                    else
                    {
                        locomotor->set_vel(0, 0);
                        usleep(10000);
                        count_detect++;
                    }
                    ros::spinOnce();

                    if (count_detect>1000)
                    {
                        ROS_WARN("No Tag detected when stoped");
                        ros::shutdown();
                        exit(1);
                    }
                }
            }

            if ((fork_count%2) == 0)
            {
                int count_detect = 0;

                while(ros::ok())
                {
                    if (abs_pose)
                    {
                        Eigen::Quaternion<float> quat;
                        quat.w() = abs_pose->pose.pose.orientation.w;
                        quat.x() = abs_pose->pose.pose.orientation.x;
                        quat.y() = abs_pose->pose.pose.orientation.y;
                        quat.z() = abs_pose->pose.pose.orientation.z;

                        Eigen::Matrix3f Rotation;

                        Rotation = qToRotation(quat);

                        Eigen::Matrix3f fixTF;
                        fixTF << 1, 0,  0,
                                 0, -1, 0,
                                 0, 0, -1;

                        Rotation = Rotation.inverse()*fixTF;

                        m_state[2] = getYawFromMat(Rotation);
                        gain = 3265*(k_angle*angle(m_cmd[2],m_state[2]))/PI;
                        if (fabs(gain) > 100)
                        {
                            gain = boost::math::sign(gain) * 100;
                        }
                        
                        if (fabs(gain) >100)
                        {
                            ros::shutdown();
                            exit(1);
                        }

                        locomotor->set_vel(floor(gain),floor(gain));
                        if (indicator(m_cmd[2], m_state[2], 0.008))
                        {
                            locomotor->set_vel(0, 0);
                            printf("Corrected!\n");
                            break;
                        }
                    }
                    else
                    {
                        locomotor->set_vel(0, 0);
                        usleep(10000);
                        count_detect++;
                    }
                    ros::spinOnce();

                    if (count_detect>1000)
                    {
                        locomotor->set_vel(0, 0);
                        ROS_WARN("No Tag detected when stoped");
                        //ros::shutdown();
                        //exit(1);
                    }
                }
            }

            // if we carry out hand hold barcode test, after correction, stop
//               ros::shutdown();
//               exit(1);

            locomotor->shut_down();
            sleep(0.5);

// comment following two lines can set make telefork not strech out
            telefork_motor->set_pos( boost::math::sign(lift_param)*(-386000) );
            sleep(15);

            if ((fork_count%2) == 1)
                 lift_motor->set_pos(-293720);
            else
                 lift_motor->set_pos(-223720);
            sleep(3);

            telefork_motor->set_pos(0);
            sleep(15);            

//            ros::shutdown();
//            exit(1);
            lift_motor->shut_down();
            locomotor->power_on();
            sleep(0.5);
            m_move = IDLE;

            break;
        }

        case TURN:
        {
            v = cos(alpha) * dist* k_dist *10000/PI;
            if(fabs(v)>300)
            {
                v = boost::math::sign(v)*300;
            }

            gain = 3265*(k_angle*angle(m_cmd[2],m_state[2]))/PI;
            if (fabs(gain) > 400)
            {
                gain = boost::math::sign(gain) * 400;
            }
            locomotor->set_vel(floor(v)+floor(gain),-floor(v)+floor(gain));

            if (indicator(m_state[2],m_cmd[2],0.01))
            {
                m_move = IDLE;
            }
            break;
        }
  
        case IDLE:
        {
           locomotor->set_vel(0,0);
           if (extracted_path.size()!=0)
           {
               geometry_msgs::PoseStamped temp_pose = extracted_path.back();
               float yaw_ = 2*atan2(temp_pose.pose.orientation.z,temp_pose.pose.orientation.w);
               m_cmd << temp_pose.pose.position.x * m_resolution,
                        temp_pose.pose.position.y * m_resolution,
                        angle(yaw_,0);

               printf("Next Commanded Pose is (%f, %f, %f)\n", m_cmd[0], m_cmd[1], m_cmd[2]);
               if ( (fabs(m_cmd[0] - m_state[0])>0.5) && (fabs(m_cmd[1] - m_state[1])>0.5) )
               {
                   printf("Invalid commanded position received!\n");
                   locomotor->shut_down();
                   ros::shutdown();
                   exit(1);
               }
               if ( (fabs(m_cmd[0] - m_state[0])>0.5) || (fabs(m_cmd[1] - m_state[1])>0.5) )
               {
                   if (fabs(angle(m_cmd[2],m_state[2]))>0.5)
                   {
                       printf("Invalid commanded pose orientation received!\n");
                       locomotor->shut_down();
                       ros::shutdown();
                       exit(1);
                   }
                   if (fabs(m_cmd[0] - m_state[0])>0.5)
                   {
                       if (cos(m_state[2]) *  (m_cmd[0] - m_state[0]) > 0)
                           m_move = FORWARD;
                       else
                           m_move = BACKWARD;
                   }
                   else
                   {
                       if (sin(m_state[2]) *  (m_cmd[1] - m_state[1]) > 0)
                           m_move = FORWARD;
                       else
                           m_move = BACKWARD;
                   }
                   if (m_move == FORWARD)
                       printf("Move Forward!\n");
                   else
                       printf("Move Backward!\n");
               }
               else if (fabs(m_cmd[2] - m_state[2])>0.5)
               {
                   m_move = TURN;
                   printf("Turn Around!\n");
               }
               else if (temp_pose.pose.position.z!=0)
               {
                   m_move = LIFTFORK;
                   fork_count++;
                   lift_param = temp_pose.pose.position.z;
               }
               else
                    m_move = IDLE;
               extracted_path.pop_back();
           }
           else
           {
                if (p_count == 2)
                {
                    lift_motor->power_on();
                    lift_motor->set_pos(0);
                    sleep(12);
                    lift_motor->shut_down();
                    sleep(0.5);
                }

               block_path_receiver = false;
               geometry_msgs::PoseStamped pose_msg;
         
               pose_msg.header.frame_id = "world";
               pose_msg.header.stamp = ros::Time::now();
               pose_msg.pose.position.x = m_state[0];
               pose_msg.pose.position.y = m_state[1];
               if (block_path_receiver)
                  pose_msg.pose.position.z = 1;
               else
                  pose_msg.pose.position.z = 0;

               pose_msg.pose.orientation.w = cos(m_state[2]/2);
               pose_msg.pose.orientation.x = 0;
               pose_msg.pose.orientation.y = 0;
               pose_msg.pose.orientation.z = sin(m_state[2]/2);
               m_posePub.publish(pose_msg);
               printf("IDLE!\n");
               sleep(1);
               m_move = IDLE;
           }

           break;
        }
    }
        
    vel.first = (vel.first + locomotor->get_vel().first)/2;
    vel.second = (vel.second + locomotor->get_vel().second)/2;

    cycle_period = (ros::Time::now() - cycle_start).toSec();

    m_state[0] = m_state[0] + (-vel.second+vel.first)/2 * cos(m_state[2]) * 0.018849555 * cycle_period/60;
    m_state[1] = m_state[1] + (-vel.second+vel.first)/2 * sin(m_state[2]) * 0.018849555 * cycle_period/60;        
    m_state[2] = m_state[2] + (vel.first + vel.second)/0.653 * 0.018849555 * cycle_period/60;


    if (abs_pose)
    {
        int id;
        id = abs_pose->id - 3;

        Eigen::Quaternion<float> quat;
        quat.w() = abs_pose->pose.pose.orientation.w;
        quat.x() = abs_pose->pose.pose.orientation.x;
        quat.y() = abs_pose->pose.pose.orientation.y;
        quat.z() = abs_pose->pose.pose.orientation.z;

        Eigen::Matrix3f Rotation;
        Eigen::Vector3f translation;
        translation << abs_pose->pose.pose.position.x,
                       abs_pose->pose.pose.position.y,
                       abs_pose->pose.pose.position.z;

        Rotation = qToRotation(quat);

        translation = -Rotation.inverse()*translation;

        Eigen::Matrix3f fixTF;
        fixTF << 1, 0,  0,
                 0, -1, 0,
                 0, 0, -1;

        Rotation = Rotation.inverse()*fixTF;

        m_state[0] = translation[0] + m_resolution * (id%10);
        m_state[1] = translation[1] + m_resolution * floor(id/10.0);
        m_state[2] = getYawFromMat(Rotation) + 0.04;
    }

    geometry_msgs::PoseStamped pose_msg;
         
    pose_msg.header.frame_id = "world";
    pose_msg.header.stamp = ros::Time::now();
    pose_msg.pose.position.x = m_state[0];
    pose_msg.pose.position.y = m_state[1];
    if (block_path_receiver)
        pose_msg.pose.position.z = 1;
    else
        pose_msg.pose.position.z = 0;

    pose_msg.pose.orientation.w = cos(m_state[2]/2);
    pose_msg.pose.orientation.x = 0;
    pose_msg.pose.orientation.y = 0;
    pose_msg.pose.orientation.z = sin(m_state[2]/2);

    m_posePub.publish(pose_msg);

    delta_y = m_cmd[1]-m_state[1];
    if(fabs(m_cmd[1]-m_state[1]) > 1.6)
    {
        delta_y = boost::math::sign(m_cmd[1]-m_state[1]) * 1.6;
    }

    delta_x = m_cmd[0]-m_state[0];
    if(fabs(m_cmd[0]-m_state[0]) > 1.6)
    {
        delta_x = boost::math::sign(m_cmd[0]-m_state[0]) * 1.6;
    }

    beta = angle(m_cmd[2], atan2(delta_y, delta_x));

    alpha = angle(m_state[2], atan2(delta_y, delta_x));

    beta1 = angle(m_cmd[2]+PI, atan2(delta_y, delta_x));

    alpha1 = angle(m_state[2]+3.1415926, atan2(delta_y, delta_x));

    dist = sqrt(delta_x*delta_x + delta_y* delta_y);

    k = -1/dist * (k2*(alpha-atan(-k1*beta)) + sin(alpha)*(1 + k1/(1+(k1*beta) * (k1*beta))));
    k_back = -1/dist * (k2*(alpha1-atan2(-k1*beta1,1)) + sin(alpha1)*(1 + k1/(1+(k1*beta1) * (k1*beta1))));
}