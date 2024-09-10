void
vmeshStoreUpdt (
Vmesh * const               meshptr,
const VmeshStore * const    storptr)
{
  byte *              frontab;                    /* Pointer to frontier data save area */
  byte *              parttab;                    /* Pointer to part data save area     */

  meshptr->ecmpsize[0] = storptr->ecmpsize[0];    /* Load partition parameters */
  meshptr->ecmpsize[1] = storptr->ecmpsize[1];
  meshptr->ncmpload[0] = storptr->ncmpload[0];
  meshptr->ncmpload[1] = storptr->ncmpload[1];
  meshptr->ncmpload[2] = storptr->ncmpload[2];
  meshptr->ncmploaddlt = storptr->ncmploaddlt;
  meshptr->ncmpsize[0] = storptr->ncmpsize[0];
  meshptr->ncmpsize[1] = storptr->ncmpsize[1];
  meshptr->fronnbr     = storptr->fronnbr;

  frontab = storptr->datatab;                     /* Compute data offsets within save structure */
  parttab = frontab + storptr->fronnbr * sizeof (Gnum);

  memCpy (meshptr->frontab, frontab, storptr->fronnbr * sizeof (Gnum));
  memCpy (meshptr->parttax + meshptr->m.baseval, parttab, (meshptr->m.velmnbr + meshptr->m.vnodnbr) * sizeof (GraphPart));
}