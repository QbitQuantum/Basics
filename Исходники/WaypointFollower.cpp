  inline void WaypointFollower::turnVelocityInGoal(VELOCITY_COMMAND & cmd) {
    double final_turning_angle = 0.0;
    final_turning_angle = NORMALIZE(this->final_gaz - this->az);
    ROS_DEBUG_NAMED("velo","Normalize(%f - %f) = %f", this->final_gaz, this->az, final_turning_angle);
    ROS_DEBUG_NAMED("velo","Reaching final angle from %f to %f = %f", this->az, this->final_gaz, final_turning_angle);
    cmd.vel.px = 0;

    if (fabs(final_turning_angle) < this->motionParams.az_success_distance) {
      cmd.vel.pa = 0;
      ROS_INFO("Goal reached at angle %f < %f", fabs(final_turning_angle) , this->motionParams.az_success_distance);
      this->goal_ready = false;
      this->robot_movement_allowed = false; // wait for new goal
    } else {
      cmd.vel.pa = ABSMAX( ( final_turning_angle * this->motionParams.pid_rot_kp ), this->motionParams.max_rot_vel );
    }
  }