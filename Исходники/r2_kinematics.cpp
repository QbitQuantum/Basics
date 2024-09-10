int __attribute__((optimize("0"))) inv_kin(tf::Transform in_T06, l_r in_arm, ik_solution iksol[8]) {
  dh_theta = robot_thetas[in_arm];
  dh_d = ds[in_arm];
  dh_alpha = alphas[in_arm];
  dh_a = aas[in_arm];
  for (int i = 0; i < 8; i++) iksol[i] = ik_zerosol;

  if (in_arm >= dh_l_r_last) {
    ROS_ERROR("BAD ARM IN IK!!!");
    return -1;
  }

  for (int i = 0; i < 8; i++) iksol[i].arm = in_arm;

  //  Step 1, Compute P5
  tf::Transform T60 = in_T06.inverse();
  tf::Vector3 p6rcm = T60.getOrigin();
  tf::Vector3 p05[8];

  p6rcm[2] = 0;  // take projection onto x-y plane
  for (int i = 0; i < 2; i++) {
    tf::Vector3 p65 = (-1 + 2 * i) * Lw * p6rcm.normalize();
    p05[4 * i] = p05[4 * i + 1] = p05[4 * i + 2] = p05[4 * i + 3] = in_T06 * p65;
  }

  //  Step 2, compute displacement of prismatic joint d3
  for (int i = 0; i < 2; i++) {
    double insertion = 0;
    insertion += p05[4 * i].length();  // Two step process avoids compiler
                                       // optimization problem. (Yeah, right. It
                                       // was the compiler's problem...)

    if (insertion <= Lw) {
      cerr << "WARNING: mechanism at RCM singularity(Lw:" << Lw << "ins:" << insertion
           << ").  IK failing.\n";
      iksol[4 * i + 0].invalid = iksol[4 * i + 1].invalid = ik_invalid;
      iksol[4 * i + 2].invalid = iksol[4 * i + 3].invalid = ik_invalid;
      return -2;
    }
    iksol[4 * i + 0].d3 = iksol[4 * i + 1].d3 = -d4 - insertion;
    iksol[4 * i + 2].d3 = iksol[4 * i + 3].d3 = -d4 + insertion;
  }

  //  Step 3, calculate theta 2
  for (int i = 0; i < 8; i += 2)  // p05 solutions
  {
    double z0p5 = p05[i][2];

    double d = iksol[i].d3 + d4;
    double cth2 = 0;

    if (in_arm == dh_left)
      cth2 = 1 / (GM1 * GM3) * ((-z0p5 / d) - GM2 * GM4);
    else
      cth2 = 1 / (GM1 * GM3) * ((z0p5 / d) + GM2 * GM4);

    // Smooth roundoff errors at +/- 1.
    if (cth2 > 1 && cth2 < 1 + eps)
      cth2 = 1;
    else if (cth2 < -1 && cth2 > -1 - eps)
      cth2 = -1;

    if (cth2 > 1 || cth2 < -1) {
      iksol[i].invalid = iksol[i + 1].invalid = ik_invalid;
    } else {
      iksol[i].th2 = acos(cth2);
      iksol[i + 1].th2 = -acos(cth2);
    }
  }

  //  Step 4: Compute theta 1
  for (int i = 0; i < 8; i++) {
    if (iksol[i].invalid == ik_invalid) continue;

    double cth2 = cos(iksol[i].th2);
    double sth2 = sin(iksol[i].th2);
    double d = iksol[i].d3 + d4;
    double BB1 = sth2 * GM3;
    double BB2 = 0;
    tf::Matrix3x3 Bmx;  // using 3 vector and matrix bullet types for convenience.
    tf::Vector3 xyp05(p05[i]);
    xyp05[2] = 0;

    if (in_arm == dh_left) {
      BB2 = cth2 * GM2 * GM3 - GM1 * GM4;
      Bmx.setValue(BB1, BB2, 0, -BB2, BB1, 0, 0, 0, 1);
    } else {
      BB2 = cth2 * GM2 * GM3 + GM1 * GM4;
      Bmx.setValue(BB1, BB2, 0, BB2, -BB1, 0, 0, 0, 1);
    }

    tf::Vector3 scth1 = Bmx.inverse() * xyp05 * (1 / d);
    iksol[i].th1 = atan2(scth1[1], scth1[0]);
  }

  //  Step 5: get theta 4, 5, 6
  for (int i = 0; i < 8; i++) {
    if (iksol[i].invalid == ik_invalid) continue;

    // compute T03:
    dh_theta[0] = iksol[i].th1;
    dh_theta[1] = iksol[i].th2;
    dh_d[2] = iksol[i].d3;
    tf::Transform T03 = getFKTransform(0, 3);
    tf::Transform T36 = T03.inverse() * in_T06;

    double c5 = -T36.getBasis()[2][2];
    double s5 = (T36.getOrigin()[2] - d4) / Lw;

    // Compute theta 4:
    double c4, s4;
    if (fabs(c5) > eps) {
      c4 = T36.getOrigin()[0] / (Lw * c5);
      s4 = T36.getOrigin()[1] / (Lw * c5);
    } else {
      c4 = T36.getBasis()[0][2] / s5;
      s4 = T36.getBasis()[1][2] / s5;
    }
    iksol[i].th4 = atan2(s4, c4);

    // Compute theta 5:
    iksol[i].th5 = atan2(s5, c5);

    // Compute theta 6:
    double s6, c6;
    if (fabs(s5) > eps) {
      c6 = T36.getBasis()[2][0] / s5;
      s6 = -T36.getBasis()[2][1] / s5;
    } else {
      dh_theta[3] = iksol[i].th4;
      dh_theta[4] = iksol[i].th5;
      tf::Transform T05 = T03 * getFKTransform(3, 5);
      tf::Transform T56 = T05.inverse() * in_T06;
      c6 = T56.getBasis()[0][0];
      s6 = T56.getBasis()[2][0];
    }
    iksol[i].th6 = atan2(s6, c6);

    //		if (gTime%1000 == 0 && in_arm == dh_left )
    //		{
    //			log_msg("dh_iksols: [%d]\t( %3f,\t %3f,\t %3f,\t %3f,\t %3f,\t
    //%3f)",0,
    //					iksol[i].th1 * r2d,
    //					iksol[i].th2 * r2d,
    //					iksol[i].d3,
    //					iksol[i].th4 * r2d,
    //					iksol[i].th5 * r2d,
    //					iksol[i].th6 * r2d
    //					);
    //		}
  }
  return 0;
}