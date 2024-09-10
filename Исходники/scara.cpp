/**
 * Morgan SCARA Inverse Kinematics. Results in delta[].
 *
 * See http://forums.reprap.org/read.php?185,283327
 *
 * Maths and first version by QHARLEY.
 * Integrated into Marlin and slightly restructured by Joachim Cerny.
 */
void inverse_kinematics(const float (&raw)[XYZ]) {

  static float C2, S2, SK1, SK2, THETA, PSI;

  float sx = raw[X_AXIS] - SCARA_OFFSET_X,  // Translate SCARA to standard X Y
        sy = raw[Y_AXIS] - SCARA_OFFSET_Y;  // With scaling factor.

  if (L1 == L2)
    C2 = HYPOT2(sx, sy) / L1_2_2 - 1;
  else
    C2 = (HYPOT2(sx, sy) - (L1_2 + L2_2)) / (2.0 * L1 * L2);

  S2 = SQRT(1 - sq(C2));

  // Unrotated Arm1 plus rotated Arm2 gives the distance from Center to End
  SK1 = L1 + L2 * C2;

  // Rotated Arm2 gives the distance from Arm1 to Arm2
  SK2 = L2 * S2;

  // Angle of Arm1 is the difference between Center-to-End angle and the Center-to-Elbow
  THETA = ATAN2(SK1, SK2) - ATAN2(sx, sy);

  // Angle of Arm2
  PSI = ATAN2(S2, C2);

  delta[A_AXIS] = DEGREES(THETA);        // theta is support arm angle
  delta[B_AXIS] = DEGREES(THETA + PSI);  // equal to sub arm angle (inverted motor)
  delta[C_AXIS] = raw[Z_AXIS];

  /*
    DEBUG_POS("SCARA IK", raw);
    DEBUG_POS("SCARA IK", delta);
    SERIAL_ECHOLNPAIR("  SCARA (x,y) ", sx, ",", sy, " C2=", C2, " S2=", S2, " Theta=", THETA, " Phi=", PHI);
  //*/
}