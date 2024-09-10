/*************************************************************************
* This function balances two partitions by moving the highest gain 
* (including negative gain) vertices to the other domain.
* It is used only when tha unbalance is due to non contigous
* subdomains. That is, the are no boundary vertices.
* It moves vertices from the domain that is overweight to the one that 
* is underweight.
**************************************************************************/
void MocInit2WayBalance(CtrlType *ctrl, GraphType *graph, float *tpwgts)
{
  int i, ii, j, k, l, kwgt, nvtxs, nbnd, ncon, nswaps, from, to, pass, me, cnum, tmp;
  idxtype *xadj, *adjncy, *adjwgt, *where, *id, *ed, *bndptr, *bndind;
  idxtype *perm, *qnum;
  float *nvwgt, *npwgts;
  PQueueType parts[MAXNCON][2];
  int higain, oldgain, mincut;

  nvtxs = graph->nvtxs;
  ncon = graph->ncon;
  xadj = graph->xadj;
  adjncy = graph->adjncy;
  nvwgt = graph->nvwgt;
  adjwgt = graph->adjwgt;
  where = graph->where;
  id = graph->id;
  ed = graph->ed;
  npwgts = graph->npwgts;
  bndptr = graph->bndptr;
  bndind = graph->bndind;

  perm = idxwspacemalloc(ctrl, nvtxs);
  qnum = idxwspacemalloc(ctrl, nvtxs);

  /* This is called for initial partitioning so we know from where to pick nodes */
  from = 1;
  to = (from+1)%2;

  if (ctrl->dbglvl&DBG_REFINE) {
    printf("Parts: [");
    for (l=0; l<ncon; l++)
      printf("(%.3f, %.3f) ", npwgts[l], npwgts[ncon+l]);
    printf("] T[%.3f %.3f], Nv-Nb[%5d, %5d]. ICut: %6d, LB: %.3f [B]\n", tpwgts[0], tpwgts[1], 
           graph->nvtxs, graph->nbnd, graph->mincut, 
           Compute2WayHLoadImbalance(ncon, npwgts, tpwgts));
  }

  for (i=0; i<ncon; i++) {
    PQueueInit(ctrl, &parts[i][0], nvtxs, PLUS_GAINSPAN+1);
    PQueueInit(ctrl, &parts[i][1], nvtxs, PLUS_GAINSPAN+1);
  }

  ASSERT(ComputeCut(graph, where) == graph->mincut);
  ASSERT(CheckBnd(graph));
  ASSERT(CheckGraph(graph));

  /* Compute the queues in which each vertex will be assigned to */
  for (i=0; i<nvtxs; i++)
    qnum[i] = samax(ncon, nvwgt+i*ncon);

  /* Insert the nodes of the proper partition in the appropriate priority queue */
  RandomPermute(nvtxs, perm, 1);
  for (ii=0; ii<nvtxs; ii++) {
    i = perm[ii];
    if (where[i] == from) {
      if (ed[i] > 0)
        PQueueInsert(&parts[qnum[i]][0], i, ed[i]-id[i]);
      else
        PQueueInsert(&parts[qnum[i]][1], i, ed[i]-id[i]);
    }
  }


  mincut = graph->mincut;
  nbnd = graph->nbnd;
  for (nswaps=0; nswaps<nvtxs; nswaps++) {
    if (AreAnyVwgtsBelow(ncon, 1.0, npwgts+from*ncon, 0.0, nvwgt, tpwgts[from]))
      break;

    if ((cnum = SelectQueueOneWay(ncon, npwgts, tpwgts, from, parts)) == -1)
      break;

    if ((higain = PQueueGetMax(&parts[cnum][0])) == -1)
      higain = PQueueGetMax(&parts[cnum][1]);

    mincut -= (ed[higain]-id[higain]);
    saxpy(ncon, 1.0, nvwgt+higain*ncon, 1, npwgts+to*ncon, 1);
    saxpy(ncon, -1.0, nvwgt+higain*ncon, 1, npwgts+from*ncon, 1);

    where[higain] = to;

    if (ctrl->dbglvl&DBG_MOVEINFO) {
      printf("Moved %6d from %d(%d). [%5d] %5d, NPwgts: ", higain, from, cnum, ed[higain]-id[higain], mincut);
      for (l=0; l<ncon; l++) 
        printf("(%.3f, %.3f) ", npwgts[l], npwgts[ncon+l]);
      printf(", LB: %.3f\n", Compute2WayHLoadImbalance(ncon, npwgts, tpwgts));
      if (ed[higain] == 0 && id[higain] > 0)
        printf("\t Pulled from the interior!\n");
    }


    /**************************************************************
    * Update the id[i]/ed[i] values of the affected nodes
    ***************************************************************/
    SWAP(id[higain], ed[higain], tmp);
    if (ed[higain] == 0 && bndptr[higain] != -1 && xadj[higain] < xadj[higain+1]) 
      BNDDelete(nbnd, bndind,  bndptr, higain);
    if (ed[higain] > 0 && bndptr[higain] == -1)
      BNDInsert(nbnd, bndind,  bndptr, higain);

    for (j=xadj[higain]; j<xadj[higain+1]; j++) {
      k = adjncy[j];
      oldgain = ed[k]-id[k];

      kwgt = (to == where[k] ? adjwgt[j] : -adjwgt[j]);
      INC_DEC(id[k], ed[k], kwgt);

      /* Update the queue position */
      if (where[k] == from) {
        if (ed[k] > 0 && bndptr[k] == -1) {  /* It moves in boundary */
          PQueueDelete(&parts[qnum[k]][1], k, oldgain);
          PQueueInsert(&parts[qnum[k]][0], k, ed[k]-id[k]);
        }
        else { /* It must be in the boundary already */
          if (bndptr[k] == -1)
            printf("What you thought was wrong!\n");
          PQueueUpdate(&parts[qnum[k]][0], k, oldgain, ed[k]-id[k]);
        }
      }

      /* Update its boundary information */
      if (ed[k] == 0 && bndptr[k] != -1) 
        BNDDelete(nbnd, bndind, bndptr, k);
      else if (ed[k] > 0 && bndptr[k] == -1)  
        BNDInsert(nbnd, bndind, bndptr, k);
    }

    ASSERTP(ComputeCut(graph, where) == mincut, ("%d != %d\n", ComputeCut(graph, where), mincut));

  }

  if (ctrl->dbglvl&DBG_REFINE) {
    printf("\tMincut: %6d, NBND: %6d, NPwgts: ", mincut, nbnd);
    for (l=0; l<ncon; l++)
      printf("(%.3f, %.3f) ", npwgts[l], npwgts[ncon+l]);
    printf(", LB: %.3f\n", Compute2WayHLoadImbalance(ncon, npwgts, tpwgts));
  }

  graph->mincut = mincut;
  graph->nbnd = nbnd;

  for (i=0; i<ncon; i++) {
    PQueueFree(ctrl, &parts[i][0]);
    PQueueFree(ctrl, &parts[i][1]);
  }

  ASSERT(ComputeCut(graph, where) == graph->mincut);
  ASSERT(CheckBnd(graph));

  idxwspacefree(ctrl, nvtxs);
  idxwspacefree(ctrl, nvtxs);
}