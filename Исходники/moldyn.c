int ComputeAvgVel( void* arg, int id ) {
  double vaverh, velocity, counter, sq;
  int    i;

  vaverh = vaver * timeStep ;
  velocity    = 0.0 ;
  counter     = 0.0 ;

  int finish;
  if (id == NTHREADS - 1) {
    finish = numMoles;
  }else {
    finish = (numMoles / NTHREADS) * (id + 1);
  }

  for (i = (numMoles / NTHREADS) * id; i < finish; i++) {
    sq = SQRT(SQR(vh[IND(0,i)]) + SQR(vh[IND(1,i)]) + SQR(vh[IND(2,i)]));

    if (sq > vaverh) {
      counter += 1.0;
    }

    velocity += sq ;
  }

  BEGIN_TRANSACTION();

  vel += (velocity/timeStep);
  count += counter;

  COMMIT_TRANSACTION();


  return 0;
}