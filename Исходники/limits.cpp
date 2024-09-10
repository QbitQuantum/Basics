// Homes the specified cycle axes, sets the machine position, and performs a pull-off motion after
// completing. Homing is a special motion case, which involves rapid uncontrolled stops to locate
// the trigger point of the limit switches. The rapid stops are handled by a system level axis lock
// mask, which prevents the stepper algorithm from executing step pulses. Homing motions typically
// circumvent the processes for executing motions in normal operation.
// NOTE: Only the abort runtime command can interrupt this process.
void limits_go_home(uint8_t cycle_mask)
{
  if (sys.abort) { return; } // Block if system reset has been issued.

  // Initialize homing in search mode to quickly engage the specified cycle_mask limit switches.
  bool approach = true;
  float homing_rate = settings.homing_seek_rate;
  uint8_t invert_pin, idx;
  uint8_t n_cycle = (2*N_HOMING_LOCATE_CYCLE+1);
  float target[N_AXIS];

  // Determine travel distance to the furthest homing switch based on user max travel settings.
  // NOTE: settings.max_travel[] is stored as a negative value.
  float max_travel = settings.max_travel[X_AXIS];
  if (max_travel > settings.max_travel[Y_AXIS]) { max_travel = settings.max_travel[Y_AXIS]; }
  if (max_travel > settings.max_travel[Z_AXIS]) { max_travel = settings.max_travel[Z_AXIS]; }
  max_travel *= -HOMING_AXIS_SEARCH_SCALAR; // Ensure homing switches engaged by over-estimating max travel.

  plan_reset(); // Reset planner buffer to zero planner current position and to clear previous motions.

  do {
    // Initialize invert_pin boolean based on approach and invert pin user setting.
    if (bit_isfalse(settings.flags,BITFLAG_INVERT_LIMIT_PINS)) { invert_pin = approach; }
    else { invert_pin = !approach; }

    // Set target location and rate for active axes.
    uint8_t n_active_axis = 0;
    for (idx=0; idx<N_AXIS; idx++) {
      if (bit_istrue(cycle_mask,bit(idx))) {
        n_active_axis++;
        if (!approach) { target[idx] = -max_travel; }
        else { target[idx] = max_travel; }
      } else {
        target[idx] = 0.0;
      }
    }
    if (bit_istrue(settings.homing_dir_mask,(1<<X_DIRECTION_BIT))) { target[X_AXIS] = -target[X_AXIS]; }
    if (bit_istrue(settings.homing_dir_mask,(1<<Y_DIRECTION_BIT))) { target[Y_AXIS] = -target[Y_AXIS]; }
    if (bit_istrue(settings.homing_dir_mask,(1<<Z_DIRECTION_BIT))) { target[Z_AXIS] = -target[Z_AXIS]; }

    homing_rate *= sqrt(n_active_axis); // [sqrt(N_AXIS)] Adjust so individual axes all move at homing rate.

      // Reset homing axis locks based on cycle mask.
    uint8_t axislock = 0;
    if (bit_istrue(cycle_mask,bit(X_AXIS))) { axislock |= (1<<X_STEP_BIT); }
    if (bit_istrue(cycle_mask,bit(Y_AXIS))) { axislock |= (1<<Y_STEP_BIT); }
    if (bit_istrue(cycle_mask,bit(Z_AXIS))) { axislock |= (1<<Z_STEP_BIT); }
    sys.homing_axis_lock = axislock;

    // Perform homing cycle. Planner buffer should be empty, as required to initiate the homing cycle.
    uint8_t limit_state;
    #ifdef USE_LINE_NUMBERS
    plan_buffer_line(target, homing_rate, false, HOMING_CYCLE_LINE_NUMBER); // Bypass mc_line(). Directly plan homing motion.
    #else
    plan_buffer_line(target, homing_rate, false); // Bypass mc_line(). Directly plan homing motion.
    #endif
    st_prep_buffer(); // Prep and fill segment buffer from newly planned block.
    st_wake_up(); // Initiate motion
    do {
      // Check limit state. Lock out cycle axes when they change.
      limit_state = LIMIT_PIN;
      if (invert_pin) { limit_state ^= LIMIT_MASK; }
      if (axislock & (1<<X_STEP_BIT)) {
        if (limit_state & (1<<X_LIMIT_BIT)) { axislock &= ~(1<<X_STEP_BIT); }
      }
      if (axislock & (1<<Y_STEP_BIT)) {
        if (limit_state & (1<<Y_LIMIT_BIT)) { axislock &= ~(1<<Y_STEP_BIT); }
      }
      if (axislock & (1<<Z_STEP_BIT)) {
        if (limit_state & (1<<Z_LIMIT_BIT)) { axislock &= ~(1<<Z_STEP_BIT); }
      }
      sys.homing_axis_lock = axislock;
      st_prep_buffer(); // Check and prep segment buffer. NOTE: Should take no longer than 200us.
      // Check only for user reset. No time to run protocol_execute_runtime() in this loop.
      if (sys.execute & EXEC_RESET) { protocol_execute_runtime(); return; }
    } while (STEP_MASK & axislock);

    st_reset(); // Immediately force kill steppers and reset step segment buffer.
    plan_reset(); // Reset planner buffer. Zero planner positions. Ensure homing motion is cleared.

    delay_ms(settings.homing_debounce_delay); // Delay to allow transient dynamics to dissipate.

    // Reverse direction and reset homing rate for locate cycle(s).
    homing_rate = settings.homing_feed_rate;
    approach = !approach;

  } while (n_cycle-- > 0);

  // The active cycle axes should now be homed and machine limits have been located. By
  // default, grbl defines machine space as all negative, as do most CNCs. Since limit switches
  // can be on either side of an axes, check and set axes machine zero appropriately. Also,
  // set up pull-off maneuver from axes limit switches that have been homed. This provides
  // some initial clearance off the switches and should also help prevent them from falsely
  // triggering when hard limits are enabled or when more than one axes shares a limit pin.
  for (idx=0; idx<N_AXIS; idx++) {
    // Set up pull off targets and machine positions for limit switches homed in the negative
    // direction, rather than the traditional positive. Leave non-homed positions as zero and
    // do not move them.
    // NOTE: settings.max_travel[] is stored as a negative value.
    if (cycle_mask & bit(idx)) {
      if ( settings.homing_dir_mask & get_direction_mask(idx) ) {
        target[idx] = settings.homing_pulloff+settings.max_travel[idx];
        sys.position[idx] = lround(settings.max_travel[idx]*settings.steps_per_mm[idx]);
      } else {
        target[idx] = -settings.homing_pulloff;
        sys.position[idx] = 0;
      }
    } else { // Non-active cycle axis. Set target to not move during pull-off.
      target[idx] = (float)sys.position[idx]/settings.steps_per_mm[idx];
    }
  }
  plan_sync_position(); // Sync planner position to current machine position for pull-off move.
  #ifdef USE_LINE_NUMBERS
  plan_buffer_line(target, settings.homing_seek_rate, false, HOMING_CYCLE_LINE_NUMBER); // Bypass mc_line(). Directly plan motion.
  #else
  plan_buffer_line(target, settings.homing_seek_rate, false); // Bypass mc_line(). Directly plan motion.
  #endif

  // Initiate pull-off using main motion control routines.
  // TODO : Clean up state routines so that this motion still shows homing state.
  sys.state = STATE_QUEUED;
  sys.execute |= EXEC_CYCLE_START;
  protocol_execute_runtime();
  protocol_buffer_synchronize(); // Complete pull-off motion.

  // Set system state to homing before returning.
  sys.state = STATE_HOMING;
}