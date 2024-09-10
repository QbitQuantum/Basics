void display_other_heuristics(tm_topology_t *topology,int N,double **comm,double **arch){
  CLOCK_T time1,time0;
  double duration; 
  int *sol;
 
  sol=(int*)malloc(sizeof(int)*N);

  map_Packed(topology,N,sol);
  printf("Packed: "); 
  print_sol(N,sol,comm,arch);



  map_RR(N,sol);
  printf("RR: "); 
  print_sol(N,sol,comm,arch);

  CLOCK(time0);
  map_MPIPP(topology,1,N,sol,comm,arch);
  CLOCK(time1);
  duration=CLOCK_DIFF(time1,time0);
  printf("MPIPP-1-D:%f\n",duration);
  printf("MPIPP-1: ");
  print_sol(N,sol,comm,arch);

  CLOCK(time0);
  map_MPIPP(topology,5,N,sol,comm,arch);
  CLOCK(time1);
  duration=CLOCK_DIFF(time1,time0);
  printf("MPIPP-5-D:%f\n",duration);
  printf("MPIPP-5: ");
  print_sol(N,sol,comm,arch);

  free(sol);
}