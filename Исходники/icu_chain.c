void icu_chain_destroy(struct icu_chain *chain)
{
    if (chain)
    {
        if (chain->coll)
            ucol_close(chain->coll);

        if (chain->iter)
            icu_iter_destroy(chain->iter);
        icu_chain_step_destroy(chain->csteps);
        xfree(chain->locale);
        xfree(chain);
    }
}