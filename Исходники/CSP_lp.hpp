  // destructor
  ~CSP_lp() {
    std::for_each(improving_patterns_.begin(),
		  improving_patterns_.end(), DELETEOBJECT());
    delete csproblem;
    delete colgen;
  }