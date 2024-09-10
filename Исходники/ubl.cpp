    void debug_current_and_destination(PGM_P title) {

      // if the title message starts with a '!' it is so important, we are going to
      // ignore the status of the g26_debug_flag
      if (*title != '!' && !g26_debug_flag) return;

      const float de = destination[E_AXIS] - current_position[E_AXIS];

      if (de == 0.0) return; // Printing moves only

      const float dx = destination[X_AXIS] - current_position[X_AXIS],
                  dy = destination[Y_AXIS] - current_position[Y_AXIS],
                  xy_dist = HYPOT(dx, dy);

      if (xy_dist == 0.0) return;

      const float fpmm = de / xy_dist;
      SERIAL_ECHOPAIR_F("   fpmm=", fpmm, 6);
      SERIAL_ECHOPAIR_F("    current=( ", current_position[X_AXIS], 6);
      SERIAL_ECHOPAIR_F(", ", current_position[Y_AXIS], 6);
      SERIAL_ECHOPAIR_F(", ", current_position[Z_AXIS], 6);
      SERIAL_ECHOPAIR_F(", ", current_position[E_AXIS], 6);
      SERIAL_ECHOPGM(" )   destination=( "); debug_echo_axis(X_AXIS);
      SERIAL_ECHOPGM(", "); debug_echo_axis(Y_AXIS);
      SERIAL_ECHOPGM(", "); debug_echo_axis(Z_AXIS);
      SERIAL_ECHOPGM(", "); debug_echo_axis(E_AXIS);
      SERIAL_ECHOPGM(" )   ");
      serialprintPGM(title);
      SERIAL_EOL();
    }