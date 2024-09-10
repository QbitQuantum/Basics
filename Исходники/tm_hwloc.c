/* transform a tgt scotch file into a topology file*/
tm_topology_t * tgt_to_tm(char *filename, double **pcost)
{
  tm_topology_t *topology = NULL;
  FILE *pf = NULL;
  char line[1024];
  char *s = NULL;
  double *cost = NULL;
  int i;



  pf = fopen(filename,"r");
  if(!pf){
    if(get_verbose_level() >= CRITICAL)
      fprintf(stderr,"Cannot open %s\n",filename);
    exit(-1);
  }

  if(get_verbose_level() >= INFO)
    printf("Reading TGT file: %s\n",filename);


  fgets(line,1024,pf);

  s = strstr(line,"tleaf");
  if(!s){
    if(get_verbose_level() >= CRITICAL)
      fprintf(stderr,"Syntax error! %s is not a tleaf file\n",filename);
    exit(-1);
  }

  s += 5;
  while(isspace(*s))
    s++;

  topology = (tm_topology_t*)MALLOC(sizeof(tm_topology_t));
  topology->nb_levels = atoi(strtok(s," "))+1;
  topology->arity = (int*)MALLOC(sizeof(int)*topology->nb_levels);
  cost = (double*)CALLOC(topology->nb_levels,sizeof(double));

  for( i = 0 ; i < topology->nb_levels-1 ; i++ ){
    topology->arity[i] = atoi(strtok(NULL," "));
    cost[i] = atoi(strtok(NULL," "));
  }

  topology->arity[topology->nb_levels-1] = 0;
  /* cost[topology->nb_levels-1]=0; */

  /*aggregate costs*/
  for( i = topology->nb_levels-2 ; i >= 0 ; i-- )
    cost[i] += cost[i+1];

  build_synthetic_proc_id(topology);

  *pcost = cost;
  /* FREE(cost); */
  /*
  topology->arity[0]=nb_proc;
  topology->nb_levels=decompose((int)ceil((1.0*nb_obj)/nb_proc),1,topology->arity);
  printf("levels=%d\n",topology->nb_levels);
  */
  if(get_verbose_level() >= INFO)
    printf("Topology built from %s!\n",filename);


  return topology;
}