int
SCOTCH_graphMapView (
const SCOTCH_Graph * const    libgrafptr,
const SCOTCH_Mapping * const  libmappptr,
FILE * const                  stream)
{
  const Graph * restrict    grafptr;
  const Mapping * restrict  mappptr;
  Anum * restrict           parttax;              /* Part array                                   */
  MappingSort * restrict    domntab;              /* Pointer to domain sort array                 */
  ArchDom                   domnfrst;             /* Largest domain in architecture               */
  Anum                      tgtnbr;               /* Number of processors in target topology      */
  Anum                      mapnbr;               /* Number of processors effectively used        */
  Anum                      mapnum;
  double                    mapavg;               /* Average mapping weight                       */
  Gnum                      mapmin;
  Gnum                      mapmax;
  Gnum                      mapsum;               /* (Partial) sum of vertex loads                */
  double                    mapdlt;
  double                    mapmmy;               /* Maximum / average ratio                      */
  Anum * restrict           nghbtab;              /* Table storing neighbors of current subdomain */
  Anum                      nghbnbr;
  Anum                      nghbmin;
  Anum                      nghbmax;
  Anum                      nghbsum;
  Gnum                      vertnum;
  Gnum                      veloval;
  Gnum                      edloval;
  Gnum                      commdist[256];        /* Array of load distribution */
  Gnum                      commload;             /* Total edge load (edge sum) */
  Gnum                      commdilat;            /* Total edge dilation        */
  Gnum                      commexpan;            /* Total edge expansion       */
  Anum                      distmax;
  Anum                      distval;
  Gnum                      diammin;
  Gnum                      diammax;
  Gnum                      diamsum;

  const Gnum * restrict const verttax = ((Graph *) libgrafptr)->verttax;
  const Gnum * restrict const vendtax = ((Graph *) libgrafptr)->vendtax;
  const Gnum * restrict const velotax = ((Graph *) libgrafptr)->velotax;
  const Gnum * restrict const edgetax = ((Graph *) libgrafptr)->edgetax;
  const Gnum * restrict const edlotax = ((Graph *) libgrafptr)->edlotax;

  grafptr = (Graph *) libgrafptr;
  mappptr = &((LibMapping *) libmappptr)->m;

  if ((grafptr->vertnbr == 0) ||                  /* Return if nothing to do */
      (grafptr->edgenbr == 0))
    return (0);

  if (memAllocGroup ((void **) (void *)
                     &domntab, (size_t) ((grafptr->vertnbr + 1) * sizeof (MappingSort)),
                     &parttax, (size_t) (grafptr->vertnbr       * sizeof (Anum)),
                     &nghbtab, (size_t) ((grafptr->vertnbr + 2) * sizeof (Anum)), NULL) == NULL) {
    errorPrint ("SCOTCH_graphMapView: out of memory");
    return     (1);
  }

  memSet (parttax, ~0, grafptr->vertnbr * sizeof (Anum));

  for (vertnum = 0; vertnum < grafptr->vertnbr; vertnum ++) {
    parttax[vertnum]      =
    domntab[vertnum].labl = archDomNum (&mappptr->archdat, mapDomain (mappptr, vertnum + grafptr->baseval));
    domntab[vertnum].peri = vertnum + grafptr->baseval; /* Build inverse permutation */
  }
  domntab[grafptr->vertnbr].labl = ARCHDOMNOTTERM; /* TRICK: avoid testing (i+1)   */
  domntab[grafptr->vertnbr].peri = ~0;            /* Prevent Valgrind from yelling */
  parttax -= grafptr->baseval;                    /* From now on, base part array  */

  intSort2asc2 (domntab, grafptr->vertnbr);       /* Sort domain label array by increasing target labels */

  archDomFrst (&mappptr->archdat, &domnfrst);     /* Get architecture domain    */
  tgtnbr = archDomSize (&mappptr->archdat, &domnfrst); /* Get architecture size */

  mapsum  = 0;
  mapnbr  = 0;
  veloval = 1;                                    /* Assume unweighted vertices */
  for (vertnum = 0; domntab[vertnum].labl != ARCHDOMNOTTERM; vertnum ++) {
    parttax[domntab[vertnum].peri] = mapnbr;      /* Build map of partition parts starting from 0  */
    if (domntab[vertnum].labl != domntab[vertnum + 1].labl) /* TRICK: if new (or end) domain label */
      mapnbr ++;
    if (velotax != NULL)
      veloval = velotax[domntab[vertnum].peri];
    mapsum += veloval;
  }
  mapavg = (mapnbr == 0) ? 0.0L : (double) mapsum / (double) mapnbr;

  mapsum = 0;
  mapmin = GNUMMAX;
  mapmax = 0;
  mapdlt = 0.0L;
  for (vertnum = 0; domntab[vertnum].labl != ARCHDOMNOTTERM; vertnum ++) {
    if (velotax != NULL)
      veloval = velotax[domntab[vertnum].peri];
    mapsum += veloval;

    if (domntab[vertnum].labl != domntab[vertnum + 1].labl) { /* TRICK: if new (or end) domain label */
      if (mapsum < mapmin)
        mapmin = mapsum;
      if (mapsum > mapmax)
        mapmax = mapsum;
      mapdlt += fabs ((double) mapsum - mapavg);
      mapsum = 0;                                 /* Reset domain load sum */
    }
  }
  mapdlt = (mapnbr != 0) ? mapdlt / ((double) mapnbr * mapavg) : 0.0L;
  mapmmy = (mapnbr != 0) ? (double) mapmax / (double) mapavg : 0.0L;

  if (mapnbr > tgtnbr) {                          /* If more subdomains than architecture size */
#ifdef SCOTCH_DEBUG_MAP2
    if (! archVar (&mappptr->archdat)) {          /* If not a variable-sized architecture */
      errorPrint ("SCOTCH_graphMapView: invalid mapping");
      memFree    (domntab);                       /* Free group leader */
      return     (1);
    }
#endif /* SCOTCH_DEBUG_MAP2 */
    tgtnbr = mapnbr;                              /* Assume it is a variable-sized architecture */
  }

  fprintf (stream, "M\tProcessors " GNUMSTRING "/" GNUMSTRING " (%g)\n",
           (Gnum) mapnbr,
           (Gnum) tgtnbr,
           (double) mapnbr / (double) tgtnbr);
  fprintf (stream, "M\tTarget min=" GNUMSTRING "\tmax=" GNUMSTRING "\tavg=%g\tdlt=%g\tmaxavg=%g\n",
           (Gnum) mapmin,
           (Gnum) mapmax,
           mapavg,
           mapdlt,
           mapmmy);

  nghbnbr = 0;
  nghbmin = ANUMMAX;
  nghbmax = 0;
  nghbsum = 0;
  nghbnbr = 0;
  nghbtab[0] = -2;
  for (vertnum = 0; domntab[vertnum].labl != ARCHDOMNOTTERM; vertnum ++) {
    Gnum                edgenum;
    Gnum                edgennd;
    Anum                partnum;

    partnum = parttax[domntab[vertnum].peri];
    for (edgenum = verttax[domntab[vertnum].peri],
         edgennd = vendtax[domntab[vertnum].peri];
         edgenum < edgennd; edgenum ++) {
      Anum                partend;

      partend = parttax[edgetax[edgenum]];
      if ((partend != partnum) &&                 /* If edge is not internal                                      */
          (partend != nghbtab[nghbnbr])) {        /* And neighbor is not sole neighbor or has not just been found */
        Anum                partmin;
        Anum                partmax;

        partmin = 0;
        partmax = nghbnbr;
        while ((partmax - partmin) > 1) {
          Anum                partmed;

          partmed = (partmax + partmin) >> 1;
          if (nghbtab[partmed] > partend)
            partmax = partmed;
          else
            partmin = partmed;
        }
        if (nghbtab[partmin] == partend)          /* If neighboring part found, skip to next neighbor */
          continue;

#ifdef SCOTCH_DEBUG_MAP2
        if (nghbnbr >= (grafptr->vertnbr + 1)) {
          errorPrint ("SCOTCH_graphMapView: internal error");
          return (1);
        }
#endif /* SCOTCH_DEBUG_MAP2 */

        nghbnbr ++;
        for (partmax = nghbnbr; partmax > (partmin + 1); partmax --)
          nghbtab[partmax] = nghbtab[partmax - 1];
        nghbtab[partmin + 1] = partend;           /* Add new neighbor part in the right place */
      }
    }
    if (domntab[vertnum].labl != domntab[vertnum + 1].labl) { /* TRICK: if new (or end) domain label */
      if (nghbnbr < nghbmin)
        nghbmin = nghbnbr;
      if (nghbnbr > nghbmax)
        nghbmax = nghbnbr;
      nghbsum += nghbnbr;

      nghbnbr = 0;
    }
  }