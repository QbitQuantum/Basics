void
METISNAMEU(METIS_PartGraphVKway) (
const int * const           n,
const int * const           xadj,
const int * const           adjncy,
const int * const           vwgt,
const int * const           vsize,
const int * const           wgtflag,
const int * const           numflag,
const int * const           nparts,
const int * const           options,
int * const                 volume,
int * const                 part)
{
  int                   baseval;
  const int *           vwgt2;
  const int *           vsize2;
  int                   vsizval;                  /* Communication volume of current vertex */
  int                   vertnbr;
  int                   vertnum;
  int                   edgenum;
  const int * restrict  edgetax;
  const int * restrict  parttax;
  int * restrict        nghbtab;
  int                   commvol;

  vsize2  = ((*wgtflag & 1) != 0) ? vsize : NULL;
  vwgt2   = ((*wgtflag & 2) != 0) ? vwgt  : NULL;
  baseval = *numflag;
  vertnbr = *n;
  edgetax = adjncy - baseval;

  if (vsize2 == NULL)                             /* If no communication load data provided */
    _SCOTCH_METIS_PartGraph (n, xadj, adjncy, vwgt2, NULL, numflag, nparts, part);
  else {                                          /* Will have to turn communication volumes into edge loads */
    const int * restrict  vsiztax;
    int                   edgenbr;
    int * restrict        edlotax;
    int                   o;

    edgenbr = xadj[vertnbr] - baseval;
    if ((edlotax = memAlloc (edgenbr * sizeof (int))) == NULL)
      return;
    edlotax -= baseval;                           /* Base access to edlotax */
    vsiztax  = vsize2 - baseval;

    for (vertnum = 0, edgenum = baseval;          /* Un-based scan of vertex array xadj */
         vertnum < vertnbr; vertnum ++) {
      int                 vsizval;                /* Communication size of current vertex */
      int                 edgennd;

      vsizval = vsize2[vertnum];
      for (edgennd = xadj[vertnum + 1]; edgenum < edgennd; edgenum ++) { /* Based traversal of edge array adjncy */
        int                 vertend;              /* Based end vertex number                                     */

        vertend = edgetax[edgenum];
        edlotax[edgenum] = vsizval + vsiztax[vertend];
      }
    }

    o = _SCOTCH_METIS_PartGraph (n, xadj, adjncy, vwgt2, edlotax + baseval, numflag, nparts, part);

    memFree (edlotax + baseval);

    if (o != 0)
      return;
  }

  if ((nghbtab = memAlloc (*nparts * sizeof (int))) == NULL)
    return;
  memSet (nghbtab, ~0, *nparts * sizeof (int));

  parttax = part - baseval;
  vsizval = 1;                                      /* Assume no vertex communication sizes */
  for (vertnum = 0, edgenum = baseval, commvol = 0; /* Un-based scan of vertex array xadj   */
       vertnum < vertnbr; vertnum ++) {
    int                 partval;
    int                 edgennd;

    partval = part[vertnum];
    nghbtab[partval] = vertnum;                   /* Do not count local neighbors in communication volume */
    if (vsize2 != NULL)
      vsizval = vsize2[vertnum];

    for (edgennd = xadj[vertnum + 1]; edgenum < edgennd; edgenum ++) { /* Based traversal of edge array adjncy */
      int                 vertend;                /* Based end vertex number                                   */
      int                 partend;

      vertend = edgetax[edgenum];
      partend = parttax[vertend];
      if (nghbtab[partend] != vertnum) {          /* If first neighbor in this part */
        nghbtab[partend] = vertnum;               /* Set part as accounted for      */
        commvol += vsizval;
      }
    }
  }
  *volume = commvol;

  memFree (nghbtab);
}