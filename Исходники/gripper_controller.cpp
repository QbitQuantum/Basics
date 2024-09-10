    //================================================================
    // Higher level motion to close gripper until contact is found
    // Pass in the rate at which contact is closed at and the 
    // distance the gripper moves rate is in Hz, 
    // move_gripper_distance in meters
    // Velocity gripper moves is found by how much moved by what rate
    //================================================================
    void findContactOld(ros::Rate rate, double move_gripper_distance)
    {
      int pressure_min = 0; 
      int pressure_max = 0;
      bool contact_found = false;
      bool fingerSet = true;
      int no_motion_counter = 0;
      int previous_pressure_max = 0;

      // Close until minimum pressure is found - however stop if
      // any finger has too much pressure
      while (pressure_min < LightPressureContact && ros::ok()
             && pressure_max < 600  && no_motion_counter < 250)
      {
        previous_pressure_max = pressure_max;
        
        // Checks if pressure has been "stuck" 
        if (abs(previous_pressure_max-pressure_max) < 1)
          no_motion_counter++;

        // First touches object
        if (pressure_max > 5 && fingerSet)
        {
          firstContact.position = simple_gripper->getGripperLastPosition();
          if (biotac_obs->pressure_normalized_[Left] > biotac_obs->pressure_normalized_[Right])
          {
            firstContact.finger = Left;
          }
          else
          {
            firstContact.finger = Right;
          }
          fingerSet = false;
        }

        // Second finger touches object
        if (pressure_min > 10)
        {
          secondContact.position = simple_gripper->getGripperLastPosition();
          if (firstContact.position == Left)
          {
            secondContact.finger = Right;
          }
          else
          {
            secondContact.finger = Left;
          }
        }

        // Set distance for object width 
        if (!contact_found && pressure_min > 10){
          gripper_initial_contact_position = simple_gripper->getGripperLastPosition();
          contact_found = true;
        }
      
        // Store last pressure felt by each finger 
        tap_pressure_left = biotac_obs->pressure_normalized_[Left];
        tap_pressure_right = biotac_obs->pressure_normalized_[Right];

        // Check pressure min and max
        pressure_min = min(biotac_obs->pressure_normalized_[Left], biotac_obs->pressure_normalized_[Right]);
        pressure_max = max(biotac_obs->pressure_normalized_[Left], biotac_obs->pressure_normalized_[Right]);
        simple_gripper->closeByAmount(move_gripper_distance);
        //ROS_INFO("Pressure Min is: [%d]", pressure_min);
       // ROS_INFO("Pressure Max is: [%d]", pressure_max);
        ros::spinOnce();
        rate.sleep();
      }
    }