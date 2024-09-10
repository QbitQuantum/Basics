static int pctldb_stat(struct pctldb_st *pctldb){

  int status;
  DB_QUEUE_STAT *qs = NULL;
  DB* dbp = pctldb->dbp;

  if((status = dbp->stat(dbp, NULL, &qs, 0)) == 0){
    pctldb->n = qs->qs_ndata;
  }

  if(qs != NULL)
    free(qs);

  return(status);
}