void
METISNAMEU(ParMETIS_V3_NodeND) (
const int * const           vtxdist,
int * const                 xadj,
int * const                 adjncy,
const int * const           numflag,
const int * const           options,              /* Not used */
int * const                 order,
int * const                 sizes,                /* Of size twice the number of processors ; not used */
MPI_Comm *                  comm)
{
  MPI_Comm            proccomm;
  int                 procglbnbr;
  int                 proclocnum;
  SCOTCH_Num          baseval;
  SCOTCH_Dgraph       grafdat;                    /* Scotch distributed graph object to interface with libScotch    */
  SCOTCH_Dordering    ordedat;                    /* Scotch distributed ordering object to interface with libScotch */
  SCOTCH_Strat        stradat;
  SCOTCH_Num          vertlocnbr;
  SCOTCH_Num          edgelocnbr;

  if (sizeof (SCOTCH_Num) != sizeof (int)) {
    SCOTCH_errorPrint ("ParMETIS_V3_NodeND (as of SCOTCH): SCOTCH_Num type should equate to int");
    return;
  }

  proccomm = *comm;
  if (SCOTCH_dgraphInit (&grafdat, proccomm) != 0)
    return;

  MPI_Comm_size (proccomm, &procglbnbr);
  MPI_Comm_rank (proccomm, &proclocnum);
  baseval    = *numflag;
  vertlocnbr = vtxdist[proclocnum + 1] - vtxdist[proclocnum];
  edgelocnbr = xadj[vertlocnbr] - baseval;

  if (sizes != NULL)
    memSet (sizes, ~0, (2 * procglbnbr - 1) * sizeof (int)); /* Array not used if procglbnbr is not a power of 2 or if error */

  if (SCOTCH_dgraphBuild (&grafdat, baseval,
                          vertlocnbr, vertlocnbr, xadj, xadj + 1, NULL, NULL,
                          edgelocnbr, edgelocnbr, adjncy, NULL, NULL) == 0) {
    SCOTCH_stratInit (&stradat);
#ifdef SCOTCH_DEBUG_ALL
    if (SCOTCH_dgraphCheck (&grafdat) == 0)       /* TRICK: next instruction called only if graph is consistent */
#endif /* SCOTCH_DEBUG_ALL */
    {
      if (SCOTCH_dgraphOrderInit (&grafdat, &ordedat) == 0) {
        int                 levlmax;
        int                 bitsnbr;
        SCOTCH_Num          proctmp;

        SCOTCH_dgraphOrderCompute (&grafdat, &ordedat, &stradat);
        SCOTCH_dgraphOrderPerm    (&grafdat, &ordedat, order);

        for (levlmax = -1, bitsnbr = 0, proctmp = procglbnbr; /* Count number of bits set to 1 in procglbnbr */
             proctmp != 0; levlmax ++, proctmp >>= 1)
          bitsnbr += proctmp & 1;

        if (bitsnbr == 1) {
          SCOTCH_Num          cblkglbnbr;

          if ((cblkglbnbr = SCOTCH_dgraphOrderCblkDist (&grafdat, &ordedat)) >= 0) {
            SCOTCH_Num *        treeglbtab;
            SCOTCH_Num *        sizeglbtab;
            SCOTCH_Num *        sepaglbtab;

            if (memAllocGroup ((void **) (void *)
                               &treeglbtab, (size_t) (cblkglbnbr * sizeof (SCOTCH_Num)),
                               &sizeglbtab, (size_t) (cblkglbnbr * sizeof (SCOTCH_Num)),
                               &sepaglbtab, (size_t) (cblkglbnbr * sizeof (SCOTCH_Num) * 3), NULL) != NULL) {
              if (SCOTCH_dgraphOrderTreeDist (&grafdat, &ordedat, treeglbtab, sizeglbtab) == 0) {
                SCOTCH_Num          rootnum;
                SCOTCH_Num          cblknum;

                memSet (sepaglbtab, ~0, cblkglbnbr * sizeof (SCOTCH_Num) * 3);
                
                for (rootnum = -1, cblknum = 0; cblknum < cblkglbnbr; cblknum ++) {
                  SCOTCH_Num          fathnum;

                  fathnum = treeglbtab[cblknum] - baseval; /* Use un-based indices  */
                  if (fathnum < 0) {              /* If father index indicates root */
                    if (rootnum != -1) {          /* If another root already found  */
                      rootnum = -1;               /* Indicate an error              */
                      break;
                    }
                    rootnum = cblknum;            /* Record index of root node */
                  }
                  else {
                    int                 i;

                    for (i = 0; i < 3; i ++) {
                      int                 j;

                      j = 3 * fathnum + i;        /* Slot number of prospective son  */
                      if (sepaglbtab[j] < 0) {    /* If potentially empty slot found */
                        if (sepaglbtab[j] == -1)  /* If we don't have too many sons  */
                          sepaglbtab[j] = cblknum; /* Add link to son in slot        */
                        break;
                      }
                    }
                    if (i == 3) {                 /* If no empty slot found             */
                      sepaglbtab[3 * fathnum] = -2; /* Indicate there are too many sons */
                      break;
                    }
                  }
                }

                if ((rootnum >= 0) && (sizes != NULL)) { /* If no error above, go on processing separator tree  */
                  memSet (sizes, 0, (2 * procglbnbr - 1) * sizeof (int)); /* Set array of sizes to 0 by default */
                  _SCOTCH_ParMETIS_V3_NodeNDTree (sizes + (2 * procglbnbr - 1), sizeglbtab, sepaglbtab, levlmax, 0, rootnum, 1);
                }
              }

              memFree (treeglbtab);               /* Free group leader */
            }
          }
        }

        SCOTCH_dgraphOrderExit (&grafdat, &ordedat);
      }
    }