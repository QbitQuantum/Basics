// Deserialize the move server packet
void deserializeMoveServerPacket(MoveServerPacket *move_server_packet) {
  int i, j;

  // Server Config
  move_server_packet->server_config.num_image_slices = ntohl(move_server_packet->server_config.num_image_slices);
  move_server_packet->server_config.image_slice_format = ntohl(move_server_packet->server_config.image_slice_format);

  // Connection Config
  move_server_packet->client_config.ms_delay_between_standard_packets = ntohl(move_server_packet->client_config.ms_delay_between_standard_packets);
  move_server_packet->client_config.ms_delay_between_camera_frame_packets = ntohl(move_server_packet->client_config.ms_delay_between_camera_frame_packets);
  move_server_packet->client_config.camera_frame_packet_paused = ntohl(move_server_packet->client_config.camera_frame_packet_paused);

  // Camera
  move_server_packet->camera_state.exposure = ntohl(move_server_packet->camera_state.exposure);
  move_server_packet->camera_state.exposure_time = ntohf(move_server_packet->camera_state.exposure_time);
  move_server_packet->camera_state.gain = ntohf(move_server_packet->camera_state.gain);
  move_server_packet->camera_state.pitch_angle = ntohf(move_server_packet->camera_state.pitch_angle);
  move_server_packet->camera_state.pitch_angle_estimate = ntohf(move_server_packet->camera_state.pitch_angle_estimate);

  // Nav
  for (i = 0; i < MOVE_SERVER_MAX_NAVS; i++) {
    move_server_packet->pad_info.port_status[i] = ntohl(move_server_packet->pad_info.port_status[i]);

    // NavPadData
    move_server_packet->pad_data[i].len = ntohl(move_server_packet->pad_data[i].len);

    for (j = 0; j < CELL_PAD_MAX_CODES; j++) {
      move_server_packet->pad_data[i].button[j] = ntohs(move_server_packet->pad_data[i].button[j]);

    }

  }

  // Gems
  for (i = 0; i < MOVE_SERVER_MAX_GEMS; i++) {

    // Status
    move_server_packet->status[i].connected = ntohl(move_server_packet->status[i].connected);
    move_server_packet->status[i].code = ntohl(move_server_packet->status[i].code);
    move_server_packet->status[i].flags = ntohll(move_server_packet->status[i].flags);

    if (move_server_packet->status[i].connected == 1) {

      // State
      for (j = 0; j < 4; j++) {
        move_server_packet->state[i].pos[j] = ntohf(move_server_packet->state[i].pos[j]);
        move_server_packet->state[i].vel[j] = ntohf(move_server_packet->state[i].vel[j]);
        move_server_packet->state[i].accel[j] = ntohf(move_server_packet->state[i].accel[j]);
        move_server_packet->state[i].quat[j] = ntohf(move_server_packet->state[i].quat[j]);
        move_server_packet->state[i].angvel[j] = ntohf(move_server_packet->state[i].angvel[j]);
        move_server_packet->state[i].angaccel[j] = ntohf(move_server_packet->state[i].angaccel[j]);
        move_server_packet->state[i].handle_pos[j] = ntohf(move_server_packet->state[i].handle_pos[j]);
        move_server_packet->state[i].handle_vel[j] = ntohf(move_server_packet->state[i].handle_vel[j]);
        move_server_packet->state[i].handle_accel[j] = ntohf(move_server_packet->state[i].handle_accel[j]);

      }

      move_server_packet->state[i].timestamp = (system_time_t)ntohll((uint64_t)move_server_packet->state[i].timestamp);
      move_server_packet->state[i].temperature = ntohf(move_server_packet->state[i].temperature);
      move_server_packet->state[i].camera_pitch_angle = ntohf(move_server_packet->state[i].camera_pitch_angle);
      move_server_packet->state[i].tracking_flags = ntohl(move_server_packet->state[i].tracking_flags);

      // Pad
      move_server_packet->state[i].pad.digital_buttons = ntohs(move_server_packet->state[i].pad.digital_buttons);
      move_server_packet->state[i].pad.analog_trigger = ntohs(move_server_packet->state[i].pad.analog_trigger);

      // Image State
      move_server_packet->image_state[i].frame_timestamp = (system_time_t)ntohll((uint64_t)move_server_packet->image_state[i].frame_timestamp);
      move_server_packet->image_state[i].timestamp = (system_time_t)ntohll((uint64_t)move_server_packet->image_state[i].timestamp);
      move_server_packet->image_state[i].u = ntohf(move_server_packet->image_state[i].u);
      move_server_packet->image_state[i].v = ntohf(move_server_packet->image_state[i].v);
      move_server_packet->image_state[i].r = ntohf(move_server_packet->image_state[i].r);
      move_server_packet->image_state[i].projectionx = ntohf(move_server_packet->image_state[i].projectionx);
      move_server_packet->image_state[i].projectiony = ntohf(move_server_packet->image_state[i].projectiony);
      move_server_packet->image_state[i].distance = ntohf(move_server_packet->image_state[i].distance);

      // Sphere State
      move_server_packet->sphere_state[i].tracking = ntohl(move_server_packet->sphere_state[i].tracking);
      move_server_packet->sphere_state[i].tracking_hue = ntohl(move_server_packet->sphere_state[i].tracking_hue);
      move_server_packet->sphere_state[i].r = ntohf(move_server_packet->sphere_state[i].r);
      move_server_packet->sphere_state[i].g = ntohf(move_server_packet->sphere_state[i].g);
      move_server_packet->sphere_state[i].b = ntohf(move_server_packet->sphere_state[i].b);

      // Pointer State
      move_server_packet->pointer_state[i].valid = ntohl(move_server_packet->pointer_state[i].valid);
      move_server_packet->pointer_state[i].normalized_x = ntohf(move_server_packet->pointer_state[i].normalized_x);
      move_server_packet->pointer_state[i].normalized_y = ntohf(move_server_packet->pointer_state[i].normalized_y);

      // Position Pointer State
      move_server_packet->position_pointer_state[i].valid = ntohl(move_server_packet->position_pointer_state[i].valid);
      move_server_packet->position_pointer_state[i].normalized_x = ntohf(move_server_packet->position_pointer_state[i].normalized_x);
      move_server_packet->position_pointer_state[i].normalized_y = ntohf(move_server_packet->position_pointer_state[i].normalized_y);

    }

  }

}