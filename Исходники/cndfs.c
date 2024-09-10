void
rec_ndfs_call (wctx_t *ctx, ref_t state)
{
    cndfs_alg_local_t  *cloc = (cndfs_alg_local_t *) ctx->local;
    alg_global_t       *sm = ctx->global;
    strategy_t          rec_strat = get_strategy (ctx->run->shared->rec->alg);
    dfs_stack_push (sm->rec->local->stack, (int*)&state);
    cloc->counters.rec++;
    switch (rec_strat) {
    case Strat_ENDFS:
       endfs_blue (sm->rec->run, sm->rec); break;
    case Strat_LNDFS:
       lndfs_blue (sm->rec->run, sm->rec); break;
    case Strat_NDFS:
       ndfs_blue (sm->rec->run, sm->rec); break;
    default:
       Abort ("Invalid recursive strategy.");
    }
}