static
int
graphMapCompute2 (
SCOTCH_Graph * const        grafptr,              /*+ Graph to order                  +*/
SCOTCH_Mapping * const      mappptr,              /*+ Mapping to compute              +*/
SCOTCH_Mapping * const      mapoptr,              /*+ Old mapping                     +*/
const double                emraval,              /*+ Edge migration ratio            +*/ 
const SCOTCH_Num *          vmlotab,              /*+ Vertex migration cost array     +*/
Gnum                        vfixval,              /*+ Equal to 0 if no fixed vertices +*/
SCOTCH_Strat * const        straptr)              /*+ Mapping strategy                +*/
{
  Kgraph                mapgrafdat;               /* Effective mapping graph              */
  const Strat *         mapstraptr;               /* Pointer to mapping strategy          */
  LibMapping * restrict lmapptr;
  LibMapping * restrict lmaoptr;
  Anum *                pfixtax;
  Gnum                  baseval;
  Anum *                parttax;                  /* Partition array                      */
  Anum *                parotax;                  /* Old partition array                  */
  Gnum                  crloval;                  /* Coefficient load for regular edges   */
  Gnum                  cmloval;                  /* Coefficient load for migration edges */
  const Gnum *          vmlotax;                  /* Vertex migration cost array          */
  Gnum                  vertnum;
  Gnum                  vertnnd;
  Gnum                  vertnbr;
  int                   o;

  lmapptr = (LibMapping *) mappptr;
#ifdef SCOTCH_DEBUG_GRAPH2
  if ((Graph *) grafptr != lmapptr->grafptr) {
    errorPrint ("graphMapCompute2: output mapping does not correspond to input graph");
    return     (1);
  }
  if (graphCheck ((Graph *) grafptr) != 0) {      /* Vertex loads can be 0 if we have fixed vertices */
    errorPrint ("graphMapCompute2: invalid input graph");
    return     (1);
  }
#endif /* SCOTCH_DEBUG_GRAPH2 */

  if (*((Strat **) straptr) == NULL) {            /* Set default mapping strategy if necessary */
    ArchDom             archdomnorg;

    archDomFrst (lmapptr->archptr, &archdomnorg);
    SCOTCH_stratGraphMapBuild (straptr, SCOTCH_STRATDEFAULT, archDomSize (lmapptr->archptr, &archdomnorg), 0.01);
  }

  mapstraptr = *((Strat **) straptr);
  if (mapstraptr->tabl != &kgraphmapststratab) {
    errorPrint ("graphMapCompute2: not a graph mapping strategy");
    return     (1);
  }

  baseval = lmapptr->grafptr->baseval;
  vertnbr = lmapptr->grafptr->vertnbr;
  if (mapoptr != NULL) {                          /* We are doing a repartitioning */
    LibMapping *        lmaoptr;
    Gnum                numeval;
    Gnum                denoval;

    lmaoptr = (LibMapping *) mapoptr;
#ifdef SCOTCH_DEBUG_GRAPH2
    if (lmapptr->grafptr != lmaoptr->grafptr) {
      errorPrint ("graphMapCompute2: output and old mapping must correspond to the same graph");
      return     (1);
    }
    if (lmapptr->archptr != lmaoptr->archptr) {
      errorPrint ("graphMapCompute2: output and old mapping must correspond to the same architecture");
      return     (1);
    }
#endif /* SCOTCH_DEBUG_GRAPH2 */

    parotax = lmaoptr->parttab - baseval;
    vmlotax = (vmlotab != NULL) ? vmlotab - baseval : NULL;
    numeval = (INT) ((emraval * 100.0) + 0.5);
    denoval = intGcd (numeval, 100);
    cmloval = numeval / denoval;
    crloval = 100     / denoval;
  }
  else {
    parotax = NULL;
    vmlotax = NULL;
    cmloval =
    crloval = 1;
  }

  parttax = NULL;
  if (vfixval != 0) {                             /* We have fixed vertices */
#ifdef SCOTCH_DEBUG_GRAPH2
    if (lmapptr->parttab == NULL) {               /* We must have fixed vertices information */
      errorPrint ("graphMapCompute2: missing output mapping part array");
      return     (1);
    }
#endif /* SCOTCH_DEBUG_GRAPH2 */
    pfixtax = lmapptr->parttab - baseval;
    if ((parttax = (Anum *) memAlloc (vertnbr * sizeof (Anum))) == NULL) {
      errorPrint ("graphMapCompute2: out of memory (1)");
      return     (1);
    }
    memSet (parttax, 0, vertnbr * sizeof (Anum)); /* All vertices mapped to first domain */
    parttax -= baseval;
  } else {
    pfixtax = NULL;
    if (lmapptr->parttab == NULL) {               /* If user mapping not initialized */
      errorPrint ("graphMapCompute2: invalid user mapping");
      return     (1);
    }
    parttax = lmapptr->parttab - baseval;
  }

  intRandInit ();                                 /* Check that random number generator is initialized */

  if (kgraphInit (&mapgrafdat, (Graph *) grafptr, lmapptr->archptr, NULL, parttax, parotax, crloval, cmloval, vmlotax, pfixtax) != 0)
    return (1);

  o = 0;
  if (mapgrafdat.vfixnbr != mapgrafdat.s.vertnbr) { /* Perform mapping if not all fixed vertices */
    o = kgraphMapSt (&mapgrafdat, mapstraptr);

    lmapptr->parttab -= baseval;
    for (vertnum = baseval, vertnnd = vertnum + lmapptr->grafptr->vertnbr;
        vertnum < vertnnd; vertnum ++)
      lmapptr->parttab[vertnum] = archDomNum (lmapptr->archptr, &mapgrafdat.m.domntab[mapgrafdat.m.parttax[vertnum]]);
    lmapptr->parttab += baseval;
  }

  if (vfixval != 0)                               /* We have fixed vertices */
    memFree (parttax + baseval);

  kgraphExit (&mapgrafdat);

  return (o);
}