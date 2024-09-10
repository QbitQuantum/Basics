  /**
   * print_line_from_here_to_there() takes two cartesian coordinates and draws a line from one
   * to the other.  But there are really three sets of coordinates involved.  The first coordinate
   * is the present location of the nozzle.  We don't necessarily want to print from this location.
   * We first need to move the nozzle to the start of line segment where we want to print.  Once
   * there, we can use the two coordinates supplied to draw the line.
   *
   * Note:  Although we assume the first set of coordinates is the start of the line and the second
   * set of coordinates is the end of the line, it does not always work out that way.  This function
   * optimizes the movement to minimize the travel distance before it can start printing.  This saves
   * a lot of time and eleminates a lot of non-sensical movement of the nozzle.   However, it does
   * cause a lot of very little short retracement of th nozzle when it draws the very first line
   * segment of a 'circle'.   The time this requires is very short and is easily saved by the other
   * cases where the optimization comes into play.
   */
  void print_line_from_here_to_there(const float &sx, const float &sy, const float &sz, const float &ex, const float &ey, const float &ez) {
    const float dx_s = current_position[X_AXIS] - sx,   // find our distance from the start of the actual line segment
                dy_s = current_position[Y_AXIS] - sy,
                dist_start = HYPOT2(dx_s, dy_s),        // We don't need to do a sqrt(), we can compare the distance^2
                                                        // to save computation time
                dx_e = current_position[X_AXIS] - ex,   // find our distance from the end of the actual line segment
                dy_e = current_position[Y_AXIS] - ey,
                dist_end = HYPOT2(dx_e, dy_e),

                line_length = HYPOT(ex - sx, ey - sy);

    // If the end point of the line is closer to the nozzle, flip the direction,
    // moving from the end to the start. On very small lines the optimization isn't worth it.
    if (dist_end < dist_start && (SIZE_OF_INTERSECTION_CIRCLES) < abs(line_length)) {
      //if (ubl.g26_debug_flag) SERIAL_ECHOLNPGM("  Reversing start and end of print_line_from_here_to_there()");
      return print_line_from_here_to_there(ex, ey, ez, sx, sy, sz);
    }

    // Decide whether to retract.

    if (dist_start > 2.0) {
      retract_filament(destination);
      //if (ubl.g26_debug_flag) SERIAL_ECHOLNPGM("  filament retracted.");
    }
    move_to(sx, sy, sz, 0.0); // Get to the starting point with no extrusion

    const float e_pos_delta = line_length * g26_e_axis_feedrate * extrusion_multiplier;

    un_retract_filament(destination);

    //if (ubl.g26_debug_flag) {
    //  SERIAL_ECHOLNPGM("  doing printing move.");
    //  debug_current_and_destination(PSTR("doing final move_to() inside print_line_from_here_to_there()"));
    //}
    move_to(ex, ey, ez, e_pos_delta);  // Get to the ending point with an appropriate amount of extrusion
  }