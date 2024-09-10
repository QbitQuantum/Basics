/**
 * Send FlightGear FDM packet
 * For visualization with moving surfaces (elevator, propeller etc).
 * start fgfs with --native-fdm=socket... option
 */
void nps_flightgear_send_fdm()
{
  struct FGNetFDM fgfdm;

  memset(&fgfdm, 0, sizeof(fgfdm));
  fgfdm.version = htonl(FG_NET_FDM_VERSION);

  fgfdm.latitude  = htond(fdm.lla_pos.lat);
  fgfdm.longitude = htond(fdm.lla_pos.lon);
  fgfdm.altitude  = htond(fdm.lla_pos.alt);


  fgfdm.agl = htonf((float)fdm.agl);

  fgfdm.phi = htonf((float)fdm.ltp_to_body_eulers.phi);
  fgfdm.theta = htonf((float)fdm.ltp_to_body_eulers.theta);
  fgfdm.psi = htonf((float)fdm.ltp_to_body_eulers.psi);

  fgfdm.vcas = htonf(0.);
  fgfdm.climb_rate = htonf(0.);

  fgfdm.num_tanks = htonl(1);
  fgfdm.fuel_quantity[0] = htonf(0.);

  fgfdm.cur_time = htonl(flightgear.initial_time + rint(fdm.time));
  // if cur_time is zero, flightgear would take the real current time
  //gui.cur_time = 0;
  // warp is used as an offset to the current time in seconds
  fgfdm.warp = htonl(flightgear.time_offset);

  // Engine
  fgfdm.num_engines = htonl(fdm.num_engines);
  for (int k = 0; k < FG_NET_FDM_MAX_ENGINES; k++) {
    // Temprary hack to clearly show when the engine is running
    if (fdm.eng_state[k] == 1) {
      fgfdm.rpm[k] = htonf(fdm.rpm[k]);
    } else {
      fgfdm.rpm[k] = htonf(0.0);
    }
    fgfdm.eng_state[k] = htonl(fdm.eng_state[k]);
  }

  //control surfaces
  fgfdm.elevator = htonf(fdm.elevator);
  fgfdm.left_aileron = htonf(fdm.left_aileron);
  fgfdm.right_aileron = htonf(fdm.right_aileron);
  fgfdm.rudder = htonf(fdm.rudder);
  fgfdm.left_flap = htonf(fdm.flap);
  fgfdm.right_flap = htonf(fdm.flap);

  if (sendto(flightgear.socket, (char *)(&fgfdm), sizeof(fgfdm), 0,
             (struct sockaddr *)&flightgear.addr, sizeof(flightgear.addr)) == -1) {
    fprintf(stderr, "error sending to FlightGear\n");
    fflush(stderr);
  }
}