/* add to list */
static void listadd(SCANSYN_GLOBALS *pp, PSCSNUX *p)
{
    CSOUND  *csound = pp->csound;
    struct scsnx_elem *i = (struct scsnx_elem *) pp->scsnx_list;

    for ( ; i != NULL; i = i->next) {
      if (i->id == p->id) {
        i->p = p;
        return;
      }
    }
    i = (struct scsnx_elem *) csound->Malloc(csound, sizeof(struct scsnx_elem));
    i->id = p->id;
    i->p = p;
    i->next = (struct scsnx_elem *) pp->scsnx_list;
    pp->scsnx_list = (void*) i;
}