/*! \brief
 * Determines a suitable grid size.
 *
 * \param[in,out] d    Grid information.
 * \param[in]     pbc  Information about the box.
 * \returns  FALSE if grid search is not suitable.
 */
static gmx_bool
grid_setup_cells(gmx_ana_nbsearch_t *d, t_pbc *pbc)
{
    real targetsize;
    int  dd;

#ifdef HAVE_CBRT
    targetsize = cbrt(pbc->box[XX][XX] * pbc->box[YY][YY] * pbc->box[ZZ][ZZ]
                      * 10 / d->nref);
#else
    targetsize = pow(pbc->box[XX][XX] * pbc->box[YY][YY] * pbc->box[ZZ][ZZ]
                     * 10 / d->nref, 1./3.);
#endif

    d->ncells = 1;
    for (dd = 0; dd < DIM; ++dd)
    {
        d->ncelldim[dd] = (int)(pbc->box[dd][dd] / targetsize);
        d->ncells      *= d->ncelldim[dd];
        if (d->ncelldim[dd] < 3)
        {
            return FALSE;
        }
    }
    /* Reallocate if necessary */
    if (d->cells_nalloc < d->ncells)
    {
        int  i;

        srenew(d->ncatoms, d->ncells);
        srenew(d->catom, d->ncells);
        srenew(d->catom_nalloc, d->ncells);
        for (i = d->cells_nalloc; i < d->ncells; ++i)
        {
            d->catom[i]        = NULL;
            d->catom_nalloc[i] = 0;
        }
        d->cells_nalloc = d->ncells;
    }
    return TRUE;
}