static void cb_idle ()
{
  if (PAUSE == state) {
    return;
  }
  if (STEP == state) {
    state = PAUSE;
  }

  //////////////////////////////////////////////////
  // beginning of "the" CHOMP iteration

  //// calculation of gradient of smoothness objective
  Vector nabla_smooth (AAR * xi + bbR);      //// changed from AA to AAR
  Vector const & xidd (nabla_smooth); // indeed, it is the same in this formulation...

  //// calculation of gradient of obstacle objective
  Vector nabla_obs (Vector::Zero (xidim));
  Vector nabla_int (Vector::Zero (xidim));
  Vector nabla_int_half (Vector::Zero (xidim/2));
  Matrix const JJ (Matrix::Identity (2, 2)); // a little silly here, as noted down.
  for (size_t iq (0); iq < nq; ++iq) {
    Vector const qq (xi.block (iq * cdim, 0, cdim, 1));
    Vector qd;
    if (iq == nq/2 - 1) {                   //// difference of end point of FIRST robot to second last point
      qd = qe1 - xi.block (iq * cdim, 0, cdim, 1);
    }
    else if (iq == nq - 1) {
      qd = qe2 - xi.block (iq * cdim, 0, cdim, 1);
    }
    else {
      qd = xi.block ((iq+1) * cdim, 0, cdim, 1) - xi.block (iq * cdim, 0, cdim, 1);
    }

    // In this case, C and W are the same, Jacobian is identity.  We
    // still write more or less the full-fledged CHOMP expressions
    // (but we only use one body point) to make subsequent extension
    // easier.
    //
    Vector const & xx (qq);
    Vector const & xd (qd);
    double const vel (xd.norm());
    if (vel < 1.0e-3) {	// avoid div by zero further down
      continue;
    }
    Vector const xdn (xd / vel);
    Vector const xdd (JJ * xidd.block (iq * cdim, 0, cdim , 1));
    Matrix const prj (Matrix::Identity (2, 2) - xdn * xdn.transpose()); // hardcoded planar case
    Vector const kappa (prj * xdd / pow (vel, 2.0));

    // Distance between corresponding trajectory points of the two robots
    if (iq < nq/2) {
      Vector dd2(2);
      dd2 = xi.block (iq * cdim, 0, cdim, 1) - xi.block (((iq * cdim) + 40), 0, cdim, 1);  // calculates the difference between every q_i and its correspondent q_n+2+i of the second robot
      double const ddnorm (dd2.norm());   // stack the distances between the two robot trajectory points in a vector
      if ((ddnorm < 1e-9)) {
        continue;
      }
      // define the cost function c(x)
      double costR (0.0);
      static double const tau (3.0);    // allowable threshold for the cost function
      if (ddnorm < 0.0) {
          costR = -ddnorm + 0.5*tau;
      }
      else if ((ddnorm >= 0) && (ddnorm <= tau)) {
          costR = (1/(2*tau)) * pow (ddnorm - tau, 2.0);
      }
      else {
          costR = 0.0;
      }
      // define the gradient cost function
      double nabla_costR = 0.0;
      if (ddnorm < 0.0) {
         nabla_costR = -1.0;
      }
      else if ((ddnorm >= 0) && (ddnorm <= tau)) {
         nabla_costR = (1/tau) * (ddnorm-tau);
      }
      else {
         nabla_costR = 0.0;
      }

      Vector vnabla_cost;
      vnabla_cost = (dd2 * nabla_costR) / ddnorm;

      nabla_int_half.block (iq * cdim, 0, cdim, 1) += JJ.transpose() * vel * (prj * vnabla_cost - costR * kappa);
      nabla_int << nabla_int_half, - nabla_int_half;
    }

    // Calculation of the cost function for nabla_obs
    Vector delta (xx - repulsor.point_);
    double const dist (delta.norm());
    static double const maxdist (4.0); // hardcoded param
    if ((dist >= maxdist) || (dist < 1e-9)) {
      continue;
    }

    static double const gain (10.0); // hardcoded param
    double const cost (gain * maxdist * pow (1.0 - dist / maxdist, 3.0) / 3.0); // hardcoded param
    delta *= - gain * pow (1.0 - dist / maxdist, 2.0) / dist; // hardcoded param

    nabla_obs.block (iq * cdim, 0, cdim, 1) += JJ.transpose() * vel * (prj * delta - cost * kappa);
  }

  //// applying the update rule
  Vector nabla_U (nabla_obs + lambda * nabla_smooth + mu * nabla_int);
  double nabla_U_norm (nabla_U.norm());
  Vector dxi (AARinv * nabla_U);
  xi -= dxi / eta;

  // Read out the convergence of nabla_U data for plotting
  if(!outFile.good()){
     cerr << "An error with opening the file is occured!" << endl;
  }

  outFile << nabla_U_norm << endl;

  // end of "the" CHOMP iteration
  //////////////////////////////////////////////////

  update_robots ();
}