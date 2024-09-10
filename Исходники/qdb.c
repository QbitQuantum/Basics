static int qdb_stat(struct nbspq_st *nbspq){

  int status;
  DB_QUEUE_STAT *qs = NULL;
  DB* dbp = nbspq->dbp;

  if((status = dbp->stat(dbp, NULL, &qs, 0)) == 0){
    nbspq->n = qs->qs_ndata;
  }

  if(qs != NULL)
    free(qs);
  
  return(status);
}