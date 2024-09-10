/*
 * All dimensions are in SI units and relative
 */
void traject_delta_on_all_axes( traject5D* traject)
{
  static unsigned long int serno = 0;
  static time_t t0;
  if (traject == NULL) {
    return;
  }
  if (serno++ == 0) {
    time( &t0);
  }
  if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
    printf( "\nMOVE[ #%lu %ds] traject_delta_on_all_axes( traject( %0.9lf, %1.9lf, %1.9lf, %1.9lf, F=%u) [m])\n",
	    serno, (int)time( NULL)-(int)t0,
	    traject->dx, traject->dy, traject->dz, traject->de, traject->feed);
  }

  double dx = traject->dx;
  double dy = traject->dy;
  double dz = traject->dz;
  double de = traject->de;

  int reverse_x = 0;
  if (dx < 0.0) {
    dx = -dx;
    reverse_x = 1;
  }
  int reverse_y = 0;
  if (dy < 0.0) {
    dy = -dy;
    reverse_y = 1;
  }
  int reverse_z = 0;
  if (dz < 0.0) {
    dz = -dz;
    reverse_z = 1;
  }
  int reverse_e = 0;
  if (de < 0.0) {
    de = -de;
    reverse_e = 1;
  }
  // We're only moving in 3D space, e-axis isn't part of this!
  double distance = sqrt( dx * dx + dy * dy + dz * dz);
  if (distance < 2.0E-9) {
    if (de == 0.0) {
      if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
        printf( "*** Null move, distance = %1.9lf\n", distance);
      }
      return;	// TODO: will this suffice ?
    }
    // If E is only moving axis, set distance from E
    distance = de;
  }
 /*
  * Travel distance and requested velocity are now known.
  * Determine the velocities for the individual axes
  * using the distances and total duration of the move.
  * If a calculated velocity is higher than the maximum
  * allowed, slow down the entire move.
  */
  double recipr_dt = traject->feed / ( 60000.0 * distance);	/* [m/s] / [m] */
  if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
    printf( "Request: total distance = %1.6lf [mm], vector velocity = %1.3lf [mm/s] => est. time = %1.3lf [ms]\n",
	    SI2MM( distance), SI2MS( traject->feed / 60000.0), SI2MS( RECIPR( recipr_dt)));
  }
  int v_change = 0;
  double vx = dx * recipr_dt;
  if (vx > vx_max) {	  // clip feed !
    if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
      printf( "*** clipping vx (%1.6lf) to vx_max (%1.6lf)\n", vx, vx_max);
    }
    recipr_dt = vx_max / dx;
    v_change = 1;
  }
  double vy = dy * recipr_dt;
  if (vy > vy_max) {	  // clip feed !
    if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
      printf( "*** clipping vy (%1.6lf) to vy_max (%1.6lf)\n", vy, vy_max);
    }
    recipr_dt = vy_max / dy;
    v_change = 1;
  }
  double vz = dz * recipr_dt;
  if (vz > vz_max) {	  // clip feed !
    if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
      printf( "*** clipping vz (%1.6lf) to vz_max (%1.6lf)\n", vz, vz_max);
    }
    recipr_dt = vz_max / dz;
    v_change = 1;
  }
  double ve = de * recipr_dt;
  if (ve > ve_max) {	  // clip feed !
    if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
      printf( "*** clipping ve (%1.6lf) to ve_max (%1.6lf)\n", ve, ve_max);
    }
    recipr_dt = ve_max / de;
    v_change = 1;
  }
 /*
  * If one or more velocity were limited by its maximum,
  * some of the other values may be incorrect. Recalculate all.
  */
  if (v_change) {
    if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
      printf( "Velocity changed to %1.3lf [mm/s] and duration to %1.3lf [ms] due to this clipping\n",
	      SI2MM( distance * recipr_dt), SI2MS( RECIPR( recipr_dt)));
    }
    vx = dx * recipr_dt;
    vy = dy * recipr_dt;
    vz = dz * recipr_dt;
    ve = de * recipr_dt;
  }
  if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
    printf( "Velocities - X: %1.3lf, Y: %1.3lf, Z %1.3lf, E: %1.3lf [mm/s]\n",
	    SI2MM( vx), SI2MM( vy), SI2MM( vz), SI2MM( ve));
  }
 /*
  * For a neat linear move, all ramps must start and end at the same moment
  * and have constant (or synchronized) accelation.
  * Now that the targeted velocity is now known for each axis, determine
  * how long it takes for that axis to reach its target speed using maximum
  * acceleration. The slowest axis then scales the acceleration used for all axes.
  */
  double tx_acc = vx * recipr_a_max_x;
  double ty_acc = vy * recipr_a_max_y;
  double tz_acc = vz * recipr_a_max_z;
  double te_acc = ve * recipr_a_max_e;
 /*
  * determine the largest period and scale the acceleration for all axes.
  */
  double t_acc = fmax( fmax( tx_acc, ty_acc), fmax( tz_acc, te_acc));
  if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
    printf( "Time needed to reach velocity: X= %1.3lf, Y= %1.3lf, Z= %1.3lf, E= %1.3lf => MAX= %1.3lf [ms]\n",
	   SI2MS( tx_acc), SI2MS( ty_acc), SI2MS( tz_acc), SI2MS( te_acc), SI2MS( t_acc));
  }
  double recipr_t_acc = 1.0 / t_acc;
  double ax = vx * recipr_t_acc;
  double ay = vy * recipr_t_acc;
  double az = vz * recipr_t_acc;
  double ae = ve * recipr_t_acc;
  if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
    printf( "Synchronized acceleration constants: X= %1.3lf, Y= %1.3lf, Z= %1.3lf, E= %1.3lf [m/s^2]\n", 
	    ax, ay, az, ae);
  }
 /*
  *  Length of acceleration/deceleration traject:
  *    s = v^2/2a or s = a.t^2/2
  */
  double t_square  = t_acc * t_acc;
  double double_sx = ax * t_square;
  double double_sy = ay * t_square;
  double double_sz = az * t_square;
  double double_se = ae * t_square;
  if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
    printf( "Distance to reach full speed: X= %1.6lf Y= %1.6lf Z= %1.6lf E= %1.6lf [mm]\n",
	    SI2MM( 0.5 * double_sx), SI2MM( 0.5 * double_sy), SI2MM( 0.5 * double_sz), SI2MM( 0.5 * double_se));
  }
  double ramp_dx, ramp_dy, ramp_dz, ramp_de;
  double dwell_dx, dwell_dy, dwell_dz, dwell_de;

  uint32_t c0x, c0y, c0z, c0e;
  uint32_t cminx, cminy, cminz, cmine;
  double recipr_t_move = 0.0;	// means: not set
 /*
  * Calculate the timing for all axes
  */
  AXIS_CALC( x);
  AXIS_CALC( y);
  AXIS_CALC( z);
  AXIS_CALC( e);
 /*
  * Put the sign back into the deltas
  */
  if (reverse_x) {
    ramp_dx = -ramp_dx;
    dwell_dx = -dwell_dx;
  }
  if (reverse_y) {
    ramp_dy = -ramp_dy;
    dwell_dy = -dwell_dy;
  }
  if (reverse_z) {
    ramp_dz = -ramp_dz;
    dwell_dz = -dwell_dz;
  }
  if (reverse_e) {
    ramp_de = -ramp_de;
    dwell_de = -dwell_de;
  }
  if (DEBUG_TRAJECT && (debug_flags & DEBUG_TRAJECT)) {
    printf( "Ramps: X= %1.6lf, Y= %1.6lf, Z= %1.6lf, E= %1.6lf [mm], ramp duration= %1.3lf [ms]\n",
	    SI2MM( ramp_dx), SI2MM( ramp_dy), SI2MM( ramp_dz), SI2MM( ramp_de), SI2MS( RECIPR( recipr_t_acc)));
  }

 /*
  * Up from version v3.0 of the stepper firmware, the stepper driver does acceleration
  * and deceleration timing and switching all by itself. Only one command needs to be
  * queued to accelerate from zero speed to max speed, dwell at max speed and decelerate
  * back to zero speed.
  */
  int any_move = 0;

  any_move += QUEUE_MOVE( x);
  any_move += QUEUE_MOVE( y);
  any_move += QUEUE_MOVE( z);
  any_move += QUEUE_MOVE( e);

  if (any_move) {
    pruss_queue_execute();
    any_move = 0;
  }
  if (ramp_dx != 0.0) {
    pruss_queue_adjust_for_ramp( 1, (int32_t)(1.0E9 * ramp_dx));
  }
  if (ramp_dy != 0.0) {
    pruss_queue_adjust_for_ramp( 2, (int32_t)(1.0E9 * ramp_dy));
  }
  if (ramp_dz != 0.0) {
    pruss_queue_adjust_for_ramp( 3, (int32_t)(1.0E9 * ramp_dz));
  }
  if (ramp_de != 0.0) {
    pruss_queue_adjust_for_ramp( 4, (int32_t)(1.0E9 * ramp_de));
  }
  if (config_e_axis_is_always_relative()) {
    pruss_queue_adjust_origin( 4);
  }
}