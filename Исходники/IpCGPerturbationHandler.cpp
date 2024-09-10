  bool
  CGPerturbationHandler::PerturbForSingularity(
    Number& delta_x, Number& delta_s,
    Number& delta_c, Number& delta_d)
  {
    DBG_START_METH("CGPerturbationHandler::PerturbForSingularity",
                   dbg_verbosity);

    bool retval;

    // Check for structural degeneracy
    if (hess_degenerate_ == NOT_YET_DETERMINED ||
        jac_degenerate_ == NOT_YET_DETERMINED) {
      Jnlst().Printf(J_DETAILED, J_LINEAR_ALGEBRA,
                     "Degeneracy test for hess_degenerate_ = %d and jac_degenerate_ = %d\n       test_status_ = %d\n",
                     hess_degenerate_, jac_degenerate_, test_status_);
      switch (test_status_) {
      case TEST_DELTA_C_EQ_0_DELTA_X_EQ_0:
        DBG_ASSERT(delta_x_curr_ == 0. && delta_c_curr_ == 0.);
        // in this case we haven't tried anything for this matrix yet
        if (jac_degenerate_ == NOT_YET_DETERMINED) {
          delta_d_curr_ = delta_c_curr_ = delta_cd();
          test_status_ = TEST_DELTA_C_GT_0_DELTA_X_EQ_0;
        }
        else {
          DBG_ASSERT(hess_degenerate_ == NOT_YET_DETERMINED);
          retval = get_deltas_for_wrong_inertia(delta_x, delta_s,
                                                delta_c, delta_d);
          if (!retval) {
            return false;
          }
          DBG_ASSERT(delta_c == 0. && delta_d == 0.);
          test_status_ = TEST_DELTA_C_EQ_0_DELTA_X_GT_0;
        }
        break;
      case TEST_DELTA_C_GT_0_DELTA_X_EQ_0:
        DBG_ASSERT(delta_x_curr_ == 0. && delta_c_curr_ > 0.);
        DBG_ASSERT(jac_degenerate_ == NOT_YET_DETERMINED);
        //if (!perturb_always_cd_) {
        delta_d_curr_ = delta_c_curr_ =
                          Max(delta_cd(), CGPenCq().curr_cg_pert_fact());
        //delta_d_curr_ = delta_c_curr_ =
        //                 Max(delta_cd(), CGPenCq().curr_cg_pert_fact());
        if (delta_d_curr_ < delta_cd()) {
          test_status_ = TEST_DELTA_C_EQ_0_DELTA_X_GT_0;
        }
        else {
          test_status_ = TEST_DELTA_C_GT_0_DELTA_X_GT_0;
        }
        retval = get_deltas_for_wrong_inertia(delta_x, delta_s,
                                              delta_c, delta_d);
        if (!retval) {
          return false;
        }
        /* DBG_ASSERT(delta_c == 0. && delta_d == 0.); */
        test_status_ = TEST_DELTA_C_EQ_0_DELTA_X_GT_0;
        //}
        /*
        else {
          retval = get_deltas_for_wrong_inertia(delta_x, delta_s,
                                                delta_c, delta_d);
          if (!retval) {
            return false;
          }
          DBG_ASSERT(delta_c > 0. && delta_d > 0.);
          test_status_ = TEST_DELTA_C_GT_0_DELTA_X_GT_0;
        }*/
        break;
      case TEST_DELTA_C_EQ_0_DELTA_X_GT_0:
        DBG_ASSERT(delta_x_curr_ > 0. && delta_c_curr_ == 0.);
        delta_d_curr_ = delta_c_curr_ = Max(delta_cd(), CGPenCq().curr_cg_pert_fact());
        //delta_d_curr_ = delta_c_curr_ = CGPenCq().curr_cg_pert_fact();
        retval = get_deltas_for_wrong_inertia(delta_x, delta_s,
                                              delta_c, delta_d);
        if (!retval) {
          return false;
        }
        test_status_ = TEST_DELTA_C_GT_0_DELTA_X_GT_0;
        break;
      case TEST_DELTA_C_GT_0_DELTA_X_GT_0:
        retval = get_deltas_for_wrong_inertia(delta_x, delta_s,
                                              delta_c, delta_d);
        if (!retval) {
          return false;
        }
        break;
      case NO_TEST:
        DBG_ASSERT(false && "we should not get here.");
      }
    }
    else {
      if (delta_c_curr_ > 0. || get_deltas_for_wrong_inertia_called_) {
        // If we already used a perturbation for the constraints, we do
        // the same thing as if we were encountering negative curvature
        retval = get_deltas_for_wrong_inertia(delta_x, delta_s,
                                              delta_c, delta_d);
        if (!retval) {
          Jnlst().Printf(J_DETAILED, J_LINEAR_ALGEBRA,
                         "Can't get_deltas_for_wrong_inertia for delta_x_curr_ = %e and delta_c_curr_ = %e\n",
                         delta_x_curr_, delta_c_curr_);
          return false;
        }
      }
      else {
        // Otherwise we now perturb the lower right corner
        delta_d_curr_ = delta_c_curr_ = delta_cd();

        // ToDo - also perturb Hessian?
        IpData().Append_info_string("L");
        Number curr_inf = IpCq().curr_primal_infeasibility(NORM_2);
        if (!CGPenData().NeverTryPureNewton()
            && curr_inf > mult_diverg_feasibility_tol_) {
          Number penalty = CGPenCq().compute_curr_cg_penalty_scale();
          penalty = Min(penalty_max_, Max(penalty,
                                          CGPenData().curr_kkt_penalty()));
          CGPenData().Set_kkt_penalty(penalty);
          Number mach_pro = std::numeric_limits<Number>::epsilon();
          delta_d_curr_ = delta_c_curr_ =
                            Max(1e3*mach_pro,Max(CGPenCq().curr_cg_pert_fact(),delta_cd()));
          IpData().Append_info_string("u");
        }
      }
    }

    delta_x = delta_x_curr_;
    delta_s = delta_s_curr_;
    delta_c = delta_c_curr_;
    delta_d = delta_d_curr_;

    IpData().Set_info_regu_x(delta_x);

    return true;
  }