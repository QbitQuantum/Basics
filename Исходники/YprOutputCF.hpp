  void jacInput(mtJacInput& J, const mtInput& input, const mtMeas& meas, double dt = 0.0) const{
    J.setZero();

    rot::EulerAnglesYprPD ypr(input.template get<mtInput::_att>());
    const double theta = ypr.pitch();
    const double phi = ypr.roll();
    const double t2 = cos(theta);
    const double t3 = 1.0/t2;
    const double t4 = cos(phi);
    const double t5 = sin(phi);
    const double t6 = sin(theta);

    J(0,0) = 0.0;
    J(0,1) = t3*t5;
    J(0,2) = t3*t4;
    J(1,0) = 0.0;
    J(1,1) = t4;
    J(1,2) = -t5;
    J(2,0) = 1.0;
    J(2,1) = t3*t5*t6;
    J(2,2) = t3*t4*t6;
  }