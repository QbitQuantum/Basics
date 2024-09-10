/*************************************************************************
* This function moves a collection of vertices and updates their rinfo
**************************************************************************/
void MoveGroupMConn(CtrlType *ctrl, GraphType *graph, idxtype *ndoms, idxtype *pmat,
                    int nparts, int to, int nind, idxtype *ind)
{
  int i, ii, iii, j, jj, k, l, nvtxs, nbnd, myndegrees; 
  int from, me;
  idxtype *xadj, *adjncy, *adjwgt;
  idxtype *where, *bndptr, *bndind;
  EDegreeType *myedegrees;
  RInfoType *myrinfo;

  nvtxs = graph->nvtxs;
  xadj = graph->xadj;
  adjncy = graph->adjncy;
  adjwgt = graph->adjwgt;

  where = graph->where;
  bndptr = graph->bndptr;
  bndind = graph->bndind;

  nbnd = graph->nbnd;

  for (iii=0; iii<nind; iii++) {
    i = ind[iii];
    from = where[i];

    myrinfo = graph->rinfo+i;
    if (myrinfo->edegrees == NULL) {
      myrinfo->edegrees = ctrl->wspace.edegrees+ctrl->wspace.cdegree;
      ctrl->wspace.cdegree += xadj[i+1]-xadj[i];
      myrinfo->ndegrees = 0;
    }
    myedegrees = myrinfo->edegrees;

    /* find the location of 'to' in myrinfo or create it if it is not there */
    for (k=0; k<myrinfo->ndegrees; k++) {
      if (myedegrees[k].pid == to)
        break;
    }
    if (k == myrinfo->ndegrees) {
      myedegrees[k].pid = to;
      myedegrees[k].ed = 0;
      myrinfo->ndegrees++;
    }

    graph->mincut -= myedegrees[k].ed-myrinfo->id;

    /* Update pmat to reflect the move of 'i' */
    pmat[from*nparts+to] += (myrinfo->id-myedegrees[k].ed);
    pmat[to*nparts+from] += (myrinfo->id-myedegrees[k].ed);
    if (pmat[from*nparts+to] == 0) 
      ndoms[from]--;
    if (pmat[to*nparts+from] == 0) 
      ndoms[to]--;

    /* Update where, weight, and ID/ED information of the vertex you moved */
    where[i] = to;
    myrinfo->ed += myrinfo->id-myedegrees[k].ed;
    SWAP(myrinfo->id, myedegrees[k].ed, j);
    if (myedegrees[k].ed == 0) 
      myedegrees[k] = myedegrees[--myrinfo->ndegrees];
    else
      myedegrees[k].pid = from;

    if (myrinfo->ed-myrinfo->id < 0 && bndptr[i] != -1)
      BNDDelete(nbnd, bndind, bndptr, i);

    /* Update the degrees of adjacent vertices */
    for (j=xadj[i]; j<xadj[i+1]; j++) {
      ii = adjncy[j];
      me = where[ii];

      myrinfo = graph->rinfo+ii;
      if (myrinfo->edegrees == NULL) {
        myrinfo->edegrees = ctrl->wspace.edegrees+ctrl->wspace.cdegree;
        ctrl->wspace.cdegree += xadj[ii+1]-xadj[ii];
      }
      myedegrees = myrinfo->edegrees;

      ASSERT(CheckRInfo(myrinfo));

      if (me == from) {
        INC_DEC(myrinfo->ed, myrinfo->id, adjwgt[j]);

        if (myrinfo->ed-myrinfo->id >= 0 && bndptr[ii] == -1)
          BNDInsert(nbnd, bndind, bndptr, ii);
      }
      else if (me == to) {
        INC_DEC(myrinfo->id, myrinfo->ed, adjwgt[j]);

        if (myrinfo->ed-myrinfo->id < 0 && bndptr[ii] != -1)
          BNDDelete(nbnd, bndind, bndptr, ii);
      }

      /* Remove contribution from the .ed of 'from' */
      if (me != from) {
        for (k=0; k<myrinfo->ndegrees; k++) {
          if (myedegrees[k].pid == from) {
            if (myedegrees[k].ed == adjwgt[j])
              myedegrees[k] = myedegrees[--myrinfo->ndegrees];
            else
              myedegrees[k].ed -= adjwgt[j];
            break;
          }
        }
      }

      /* Add contribution to the .ed of 'to' */
      if (me != to) {
        for (k=0; k<myrinfo->ndegrees; k++) {
          if (myedegrees[k].pid == to) {
            myedegrees[k].ed += adjwgt[j];
            break;
          }
        }
        if (k == myrinfo->ndegrees) {
          myedegrees[myrinfo->ndegrees].pid = to;
          myedegrees[myrinfo->ndegrees++].ed = adjwgt[j];
        }
      }

      /* Update pmat to reflect the move of 'i' for domains other than 'from' and 'to' */
      if (me != from && me != to) {
        pmat[me*nparts+from] -= adjwgt[j];
        pmat[from*nparts+me] -= adjwgt[j];
        if (pmat[me*nparts+from] == 0) 
          ndoms[me]--;
        if (pmat[from*nparts+me] == 0) 
          ndoms[from]--;

        if (pmat[me*nparts+to] == 0) 
          ndoms[me]++;
        if (pmat[to*nparts+me] == 0) 
          ndoms[to]++;

        pmat[me*nparts+to] += adjwgt[j];
        pmat[to*nparts+me] += adjwgt[j];
      }

      ASSERT(CheckRInfo(myrinfo));
    }

    ASSERT(CheckRInfo(graph->rinfo+i));
  }

  graph->nbnd = nbnd;

}