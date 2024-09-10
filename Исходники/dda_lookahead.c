/**
 * \brief Join 2 moves by removing the full stop between them, where possible.
 * \details To join the moves, the deceleration ramp of the previous move and
 * the acceleration ramp of the current move are shortened, resulting in a
 * non-zero speed at that point. The target speed at the corner is already to
 * be found in dda->crossF. See dda_find_corner_speed().
 *
 * Ideally, both ramps can be reduced to actually have Fcorner at the corner,
 * but the surrounding movements might no be long enough to achieve this speed.
 * Analysing both moves to find the best result is done here.
 *
 * TODO: to achieve better results with short moves (move distance < both ramps),
 *       this function should be able to enhance the corner speed on repeated
 *       calls when reverse-stepping through the movement queue.
 *
 * \param [in] prev is the DDA structure of the move previous to the current one.
 * \param [in] current is the DDA structure of the move currently created.
 *
 * Premise: the 'current' move is not dispatched in the queue: it should remain
 * constant while this function is running.
 *
 * Note: the planner always makes sure the movement can be stopped within the
 * last move (= 'current'); as a result a lot of small moves will still limit the speed.
 */
void dda_join_moves(DDA *prev, DDA *current) {

  // Calculating the look-ahead settings can take a while; before modifying
  // the previous move, we need to locally store any values and write them
  // when we are done (and the previous move is not already active).
  uint32_t prev_F, prev_F_in_steps, prev_F_start_in_steps, prev_F_end_in_steps;
  uint32_t prev_rampup, prev_rampdown, prev_total_steps;
  uint32_t crossF, crossF_in_steps;
  uint8_t prev_id;
  // Similarly, we only want to modify the current move if we have the results of the calculations;
  // until then, we do not want to touch the current move settings.
  // Note: we assume 'current' will not be dispatched while this function runs, so we do not to
  // back up the move settings: they will remain constant.
  uint32_t this_F, this_F_in_steps, this_F_start_in_steps, this_rampup, this_rampdown, this_total_steps;
  uint8_t this_id;
  static uint32_t la_cnt = 0;     // Counter: how many moves did we join?
  #ifdef LOOKAHEAD_DEBUG
  static uint32_t moveno = 0;     // Debug counter to number the moves - helps while debugging
  moveno++;
  #endif

  // Bail out if there's nothing to join (e.g. G1 F1500).
  if ( ! prev || prev->nullmove || current->crossF == 0)
    return;

    // Show the proposed crossing speed - this might get adjusted below.
    if (DEBUG_DDA && (debug_flags & DEBUG_DDA))
      sersendf_P(PSTR("Initial crossing speed: %lu\n"), current->crossF);

  // Make sure we have 2 moves and the previous move is not already active
  if (prev->live == 0) {
    // Perform an atomic copy to preserve volatile parameters during the calculations
    ATOMIC_START
      prev_id = prev->id;
      prev_F = prev->endpoint.F;
      prev_F_start_in_steps = prev->start_steps;
      prev_F_end_in_steps = prev->end_steps;
      prev_rampup = prev->rampup_steps;
      prev_rampdown = prev->rampdown_steps;
      prev_total_steps = prev->total_steps;
      crossF = current->crossF;
      this_id = current->id;
      this_F = current->endpoint.F;
      this_total_steps = current->total_steps;
    ATOMIC_END

    // Here we have to distinguish between feedrate along the movement
    // direction and feedrate of the fast axis. They can differ by a factor
    // of 2.
    // Along direction: F, crossF.
    // Along fast axis already: start_steps, end_steps.
    //
    // All calculations here are done along the fast axis, so recalculate
    // F and crossF to match this, too.
    prev_F = muldiv(prev->fast_um, prev_F, prev->distance);
    this_F = muldiv(current->fast_um, current->endpoint.F, current->distance);
    crossF = muldiv(current->fast_um, crossF, current->distance);

    // TODO: calculate the steps from the fastest axis and not from X.
    prev_F_in_steps = ACCELERATE_RAMP_LEN(prev_F);
    this_F_in_steps = ACCELERATE_RAMP_LEN(this_F);
    crossF_in_steps = ACCELERATE_RAMP_LEN(crossF);

    // Show the proposed crossing speed - this might get adjusted below
    if (DEBUG_DDA && (debug_flags & DEBUG_DDA))
      sersendf_P(PSTR("Initial crossing speed: %lu\n"), crossF_in_steps);

    // Compute the maximum speed we can reach for crossing.
    crossF_in_steps = MIN(crossF_in_steps, this_total_steps);
    crossF_in_steps = MIN(crossF_in_steps, prev_total_steps + prev_F_start_in_steps);

    if (crossF_in_steps == 0)
      return;

    // Build ramps for previous move.
    if (crossF_in_steps == prev_F_in_steps) {
      prev_rampup = prev_F_in_steps - prev_F_start_in_steps;
      prev_rampdown = 0;
    }
    else if (crossF_in_steps < prev_F_start_in_steps) {
      uint32_t extra, limit;

      prev_rampup = 0;
      prev_rampdown = prev_F_start_in_steps - crossF_in_steps;
      extra = (prev_total_steps - prev_rampdown) >> 1;
      limit = prev_F_in_steps - prev_F_start_in_steps;
      extra = MIN(extra, limit);

      prev_rampup += extra;
      prev_rampdown += extra;
    }