//--------------------------------------------------------------------------------------
// FUNCTION: RCCE_init
//--------------------------------------------------------------------------------------
// initialize the library and sanitize parameter list
//--------------------------------------------------------------------------------------
int RCCE_init(
  int *argc,   // pointer to argc, passed in from main program
  char ***argv // pointer to argv, passed in from main program
  ) {

  int i, ue, dummy_offset, loc, error;
#ifdef SCC
  int x, y, z;
  unsigned int physical_lockaddress;
#endif

#ifdef SHMADD
  unsigned int RCCE_SHM_BUFFER_offset ,result, rd_slot_nbr, wr_slot_nbr;
#endif
  void *nothing = NULL;
  
#ifdef SCC
  // Copperridge specific initialization...
  InitAPI(0);fflush(0);
#endif  

  // save pointer to executable name for later insertion into the argument list
  char *executable_name = (*argv)[0];

  RCCE_NP        = atoi(*(++(*argv)));  
  RC_REFCLOCKGHZ = atof(*(++(*argv)));  

  // put the participating core ids (unsorted) into an array             
  for (ue=0; ue<RCCE_NP; ue++) {
    RC_COREID[ue] = atoi(*(++(*argv)));
  }

#ifndef SCC
  // if using the functional emulator, must make sure to have read all command line 
  // parameters up to now before overwriting (shifted) first one with executable
  // name; even though argv is made firstprivate, that applies only the pointer to 
  // the arguments, not the actual data
  #pragma omp barrier
#endif
  // make sure executable name is as expected                 
  (*argv)[0] = executable_name;

  RC_MY_COREID = MYCOREID();

  // adjust apparent number of command line arguments, so it will appear to main 
  // program that number of UEs, clock frequency, and core ID list were not on
  // command line        
  *argc -= RCCE_NP+2;

  // sort array of participating phyical core IDs to determine their ranks
  RCCE_qsort((char *)RC_COREID, RCCE_NP, sizeof(int), id_compare);

  // determine rank of calling core
  for (ue=0; ue<RCCE_NP; ue++) {
    if (RC_COREID[ue] == RC_MY_COREID) RCCE_IAM = ue;
  }

#ifdef SHMADD
//   printf("Using SHMADD\n");
     RCCE_SHM_BUFFER_offset     = 0x00;
//   RCCE_SHM_BUFFER_offset     = 0x3FFFF80;
//   RCCE_SHM_BUFFER_offset   = 0x4000000;
//   RCCE_SHM_BUFFER_offset   = 0x181000;
   rd_slot_nbr=0x80;
   for(i=0; i<60; i++) {
     result  = readLUT(rd_slot_nbr);
     result -= 1;
     wr_slot_nbr = rd_slot_nbr + 4;
     writeLUT(wr_slot_nbr,result);
     rd_slot_nbr++;
   }
#endif

  // leave in one reassuring debug print
  if (DEBUG){
    printf("My rank is %d, physical core ID is %d\n", RCCE_IAM, RC_MY_COREID);
    fflush(0);
  }

  if (RCCE_IAM<0)
    return(RCCE_error_return(RCCE_debug_comm,RCCE_ERROR_CORE_NOT_IN_HOSTFILE));

#ifdef SCC
  // compute and memory map addresses of test&set registers for all participating cores 
  for (ue=0; ue<RCCE_NP; ue++) { 
    z = Z_PID(RC_COREID[ue]);
    x = X_PID(RC_COREID[ue]);
    y = Y_PID(RC_COREID[ue]);
    physical_lockaddress = CRB_ADDR(x,y) + (z==0 ? LOCK0 : LOCK1);
    virtual_lockaddress[ue] = (t_vcharp) MallocConfigReg(physical_lockaddress);
  }
#endif

  // initialize MPB starting addresses for all participating cores; allow one
  // dummy cache line at front of MPB for fooling write combine buffer in case
  // of single-byte MPB access
  RCCE_fool_write_combine_buffer = RC_COMM_BUFFER_START(RCCE_IAM);

  for (ue=0; ue<RCCE_NP; ue++) 
    RCCE_comm_buffer[ue] = RC_COMM_BUFFER_START(ue) + RCCE_LINE_SIZE;

  // gross MPB size is set equal to maximum
  RCCE_BUFF_SIZE = RCCE_BUFF_SIZE_MAX - RCCE_LINE_SIZE;

#ifdef RC_POWER_MANAGEMENT
#ifndef SCC
  // always store RPC queue data structure at beginning of usable MPB, so allocatable
  // storage needs to skip it. Only need to do this for functional emulator
  for (ue=0; ue<RCCE_NP; ue++) 
    RCCE_comm_buffer[ue] += REGULATOR_LENGTH;
  RCCE_BUFF_SIZE -= REGULATOR_LENGTH;
#endif
#endif

  // initialize RCCE_malloc
  RCCE_malloc_init(RCCE_comm_buffer[RCCE_IAM],RCCE_BUFF_SIZE);
#ifdef SHMADD

  RCCE_shmalloc_init(RC_SHM_BUFFER_START()+RCCE_SHM_BUFFER_offset ,RCCE_SHM_SIZE_MAX);
#ifdef SHMDBG
  printf("\n%d:%s:%d: RCCE_SHM_BUFFER_offset, RCCE_SHM_SIZE_MAX: % x %x\n", RCCE_IAM, 
    __FILE__,__LINE__,RCCE_SHM_BUFFER_offset ,RCCE_SHM_SIZE_MAX);
#endif
#else
  RCCE_shmalloc_init(RC_SHM_BUFFER_START(),RCCE_SHM_SIZE_MAX);
#endif

  // initialize the (global) flag bookkeeping data structure
  for (loc=0; loc<RCCE_FLAGS_PER_LINE; loc++) 
    RCCE_flags.flag[loc] = (char)((unsigned int)0);
  RCCE_flags.line_address = NULL;
  RCCE_flags.members=0;
  RCCE_flags.next=NULL;

  // create global communicator (equivalent of MPI_COMM_WORLD); this will also allocate 
  // the two synchronization flags associated with the global barrier 
  RCCE_comm_split(RCCE_global_color, nothing, &RCCE_COMM_WORLD);

  // if power management is enabled, initialize more stuff; this includes two more 
  // communicators (for voltage and frequency domains), plus two synchronization flags
  // associated with the barrier for each communicator       
#ifdef RC_POWER_MANAGEMENT
  if (error=RCCE_init_RPC(RC_COREID, RCCE_IAM, RCCE_NP)) 
       return(RCCE_error_return(RCCE_debug_RPC,error));
#endif

#ifndef GORY
  // if we use the simplified API, we need to define more flags upfront  
  for (ue=0; ue<RCCE_NP; ue++) {
    if (error=RCCE_flag_alloc(&RCCE_sent_flag[ue]))
      return(RCCE_error_return(RCCE_debug_synch,error));
    if (error=RCCE_flag_alloc(&RCCE_ready_flag[ue]))
      return(RCCE_error_return(RCCE_debug_synch,error));
  }

#endif

  return (RCCE_SUCCESS);
}