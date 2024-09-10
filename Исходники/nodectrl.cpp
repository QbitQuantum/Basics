 /* This callback is called everytime this node's simulation starts or restarts.
  This is different from initialize() above. */
 virtual void onInitialization() override {
     // Initial state and output
     x.setZero();
     command = 0.0;
     std::cout << "At " << _current_sim_time << " INIT" << std::endl;
 }