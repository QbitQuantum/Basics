void
kgraphStoreUpdt (
Kgraph * const              grafptr,
const KgraphStore * const   storptr)
{
  grafptr->commload  = storptr->mflaval;
  grafptr->m.domnnbr = storptr->domnnbr;
  grafptr->fronnbr   = storptr->fronnbr;
  grafptr->kbalval   = storptr->kbalval;
  grafptr->commload  = storptr->commload;

  memCpy (grafptr->m.parttax + grafptr->s.baseval, storptr->parttab,     grafptr->s.vertnbr * sizeof (Anum));
  memCpy (grafptr->m.domntab,                      storptr->domntab,     grafptr->m.domnnbr * sizeof (ArchDom));
  memCpy (grafptr->frontab,                        storptr->frontab,     storptr->fronnbr * sizeof (Gnum));
  memCpy (grafptr->comploadavg,                    storptr->comploadavg, storptr->partnbr * sizeof (Gnum));
  memCpy (grafptr->comploaddlt,                    storptr->comploaddlt, storptr->partnbr * sizeof (Gnum));

#ifdef SCOTCH_DEBUG_KGRAPH2
  if (kgraphCheck (grafptr) != 0)
    errorPrint ("kgraphStoreUpdt: inconsistent graph data");
#endif /* SCOTCH_DEBUG_KGRAPH2 */
}