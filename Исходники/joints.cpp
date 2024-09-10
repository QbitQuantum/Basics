    bool FLOATING_T::run(robot::robot_state_t& target, control_data_t* data)
    {
        // 1. Setup
        Eigen::Isometry3d body;
        target.get_body(body);

        // 1. Variables
        Eigen::Quaterniond save_rotation(data->joy_rotation);
        Eigen::Vector3d save_position = data->joy_position;
        
        Eigen::Quaterniond rotation(data->joy_rotation);
        Eigen::Vector3d& position = data->joy_position;

        // 2. Clamp to xyy
        position[2] = 0;
        rotation.y() = 0;
        rotation.x() = 0;

        body.linear() = body.linear() * rotation.matrix();
        body.translation() += position;

        // 3.
        target.set_body(body);

        return true;
    }    