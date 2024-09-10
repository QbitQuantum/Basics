  void run(){
    long long cnt = 0;
    while(1) {
      cnt++;
      if (cnt % 1000000 == 0) {
        xprintf("."); 
        FFLUSH();
      }
      if (cnt % 10000000 == 0) {
	      highPriorityThread01.resume();
      }
    }
  }