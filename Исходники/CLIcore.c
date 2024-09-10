/*^-----------------------------------------------------------------------------
| void main_init : Initialization the "data" structure  
| 
| 
|
|
+-----------------------------------------------------------------------------*/
void main_init()
{

  long tmplong;
  int i;
  struct timeval t1;

   
  /* initialization of the data structure 
   */
  data.quiet           = 1;
  data.NB_MAX_IMAGE    = 5000;
  data.NB_MAX_VARIABLE = 5000;
  data.INVRANDMAX      = 1.0/RAND_MAX;
  

  // initialize modules
  data.NB_MAX_MODULE = 100;
  data.module = (MODULE*) malloc(sizeof(MODULE)*data.NB_MAX_MODULE);
  

  // initialize commands
  data.NB_MAX_COMMAND = 5000;
  if(data.Debug>0)
    {
      printf("Allocating cmd array : %ld\n", data.NB_MAX_COMMAND*sizeof(CMD));
      fflush(stdout);
    }
  data.cmd = (CMD*) malloc(sizeof(CMD)*data.NB_MAX_COMMAND);
  data.NBcmd = 0;
  
  data.cmdNBarg = 0;

  // Allocate data.image
  data.image           = (IMAGE*) calloc(data.NB_MAX_IMAGE, sizeof(IMAGE));
  if(data.image==NULL)  {
    printERROR(__FILE__,__func__,__LINE__,"Allocation of data.image has failed - exiting program");
    exit(0);
  }
  if(data.Debug>0)
    {
      printf("Allocation of data.image completed %p\n", data.image);
      fflush(stdout);
    }






  // Allocate data.variable
  data.variable = (VARIABLE*) calloc(data.NB_MAX_VARIABLE, sizeof(VARIABLE));
  if(data.variable==NULL)  {
    printERROR(__FILE__,__func__,__LINE__,"Allocation of data.variable has failed - exiting program");       
    exit(0);
  }
  
  data.image[0].used   = 0;
  data.image[0].shmfd  = -1;
  tmplong              = data.NB_MAX_VARIABLE;
  data.NB_MAX_VARIABLE = data.NB_MAX_VARIABLE + NB_VARIABLES_BUFFER_REALLOC ;
  
  // 
  data.variable = (VARIABLE *) realloc(data.variable, data.NB_MAX_VARIABLE*sizeof(VARIABLE));
  for(i=tmplong;i<data.NB_MAX_VARIABLE;i++)
	{
		data.variable[i].used = 0;
		data.variable[i].type = 0; /** defaults to floating point type */
	}
  
  
  tmplong = data.NB_MAX_VARIABLE;
  if (data.variable == NULL)   {
    printERROR(__FILE__,__func__,__LINE__,"Reallocation of data.variable has failed - exiting program");
    exit(0);
  }
  
  
  
 


  create_variable_ID("_PI",3.14159265358979323846264338328);
  create_variable_ID("_e",exp(1));
  create_variable_ID("_gamma",0.5772156649);
  create_variable_ID("_c",299792458.0);
  create_variable_ID("_h",6.626075540e-34);
  create_variable_ID("_k",1.38065812e-23);
  create_variable_ID("_pc",3.0856776e16);
  create_variable_ID("_ly",9.460730472e15);
  create_variable_ID("_AU",1.4959787066e11);




	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);
