void RKIntegratorInternal::init(){
  // Call the base class init
  IntegratorInternal::init();
  casadi_assert_message(nq_==0, "Quadratures not supported.");
  
  // Number of finite elements
  int nk = getOption("number_of_finite_elements");
  
  // Interpolation order
  int deg = getOption("interpolation_order");
  casadi_assert_message(deg==1, "Not implemented");

  // Expand f?
  bool expand_f = getOption("expand_f");

  // Size of the finite elements
  double h = (tf_-t0_)/nk;
  
  // MX version of the same
  MX h_mx = h;
    
  // Initial state
  MX Y0("Y0",nx_);
  
  // Free parameters
  MX P("P",np_);

  // Current state
  MX Y = Y0;
  
  // Dummy time
  MX T = 0;
  
  // Integrate until the end
  for(int k=0; k<nk; ++k){
    
    // Call the ode right hand side function
    vector<MX> f_in(DAE_NUM_IN);
    f_in[DAE_T] = T;
    f_in[DAE_X] = Y;
    f_in[DAE_P] = P;
    vector<MX> f_out = f_.call(f_in);
    MX ode_rhs = f_out[DAE_ODE];
    
    // Explicit Euler step
    Y += h_mx*ode_rhs;
  }
  
  // Create a function which returns the state at the end of the time horizon
  vector<MX> yf_in(2);
  yf_in[0] = Y0;
  yf_in[1] = P;
  MXFunction yf_fun(yf_in,Y);
  
  // Should the function be expanded in elementary operations?
  if(expand_f){
    yf_fun.init();
    yf_fun_ = SXFunction(yf_fun);
  } else {
    yf_fun_ = yf_fun;
  }
  
  // Set number of derivative directions
  yf_fun_.setOption("number_of_fwd_dir",getOption("number_of_fwd_dir"));
  yf_fun_.setOption("number_of_adj_dir",getOption("number_of_adj_dir"));
  
  // Initialize function
  yf_fun_.init();
}