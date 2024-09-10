void NEWgroundoperators() {
  int i,j;
  int *domains[1000];
  int binding[1000];
  int staticrestriction[1000];
  atom *al;

  NEWpreprocessoperators();

  initactions(); /* initialize the ground action data structure */
  initatomtable(); /* initialize the tables for atoms */

  for(i=0;i<nOfSActions;i++) {
    typedvarlist *params = Sactions[i].params;
    typedvarlist *l = params;

    if(flagShowInput) {
      printf("Grounding schema %i:%s\n",i,symbol(Sactions[i].name));
      printSaction(&Sactions[i]);
    }

    /* Fetch domains of the parameters */
    nOfBindings = 0;
    while(l != NULL) {
      staticrestriction[nOfBindings] = occursinstatic(nOfBindings,Sactions[i].precon);
#ifdef DEBUG
      if(staticrestriction[nOfBindings]) {
	printf("Parameter %i is static.\n",nOfBindings);
	printSaction(&Sactions[i]);
      } else { printf("."); }
#endif
#ifdef ASSERTS
      assert(isvar(l->v));
#endif
      domains[nOfBindings] = getdomain(l->t);
      nOfBindings += 1;
      l = l->tl;
    }

#ifdef ASSERTS
    assert(nOfBindings < 100);
#endif

    /* Go through all parameter assignments and ground */

    NEWgothrough(0,i,domains,staticrestriction);

  }

  goal = NEWgroundfma(Sgoal,binding);

  /* Go through the initial state description to assign
     indices to initial state atoms. */

  al = Sinit;
  while(*al != NULL) {
    atomindex(*al,NULL);
    al = al + 1;
  }

  initialstate = (int *)malloc(sizeof(int) * nOfAtoms);
  for(i=0;i<nOfAtoms;i++) initialstate[i] = 0;

  al = Sinit;
  while(*al != NULL) {
    j = atomindex(*al,NULL);
    initialstate[j] = 1;

#ifdef ASSERTS
    assert(j>=0); assert(j<nOfAtoms);
#endif

    al = al + 1;
  }

}