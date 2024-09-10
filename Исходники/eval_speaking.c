int main(int argc,char *argv[])
{
  char euclid_output[100],target_output[100];
  Real sse;
  FILE *f;
  Real clampNoise=0.1;
  char feature[1000][30];
  char name[255];
  int time=4;
  int wrongs=0,wrong=0,wrongtot;
  char weightFile[4000];
  int reset=1;
  ExampleSet *examples;
  Example *ex;
  int i,count;
  Real error;
  Real epsilon,range;
  int runfor=TICKS;


  f=fopen("key","r");
  if (f==NULL)
    {
      fprintf(stderr,"can't open key file\n");
      exit(-1);
    }

  i=0;
  fscanf(f,"%s",feature[i++]);
  while(!feof(f))
    fscanf(f,"%s",feature[i++]);
  fclose(f);

  /* don't buffer output */
  setbuf(stdout,NULL);

  /* set random number seed to process id
     (only unix machines have getpid call) */
#ifdef unix
  mikenet_set_seed(getpid()); 
#endif

  /* a default learning rate */
  epsilon=0.01;
  
  /* default weight range */
  range=0.01;

  /* what are the command line arguments? */
  for(i=1;i<argc;i++)
    {
      if (strcmp(argv[i],"-seed")==0)
	{
	  mikenet_set_seed(atol(argv[i+1]));
	  i++;
	}
      else if (strncmp(argv[i],"-epsilon",5)==0)
	{
	  epsilon=atof(argv[i+1]);
	  i++;
	}
      else if (strcmp(argv[i],"-clampNoise")==0)
	{
	  clampNoise=atof(argv[i+1]);
	  i++;
	}
      else if (strncmp(argv[i],"-noreset",5)==0)
	{
	  reset=0;
	}
      else if (strncmp(argv[i],"-runfor",5)==0)
	{
	  runfor=atoi(argv[i+1]);
	  i++;
	}
      else if (strncmp(argv[i],"-time",5)==0)
	{
	  time=atoi(argv[i+1]);
	  i++;
	}
      else if (strcmp(argv[i],"-range")==0)
	{
	  range=atof(argv[i+1]);
	  i++;
	}
      else if ((strncmp(argv[i],"-weight",5)==0) ||
	       (strncmp(argv[i],"-load",5)==0))
	{
	  strcpy(weightFile,argv[i+1]);
	  i++;
	}
      else if (strcmp(argv[i],"-errorRadius")==0)
	{
	  default_errorRadius=atof(argv[i+1]);
	  i++;
	}
      else
	{
	  fprintf(stderr,"unknown argument: %s\n",argv[i]);
	  exit(-1);
	}
    }

  build_hearing_model();
  hearing->integrationConstant=(float)time/(float)TICKS;
  hearing->runfor=runfor;
  sp->integrationConstant=(float)time/(float)TICKS;
  sp->runfor=runfor;

  examples=load_examples("sp.pat",TICKS);
  load_weights(hearing,weightFile);

  load_phonemes();

  error=0.0;
  count=1;
  wrongs=0;
  wrongtot=0;
  /* loop for ITER number of times */
  for(i=0;i<examples->numExamples;i++)
    {
      /* get j'th example from exampleset */
      ex=&examples->examples[i];
      get_name(ex->name,name);
      printf("%s\t",name);
      /* do forward propagation */
      crbp_forward(sp,ex);
      wrong=0;
      sse=0.0;
      euclid(phonology->outputs[runfor-1],euclid_output);
      printf("%s\t",euclid_output);
      euclid(ex->targets[phonology->index][runfor-1],target_output);
      printf("%s\t",target_output);
      if (strcmp(target_output,euclid_output)!=0)
	{
	  printf("[WRONG]\n");
	  wrongs++;
	}
      else printf("\n");
    }
  printf("%d wrong\n",wrongs);
  return 0;
}