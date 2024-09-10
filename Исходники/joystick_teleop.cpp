    /**
     *  \brief Callback for the joystick topic.
     */
    void joyCb(const sensor_msgs::Joy::ConstPtr& msg)
    {
        last_recv_ = ros::Time::now();

        deadman_ = msg->buttons[deadman_button_];
        deadman_head_ = msg->buttons[deadman_head_button_];
        deadman_arm_angular_ = msg->buttons[deadman_arm_angular_button_];
        deadman_arm_linear_ = msg->buttons[deadman_arm_linear_button_];

        if (!deadman_)
        {
            controller_.stop();
            return;
        }

        controller_.start();

        if (deadman_arm_angular_ || deadman_arm_linear_)
        {
            // Stop moving base
            vx = 0.0;
            vw = 0.0;

            // Stop head
            pan = 0.0;
            tilt = 0.0;

            // Stop moving torso
            torso = 0.0;

            if (deadman_arm_linear_)
            {
                // Linear takes precedence over angular
                arm_lx = msg->axes[arm_lx_axis_]*arm_linear_scale_;
                arm_ly = msg->axes[arm_ly_axis_]*arm_linear_scale_;
                arm_lz = msg->axes[arm_lz_axis_]*arm_linear_scale_;
                arm_ax = 0.0;
                arm_ay = 0.0;
                arm_az = 0.0;
            }
            else
            {
                arm_lx = 0.0;
                arm_ly = 0.0;
                arm_lz = 0.0;
                arm_ax = -msg->axes[arm_ax_axis_]*arm_angular_scale_;
                arm_ay = msg->axes[arm_ay_axis_]*arm_angular_scale_;
                arm_az = msg->axes[arm_az_axis_]*arm_angular_scale_;
            }

            controller_.setArmTwist(arm_lx, arm_ly, arm_lz, arm_ax, arm_ay, arm_az);
        }
        else if (deadman_head_)
        {
            // Stop moving base
            vx = 0.0;
            vw = 0.0;

            // Get head
            pan = msg->axes[head_pan_axis_]*head_pan_step_;
            tilt = msg->axes[head_tilt_axis_]*head_tilt_step_;

            // Stop moving torso
            torso = 0.0;

            // Stop moving arm
            controller_.disableArm();
        }
        else
        {
            // Get base velocities
            vx = msg->axes[base_vx_axis_] * base_max_vel_x_;
            vw = msg->axes[base_vw_axis_] * base_max_vel_w_;

            // Limit velocities
            vx = fmax(fmin(vx, base_max_vel_x_), -base_max_vel_x_);
            vw = fmax(fmin(vw, base_max_vel_w_), -base_max_vel_w_);

            // Stop moving head
            pan = 0.0;
            tilt = 0.0;

            // Get torso
            if (msg->buttons[torso_down_button_])
                torso = -torso_step_;
            else if (msg->buttons[torso_up_button_])
                torso = torso_step_;
            else
                torso = 0.0;

            // Get Gripper
            if (msg->buttons[gripper_open_button_])
                controller_.openGripper();
            else if (msg->buttons[gripper_close_button_])
                controller_.closeGripper();

            // Stop moving arm
            controller_.disableArm();
        }
    }