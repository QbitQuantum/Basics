void run_epd_testsuite(void)
{
  FILE *testsuite;
  char readbuff[2000];
  char testname[FILENAME_MAX];
  char tempbuff[2000];
  float elapsed; 
  int nps;
  long thinktime;
	move_s comp_move;
  int tested, found;
	
  clock_t cpu_start, cpu_end;
  
  tested = 0;
  found = 0;
  
  printf("\nName of EPD testsuite: ");
  rinput(testname, STR_BUFF, stdin);
  printf("\nTime per move (s): ");
  rinput(readbuff, STR_BUFF, stdin);
  thinktime = atol(readbuff);
  printf("\n");

  thinktime *= 100;

  testsuite = fopen(testname, "r");

  while (fgets(readbuff, 2000, testsuite) != NULL)
    {
      tested++;

      setup_epd_line(readbuff);

      root_to_move = ToMove;
      
      clear_tt();
      initialize_hash();
      
      display_board(stdout, 1); 
 
      forcedwin = FALSE;    
    //  pn_time = thinktime;
    //  cpu_start = clock();
    //  proofnumbersearch();
    //  cpu_end = clock();
     // rdelay(2);
     
     elapsed = (cpu_end-cpu_start)/(double) CLOCKS_PER_SEC;
     printf("Time: %f\n", elapsed);
      
     if (interrupt()) rinput(tempbuff, STR_BUFF, stdin);
      
      fixed_time = thinktime;
      
       cpu_start = clock();
       comp_move = think();
       cpu_end = clock();
      

      printf ("\nNodes: %ld (%0.2f%% qnodes)\n", nodes,
	      (float) ((float) qnodes / (float) nodes * 100.0));
      
      elapsed = (cpu_end-cpu_start)/(float) CLOCKS_PER_SEC;
      nps = (int)((float) nodes/(float) elapsed);
      
      if (!elapsed)
	printf ("NPS: N/A\n");
      else
	printf ("NPS: %ld\n", (long int) nps);
      
      printf("ECacheProbes : %ld   ECacheHits : %ld   HitRate : %f%%\n", 
	     ECacheProbes, ECacheHits, 
	     ((float)ECacheHits/((float)ECacheProbes+1)) * 100);
      
      printf("TTStores : %ld TTProbes : %ld   TTHits : %ld   HitRate : %f%%\n", 
	     TTStores, TTProbes, TTHits, 
	     ((float)TTHits/((float)TTProbes+1)) * 100);
      
      printf("NTries : %d  NCuts : %d  CutRate : %f%%  TExt: %d\n", 
	     NTries, NCuts, (((float)NCuts*100)/((float)NTries+1)), TExt);
      
      printf("Check extensions: %ld  Razor drops : %ld  Razor Material : %ld\n", ext_check, razor_drop, razor_material);
      printf("EGTB Hits: %d  EGTB Probes: %d  Efficiency: %3.1f%%\n", EGTBHits, EGTBProbes,
             (((float)EGTBHits*100)/(float)(EGTBProbes+1)));		 
      
      printf("Move ordering : %f%%\n", (((float)FHF*100)/(float)FH+1));
      
      printf("Material score: %d   Eval : %ld\n", Material, eval());
      printf("\n");
     
      if (!forcedwin)
      {
      if(check_solution(readbuff, comp_move))
	{
	  found++;
	  printf("Solution found.\n");
	}
      else
	{
	  printf("Solution not found.\n");
	}
      }
      else
      {
	found++;
      }
      
      printf("Solved: %d/%d\n", found, tested);
      
    };
 
  printf("\n");
};