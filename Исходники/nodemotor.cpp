 /* This callback is called everytime this node's simulation starts or restarts.
  This is different from initialize() above. */
 virtual int64_t onInitialization() override {
     // Initial state and output
     x.setZero();
     velocity = 0.0;
     std::cout << "At " << currentSimulationTime() << " INIT" << std::endl;
     return 0;
 }