//	printf("RAND: %ld\n", t1.tv_usec * t1.tv_sec);
//  srand(time(NULL));





  strcpy(data.cmd[data.NBcmd].key,"exit");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = exitCLI;
  strcpy(data.cmd[data.NBcmd].info,"exit program (same as quit command)");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"exit");
  strcpy(data.cmd[data.NBcmd].Ccall,"exitCLT");
  data.NBcmd++;

  strcpy(data.cmd[data.NBcmd].key,"quit");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = exitCLI;
  strcpy(data.cmd[data.NBcmd].info,"quit program (same as exit command)");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"quit");
  strcpy(data.cmd[data.NBcmd].Ccall,"exitCLI");
  data.NBcmd++;

  strcpy(data.cmd[data.NBcmd].key,"exitCLI");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = exitCLI;
  strcpy(data.cmd[data.NBcmd].info,"quit program (same as exit command)");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"quit");
  strcpy(data.cmd[data.NBcmd].Ccall,"exitCLI");
  data.NBcmd++;





  strcpy(data.cmd[data.NBcmd].key,"help");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = help;
  strcpy(data.cmd[data.NBcmd].info,"print help");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"help");
  strcpy(data.cmd[data.NBcmd].Ccall,"int help()");
  data.NBcmd++;

  strcpy(data.cmd[data.NBcmd].key,"?");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = help;
  strcpy(data.cmd[data.NBcmd].info,"print help");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"help");
  strcpy(data.cmd[data.NBcmd].Ccall,"int help()");
  data.NBcmd++;


  strcpy(data.cmd[data.NBcmd].key,"helprl");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = helpreadline;
  strcpy(data.cmd[data.NBcmd].info,"print readline help");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"helprl");
  strcpy(data.cmd[data.NBcmd].Ccall,"int helpreadline()");
  data.NBcmd++;
  
  strcpy(data.cmd[data.NBcmd].key,"cmd?");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = help_cmd;
  strcpy(data.cmd[data.NBcmd].info,"list commands");
  strcpy(data.cmd[data.NBcmd].syntax,"command name (optional)");
  strcpy(data.cmd[data.NBcmd].example,"cmd?");
  strcpy(data.cmd[data.NBcmd].Ccall,"int help_cmd()");
  data.NBcmd++;

  strcpy(data.cmd[data.NBcmd].key,"m?");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = help_module;
  strcpy(data.cmd[data.NBcmd].info,"list commands in a module");
  strcpy(data.cmd[data.NBcmd].syntax,"module name");
  strcpy(data.cmd[data.NBcmd].example,"m? COREMOD_memory.c");
  strcpy(data.cmd[data.NBcmd].Ccall,"int list_commands_module()");
  data.NBcmd++;

  strcpy(data.cmd[data.NBcmd].key,"ci");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = printInfo;
  strcpy(data.cmd[data.NBcmd].info,"Print version, settings, info and exit");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"ci");
  strcpy(data.cmd[data.NBcmd].Ccall,"int printInfo()");
  data.NBcmd++;

  strcpy(data.cmd[data.NBcmd].key,"dpsingle");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = set_default_precision_single;
  strcpy(data.cmd[data.NBcmd].info,"Set default precision to single");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"dpsingle");
  strcpy(data.cmd[data.NBcmd].Ccall,"data.precision = 0");
  data.NBcmd++;

  strcpy(data.cmd[data.NBcmd].key,"dpdouble");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = set_default_precision_double;
  strcpy(data.cmd[data.NBcmd].info,"Set default precision to doube");
  strcpy(data.cmd[data.NBcmd].syntax,"no argument");
  strcpy(data.cmd[data.NBcmd].example,"dpdouble");
  strcpy(data.cmd[data.NBcmd].Ccall,"data.precision = 1");
  data.NBcmd++;

  strcpy(data.cmd[data.NBcmd].key,"usleep");
  strcpy(data.cmd[data.NBcmd].module,__FILE__);
  data.cmd[data.NBcmd].fp = cfits_usleep_cli;
  strcpy(data.cmd[data.NBcmd].info,"usleep");
  strcpy(data.cmd[data.NBcmd].syntax,"<us>");
  strcpy(data.cmd[data.NBcmd].example,"usleep 1000");
  strcpy(data.cmd[data.NBcmd].Ccall,"usleep(long tus)");
  data.NBcmd++;

  

  init_modules();

  printf("LOADED: %ld modules, %ld commands\n", data.NBmodule, data.NBcmd);
  
}