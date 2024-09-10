    // TODO needs some love
    void run() {
        while(ros::ok()) {
            current_time = ros::Time::now();
            double dt = (current_time - last_time).toSec();
            // TODO these predicst and measure variables are not something that I understand
            if (predict) {
                prediction(dt);
                last_time = current_time;
                predict = false;

                if (measure) {
                    update_estimated_measurement();
                    weighting();
                    measure = false;
                }

                Normalization();
                resample();
            }

            if (visualization_enabled) {
                if (publish_particles) {
                    particles_pub.publish(loc_viz.get_particle_marker(particle_state));
                }
                if (publish_robot) {
                    robot_pub.publish(
                        loc_viz.get_robot_marker(std::vector<ras::sensor_info>(), x, y, theta, visualization_use_distance));
                }
                if (publish_thickened_walls) {
                    wall_cell_pub.publish(loc_viz.get_thick_wall_grid_cells());
                }
                if (publish_walls) {
                    grid_cell_pub.publish(loc_viz.get_wall_grid_cells());
                }
                if (publish_path) {
                    point_path_pub.publish(loc_viz.add_to_path(x, y));
                }
            }

            //Publish Geometry msg of Predicted postion
            geometry_msgs::Pose2D msg;
            msg.x = x;
            msg.y = y;
            msg.theta = theta;
            position_pub.publish(msg);

            //Use if add a subscription(Add as good measure)
            ros::spinOnce();
            //Delays untill it is time to send another message
            rate->sleep();
            last_time = current_time;
        }
    }