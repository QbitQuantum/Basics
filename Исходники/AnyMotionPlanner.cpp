  virtual int PlanMore() { 
    iterationCount++;
    if(anytime) {
      int d=qStart.n;
      Real scaleFactor = Pow(0.5,1.0/Real(d));
      planner.resolution *= scaleFactor;

      planner.SolveFMM();
    }
    else
      planner.SolveFMM();
    return -1;
  }