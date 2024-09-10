int main (int argc, char **argv)
{
  unsigned int L1_CacheSize; /* L1 data cache size in bytes */
  unsigned int L2_CacheSize; /* L2 data cache size in bytes */
  float Target_IPC = 0.5;
  float Target_MEM = 0.01;
  int IPC_weight = 5, Dcache_weight = 5;

  /* dcache vars */
  unsigned int * data;
  int i;         /* loop counter */
  unsigned int dataSize;  /* Size of the data array */
  unsigned int nextInd, prevInd; /* array indicies */
  register int bench_index;
  register unsigned int array_index;
  int dumb = 1;
  
  /* vary IPC vars */
  int a[100]; int pos = 0;
  int int1=1,int2=2,int3=3;
  double fp1=1.0, fp2=2.0, fp3=3.0;
  int d_low; int loopcount_hiIPC, loopcount_loIPC;
  
  
  /* 1) READ RATES */
  /*********************************************************************/
  if (argc != 7)
  {
    fprintf(stderr, "\nUsage: %s -I <IPC [0.0-2.0] > -M <Mem/Uop rate [0.0-0.060]> -W <Proportion of IPC loop [0-10]int> \n", argv[0]);
    fprintf(stderr, "i.e. %s -I 0.5 -M 0.020 -W 5\n\n", argv[0]);
    fprintf(stderr, "   Proportion of IPC loop: How much of the constructed bench mixture should be IPC varying bench.\n");  
    fprintf(stderr, "   For example,  5 means,  50%% varyIPC &  50%% Dcache.\n");  
    fprintf(stderr, "                 0 means,   0%% varyIPC & 100%% Dcache --> pure dcache bench.\n");  
    fprintf(stderr, "   For example, 10 means, 100%% varyIPC &   0%% Dcache --> pure vary IPC bench.\n");  
    exit(1);
  }
  
  if (strcmp(argv[1], "-I") == 0)
  {
    Target_IPC = atof(argv[2]);
    //printf("%.20f", Target_IPC);
  }
  else
  {
    fprintf(stderr,"\n\n\tDON't UNDERSTAND OPTION %s %s..\n", argv[1], argv[2]);
    fprintf(stderr,"\n\n\tShould be: -I <IPC> \n");
    exit(2);
  }

  if (strcmp(argv[3], "-M") == 0)
  {
    Target_MEM = atof(argv[4]);
    //printf("%.20f", Target_MEM);
  }
  else
  {
    fprintf(stderr,"\n\n\tDON't UNDERSTAND OPTION %s %s..\n", argv[3], argv[4]);
    fprintf(stderr,"\n\n\tShould be: -M <Mem Rate> \n");
    exit(2);
  }

  if (strcmp(argv[5], "-W") == 0)
  {
    IPC_weight = atoi(argv[6]);
    if ( (IPC_weight >= 0) && (IPC_weight <= 10) )
    {
      Dcache_weight = 10 - IPC_weight;
    }
    else {
      fprintf(stderr,"\n\n IPC loop proportion should be between [0,10]; NOT %d\n", IPC_weight);
    }
  }
  else
  {
    fprintf(stderr,"\n\n\tDON't UNDERSTAND OPTION %s %s..\n", argv[5], argv[6]);
    fprintf(stderr,"\n\n\tShould be: -W <Proportion of IPC loop> \n");
    exit(2);
  }
  /*********************************************************************/

  fprintf (stderr,"L1 Data Cache Size in bytes: (32K)\n");
  L1_CacheSize = 32*1024;
  /*scanf ("%d", &L1_CacheSize);*/
  fprintf (stderr,"L2 Data Cache Size in bytes: (1024K)\n");
  L2_CacheSize = 1024*1024;
  

  /*******************************************************************/
  /* Initialize hi & lo IPC loop weights, a array */
  /*******************************************************************/
  if ( (Target_IPC > 2.1) || (Target_IPC < 0.0) )
  {
    fprintf(stderr, "Target IPC (%f) Out of [0.0-2.0] range man chill out!\n", Target_IPC);
    exit(-1);
  }
  loopcount_hiIPC = MIN ( (int) ((Target_IPC/2.0)*1000.0), 1000);
  loopcount_loIPC = 1000 - loopcount_hiIPC;
  
  a[pos] = 4396; a[pos+1] = 155;
  /*######################################################################**/

  /*******************************************************************/
  /* Initialize THe Array Data */
  /*******************************************************************/
  if (Target_MEM < 0.0001)
  {
    dataSize = (unsigned int) (L1_CacheSize / 32); /*800% L1 hit rate*/
  }
  else if (Target_MEM < 0.045) 
  {
    dataSize = (unsigned int) ( 16379854.1665904*Target_MEM + 87223.0988672634 ); /* from piecewise curve fit */
  }
  else if (Target_MEM < 0.061) 
  {
    dataSize = (unsigned int) ( 287285513.968285*Target_MEM - 12408337.3961814 );/* from piecewise curve fit */
  }
  else 
  {
    fprintf(stderr, "TOO HIGH MEM RATE! Get Your act together!\n");
    exit(1);
  }

  data = (unsigned int *) malloc (sizeof (unsigned int) * dataSize); /*our huge array*/
  /* initially all -1*/
  for (i=0; i<dataSize; i++)
    data [i] = -1;
  /* assign the linked list type of values */
  prevInd = 0;
  for (i=0; i<dataSize-1; i++)
  /* each loop assignes 1 element do the whole thing assignes dataSize -1 elements */
  {
    /* find the 1st unassigned element (still -1) */
    do
    {
      nextInd = ((rand () << 15) | rand ()) % dataSize;
    } while (data[nextInd] != -1);
    data[prevInd] = nextInd; /* old element's value is new index */
    prevInd = nextInd;
  }
  data[prevInd] = 0; /* last element goes back to first */

  fprintf (stderr,"Done Initializing the Array!\n");
  /*######################################################################**/

  /*--------------------------------------------------------------*/
  /* Main Benchmark Loop */
  /*--------------------------------------------------------------*/
  array_index = 0; /* move Dcache array index out of main looop */
  
  for (bench_index=0; bench_index<3000; bench_index++)
  {

  /* Hi IPC loop */
    //fprintf(stderr, "\tIPC: 1.9 \n");
    i = 0;
    while (i<loopcount_hiIPC*IPC_weight*8) /* x8 to balance loop weights */
    {
       //fprintf(stdout, "pos: %d, a[pos]: %d, a[pos+1]: %d\n",pos, a[pos], a[pos+1]);getchar();	
       int1 = int1 + 1;
       int2 = a[pos] + a[pos+1];
       int3 = int1 + int2;
       int1 = int1 + 1;
       int2 = a[pos] + a[pos+1];
       int3 = int1 + int2;
       int1 = int1 + 1;
       int2 = a[pos] + a[pos+1];
       int3 = int1 + int2;
       a[pos] = int3;
       i ++;
       //fprintf(stdout, "pos: %d, a[pos]: %d, a[pos+1]: %d\n",pos, a[pos], a[pos+1]);getchar();	
    }

    /* Lo IPC loop */
    //fprintf(stderr, "\tIPC:0.1 \n");
    d_low = 0;
    while(d_low < loopcount_loIPC*IPC_weight)
    {
      // fprintf(stderr, "%.20f %.20f %.20f\n", fp1, fp2, fp3); getchar();
      fp1 = fp2 / fp3;
      fp2 = fp3 / fp1;
      fp3 = fp1 / fp2;
      fp1 = fp3 / fp2;
      fp2 = fp1 / fp3;
      fp3 = fp2 / fp1;
      fp1 = fp1 / 0.03292181069958847323;
      fp2 = fp2 / 0.22222222222222220989 / 0.5;
      fp3 = fp3 / 6.75000000000000088818 / 0.33333333333333333333;

      d_low = d_low+1;
    }

    /*  Dcache loop */
    for (i=0; i<10000*Dcache_weight; i++)
    {
      array_index = data[array_index];
      dumb = dumb + 1;
    }	
  } 
  /* EO MAIN BENCHMARK LOOP */
  fprintf(stdout, "dcache_iter/big_bench_loop_iter = %d/%d\n", dumb, bench_index);

  return 0;
}