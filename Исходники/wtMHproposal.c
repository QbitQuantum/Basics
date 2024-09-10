/*********************
 void WtMHProposalInitialize

 A helper function to process the MH_* related initialization.
*********************/
WtMHProposal *WtMHProposalInitialize(
	     char *MHProposaltype, char *MHProposalpackage, 
	       double *inputs,
	     int fVerbose,
	     WtNetwork *nwp){
  WtMHProposal *MHp = Calloc(1, WtMHProposal);

  char *fn, *sn;
  int i;
  for (i = 0; MHProposaltype[i] != ' ' && MHProposaltype[i] != 0; i++);
  MHProposaltype[i] = 0;
  /* Extract the required string information from the relevant sources */
  fn = Calloc(i+4, char);
  fn[0]='M';
  fn[1]='H';
  fn[2]='_';
  for(int j=0;j<i;j++)
    fn[j+3]=MHProposaltype[j];
  fn[i+3]='\0';
  /* fn is now the string 'MH_[name]', where [name] is MHProposaltype */
  for (i = 0; MHProposalpackage[i] != ' ' && MHProposalpackage[i] != 0; i++);
  MHProposalpackage[i] = 0;
  sn = Calloc(i+1, char);
  sn=strncpy(sn,MHProposalpackage,i);
  sn[i]='\0';
  
  /* Search for the MH proposal function pointer */
  MHp->func=(void (*)(WtMHProposal*, WtNetwork*)) R_FindSymbol(fn,sn,NULL);
  if(MHp->func==NULL){
    error("Error in MH_* initialization: could not find function %s in "
	  "namespace for package %s."
	  "Memory has not been deallocated, so restart R sometime soon.\n",fn,sn);
  }

  MHp->inputs=inputs;
  
  MHp->discord=NULL;

  /*Clean up by freeing sn and fn*/
  Free(fn);
  Free(sn);

  MHp->ntoggles=0;
  (*(MHp->func))(MHp, nwp); /* Call MH proposal function to initialize */
  MHp->toggletail = (Vertex *)Calloc(MHp->ntoggles, Vertex);
  MHp->togglehead = (Vertex *)Calloc(MHp->ntoggles, Vertex);
  MHp->toggleweight = (double *)Calloc(MHp->ntoggles, double);

  return MHp;
}