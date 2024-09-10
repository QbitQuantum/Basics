static void
permute_one (void *arg, transition_info_t *ti, state_data_t dst, int *cpy)
{

    (void) cpy;

    permute_t          *perm = (permute_t*) arg;
    int                 seen;
    seen = state_info_new_state (perm->next, dst, ti, perm->state);
    if (EXPECT_FALSE(seen < 0)) {
        global->exit_status = LTSMIN_EXIT_FAILURE;
        if (run_stop(perm->run_ctx)) {
            Warning (info, "Error: %s full! Change -s/--ratio.",
                           state_store_full_msg(seen));
        }
        return;
    }
    switch (perm->permutation) {
    case Perm_Shift:
        if (ti->group < perm->start_group) {
            perm_todo (perm, ti, seen);
            break;
        } else // fall through
    case Perm_None:
        perm->real_cb (perm->call_ctx, perm->next, ti, seen);
        ti->por_proviso &= perm->por_proviso;
        break;
    case Perm_Shift_All:
        if (0 == perm->start_group_index && ti->group >= perm->start_group)
            perm->start_group_index = perm->nstored;
        // fall through
    case Perm_Dynamic:
    case Perm_Random:
    case Perm_SR:
    case Perm_RR:
    case Perm_Otf:
    case Perm_Sort:
        perm_todo (perm, ti, seen);
        break;
    default:
        Abort ("Unknown permutation!");
    }
}