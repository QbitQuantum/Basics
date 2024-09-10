    // return couplings and its beta-functions
    std::pair<SMCouplings, SMCouplings> AandB(const Rt& mu2End)
    {
    
      Rt lEnd = log(mu2End/mu0);

      bep->setEvolutionDirection(lEnd < 0);

      // Integration parameters
      // 
      // For the Runge-Kutta controller the error made during one step
      // is compared with 
      //    eps_abs + eps_rel * ( ax * |x| + adxdt * dt * |dxdt| ). 
      // If the error is smaller than this value the current
      // step is accepted, otherwise it is rejected and the step size is decreased.
      SMCouplings::value_type abs_err = 1.0e-12 , rel_err = 1.0e-5 , a_x = 1.0 , a_dxdt = 1.0;
      SMCouplings aSM(aSM0);

      controlled_stepper_type 
        controlled_stepper(default_error_checker< SMCouplings::value_type , range_algebra , default_operations >
                           ( abs_err , rel_err , a_x , a_dxdt ) );
    
      integrate_adaptive( controlled_stepper , // Stepper function
                          *bep,                // Derivatives
                          aSM,                 // Initial values
                          Rt(0.0),             // t0 = Log[mu0/mu0]
                          Rt(fabs(lEnd)),      // t  = Log[mu/mu0]
                          Rt(0.001)            // Initial step size
                          );

      // beta-functions
      SMCouplings bSM(aSM0.size());

      bep->operator()(aSM,bSM,0);
    
      return std::make_pair(aSM,bSM); 
    }