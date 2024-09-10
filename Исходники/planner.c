// Add a new linear movement to the buffer. x, y and z is the signed, absolute target position in 
// millimeters. Feed rate specifies the speed of the motion. If feed rate is inverted, the feed
// rate is taken to mean "frequency" and would complete the operation in 1/feed_rate minutes.
// All position data passed to the planner must be in terms of machine position to keep the planner 
// independent of any coordinate system changes and offsets, which are handled by the g-code parser.
// NOTE: Assumes buffer is available. Buffer checks are handled at a higher level by motion_control.
void plan_buffer_line(float x, float y, float z, float feed_rate, uint8_t invert_feed_rate) 
{
  // Prepare to set up new block
  block_t *block = &block_buffer[block_buffer_head];

  // Calculate target position in absolute steps
  int32_t target[3];
  target[X_AXIS] = lround(x*settings.steps_per_mm[X_AXIS]);
  target[Y_AXIS] = lround(y*settings.steps_per_mm[Y_AXIS]);
  target[Z_AXIS] = lround(z*settings.steps_per_mm[Z_AXIS]);     

  // Compute direction bits for this block
  block->direction_bits = 0;
  if (target[X_AXIS] < pl.position[X_AXIS]) { block->direction_bits |= (1<<X_DIRECTION_BIT); }
  if (target[Y_AXIS] < pl.position[Y_AXIS]) { block->direction_bits |= (1<<Y_DIRECTION_BIT); }
  if (target[Z_AXIS] < pl.position[Z_AXIS]) { block->direction_bits |= (1<<Z_DIRECTION_BIT); }
  
  // Number of steps for each axis
  block->steps_x = labs(target[X_AXIS]-pl.position[X_AXIS]);
  block->steps_y = labs(target[Y_AXIS]-pl.position[Y_AXIS]);
  block->steps_z = labs(target[Z_AXIS]-pl.position[Z_AXIS]);
  block->step_event_count = max(block->steps_x, max(block->steps_y, block->steps_z));

  // Bail if this is a zero-length block
  if (block->step_event_count == 0) { return; };
  
  // Compute path vector in terms of absolute step target and current positions
  float delta_mm[3];
  delta_mm[X_AXIS] = (target[X_AXIS]-pl.position[X_AXIS])/settings.steps_per_mm[X_AXIS];
  delta_mm[Y_AXIS] = (target[Y_AXIS]-pl.position[Y_AXIS])/settings.steps_per_mm[Y_AXIS];
  delta_mm[Z_AXIS] = (target[Z_AXIS]-pl.position[Z_AXIS])/settings.steps_per_mm[Z_AXIS];
  block->millimeters = sqrt(delta_mm[X_AXIS]*delta_mm[X_AXIS] + delta_mm[Y_AXIS]*delta_mm[Y_AXIS] + 
                            delta_mm[Z_AXIS]*delta_mm[Z_AXIS]);
  float inverse_millimeters = 1.0/block->millimeters;  // Inverse millimeters to remove multiple divides	
  
  // Calculate speed in mm/minute for each axis. No divide by zero due to previous checks.
  // NOTE: Minimum stepper speed is limited by MINIMUM_STEPS_PER_MINUTE in stepper.c
  float inverse_minute;
  if (!invert_feed_rate) {
    inverse_minute = feed_rate * inverse_millimeters;
  } else {
    inverse_minute = 1.0 / feed_rate;
  }
  block->nominal_speed = block->millimeters * inverse_minute; // (mm/min) Always > 0
  block->nominal_rate = ceil(block->step_event_count * inverse_minute); // (step/min) Always > 0
  
  // Compute the acceleration rate for the trapezoid generator. Depending on the slope of the line
  // average travel per step event changes. For a line along one axis the travel per step event
  // is equal to the travel/step in the particular axis. For a 45 degree line the steppers of both
  // axes might step for every step event. Travel per step event is then sqrt(travel_x^2+travel_y^2).
  // To generate trapezoids with contant acceleration between blocks the rate_delta must be computed 
  // specifically for each line to compensate for this phenomenon:
  // Convert universal acceleration for direction-dependent stepper rate change parameter
  block->rate_delta = ceil( block->step_event_count*inverse_millimeters *  
        settings.acceleration / (60 * ACCELERATION_TICKS_PER_SECOND )); // (step/min/acceleration_tick)

  // Compute path unit vector                            
  float unit_vec[3];

  unit_vec[X_AXIS] = delta_mm[X_AXIS]*inverse_millimeters;
  unit_vec[Y_AXIS] = delta_mm[Y_AXIS]*inverse_millimeters;
  unit_vec[Z_AXIS] = delta_mm[Z_AXIS]*inverse_millimeters;  

  // Compute maximum allowable entry speed at junction by centripetal acceleration approximation.
  // Let a circle be tangent to both previous and current path line segments, where the junction 
  // deviation is defined as the distance from the junction to the closest edge of the circle, 
  // colinear with the circle center. The circular segment joining the two paths represents the 
  // path of centripetal acceleration. Solve for max velocity based on max acceleration about the
  // radius of the circle, defined indirectly by junction deviation. This may be also viewed as 
  // path width or max_jerk in the previous grbl version. This approach does not actually deviate 
  // from path, but used as a robust way to compute cornering speeds, as it takes into account the
  // nonlinearities of both the junction angle and junction velocity.
  // NOTE: This is basically an exact path mode (G61), but it doesn't come to a complete stop unless
  // the junction deviation value is high. In the future, if continuous mode (G64) is desired, the
  // math here is exactly the same. Instead of motioning all the way to junction point, the machine
  // will just need to follow the arc circle defined above and check if the arc radii are no longer
  // than half of either line segment to ensure no overlapping. Right now, the Arduino likely doesn't
  // have the horsepower to do these calculations at high feed rates.
  float vmax_junction = MINIMUM_PLANNER_SPEED; // Set default max junction speed

  // Skip first block or when previous_nominal_speed is used as a flag for homing and offset cycles.
  if ((block_buffer_head != block_buffer_tail) && (pl.previous_nominal_speed > 0.0)) {
    // Compute cosine of angle between previous and current path. (prev_unit_vec is negative)
    // NOTE: Max junction velocity is computed without sin() or acos() by trig half angle identity.
    float cos_theta = - pl.previous_unit_vec[X_AXIS] * unit_vec[X_AXIS] 
                       - pl.previous_unit_vec[Y_AXIS] * unit_vec[Y_AXIS] 
                       - pl.previous_unit_vec[Z_AXIS] * unit_vec[Z_AXIS] ;
                         
    // Skip and use default max junction speed for 0 degree acute junction.
    if (cos_theta < 0.95) {
      vmax_junction = min(pl.previous_nominal_speed,block->nominal_speed);
      // Skip and avoid divide by zero for straight junctions at 180 degrees. Limit to min() of nominal speeds.
      if (cos_theta > -0.95) {
        // Compute maximum junction velocity based on maximum acceleration and junction deviation
        float sin_theta_d2 = sqrt(0.5*(1.0-cos_theta)); // Trig half angle identity. Always positive.
        vmax_junction = min(vmax_junction,
          sqrt(settings.acceleration * settings.junction_deviation * sin_theta_d2/(1.0-sin_theta_d2)) );
      }
    }
  }
  block->max_entry_speed = vmax_junction;
  
  // Initialize block entry speed. Compute based on deceleration to user-defined MINIMUM_PLANNER_SPEED.
  float v_allowable = max_allowable_speed(-settings.acceleration,MINIMUM_PLANNER_SPEED,block->millimeters);
  block->entry_speed = min(vmax_junction, v_allowable);

  // Initialize planner efficiency flags
  // Set flag if block will always reach maximum junction speed regardless of entry/exit speeds.
  // If a block can de/ac-celerate from nominal speed to zero within the length of the block, then
  // the current block and next block junction speeds are guaranteed to always be at their maximum
  // junction speeds in deceleration and acceleration, respectively. This is due to how the current
  // block nominal speed limits both the current and next maximum junction speeds. Hence, in both
  // the reverse and forward planners, the corresponding block junction speed will always be at the
  // the maximum junction speed and may always be ignored for any speed reduction checks.
  if (block->nominal_speed <= v_allowable) { block->nominal_length_flag = true; }
  else { block->nominal_length_flag = false; }
  block->recalculate_flag = true; // Always calculate trapezoid for new block

  // Update previous path unit_vector and nominal speed
  memcpy(pl.previous_unit_vec, unit_vec, sizeof(unit_vec)); // pl.previous_unit_vec[] = unit_vec[]
  pl.previous_nominal_speed = block->nominal_speed;
  
  // Update buffer head and next buffer head indices
  block_buffer_head = next_buffer_head;  
  next_buffer_head = next_block_index(block_buffer_head);
  
  // Update planner position
  memcpy(pl.position, target, sizeof(target)); // pl.position[] = target[]

  planner_recalculate(); 
}