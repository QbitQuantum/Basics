op_generic_t *rs_simple_request(resource_service_fn_t *arg, data_attr_t *da, rs_query_t *rsq, data_cap_set_t **caps, rs_request_t *req, int req_size, rs_hints_t *hints_list, int fixed_size, int n_rid, int ignore_fixed_err, int timeout)
{
    rs_simple_priv_t *rss = (rs_simple_priv_t *)arg->priv;
    rsq_base_t *query_global = (rsq_base_t *)rsq;
    rsq_base_t *query_local;
    kvq_table_t kvq_global, kvq_local, *kvq;
    apr_hash_t *pick_from;
    rid_change_entry_t *rid_change;
    ex_off_t change;
    op_status_t status;
    opque_t *que;
    rss_rid_entry_t *rse;
    rsq_base_ele_t *q;
    int slot, rnd_off, i, j, k, i_unique, i_pickone, found, err_cnt, loop, loop_end;
    int state, *a, *b, *op_state, unique_size;
    tbx_stack_t *stack;

    log_printf(15, "rs_simple_request: START rss->n_rids=%d n_rid=%d req_size=%d fixed_size=%d\n", rss->n_rids, n_rid, req_size, fixed_size);

    for (i=0; i<req_size; i++) req[i].rid_key = NULL;  //** Clear the result in case of an error

    apr_thread_mutex_lock(rss->lock);
    i = _rs_simple_refresh(arg);  //** Check if we need to refresh the data
    if (i != 0) {
        apr_thread_mutex_unlock(rss->lock);
        return(gop_dummy(op_failure_status));
    }

    //** Determine the query sizes and make the processing arrays
    memset(&kvq, 0, sizeof(kvq));
    rs_query_count(arg, rsq, &i, &(kvq_global.n_unique), &(kvq_global.n_pickone));

    log_printf(15, "rs_simple_request: n_unique=%d n_pickone=%d\n", kvq_global.n_unique, kvq_global.n_pickone);
    tbx_log_flush();

    //** Make space the for the uniq and pickone fields.
    //** Make sure we have space for at least 1 more than we need of each to pass to the routines even though they aren't used
    j = (kvq_global.n_pickone == 0) ? 1 : kvq_global.n_pickone + 1;
    tbx_type_malloc_clear(kvq_global.pickone, kvq_ele_t, j);

    unique_size = kvq_global.n_unique + 1;
    tbx_type_malloc_clear(kvq_global.unique, kvq_ele_t *, unique_size);
    log_printf(15, "MALLOC j=%d\n", unique_size);
    for (i=0; i<unique_size; i++) {
        tbx_type_malloc_clear(kvq_global.unique[i], kvq_ele_t, n_rid);
    }

    //** We don't allow these on the local but make a temp space anyway
    kvq_local.n_pickone = 0;
    tbx_type_malloc_clear(kvq_local.pickone, kvq_ele_t, 1);
    kvq_global.n_unique = 0;
    tbx_type_malloc_clear(kvq_local.unique, kvq_ele_t *, 1);
    tbx_type_malloc_clear(kvq_local.unique[0], kvq_ele_t, n_rid);

    status = op_success_status;

    que = new_opque();
    stack = tbx_stack_new();

    err_cnt = 0;
    found = 0;
//  max_size = (req_size > fixed_size) ? req_size : fixed_size;

    for (i=0; i < n_rid; i++) {
        found = 0;
        loop_end = 1;
        query_local = NULL;
        rnd_off = tbx_random_get_int64(0, rss->n_rids-1);
//rnd_off = 0;  //FIXME

        if (hints_list != NULL) {
            query_local = (rsq_base_t *)hints_list[i].local_rsq;
            if (query_local != NULL) {
                loop_end = 2;
                rs_query_count(arg, query_local, &j, &(kvq_local.n_unique), &(kvq_local.n_pickone));
                if ((kvq_local.n_unique != 0) && (kvq_local.n_pickone != 0)) {
                    log_printf(0, "Unsupported use of pickone/unique in local RSQ hints_list[%d]=%s!\n", i, hints_list[i].fixed_rid_key);
                    status.op_status = OP_STATE_FAILURE;
                    status.error_code = RS_ERROR_FIXED_NOT_FOUND;
                    hints_list[i].status = RS_ERROR_HINTS_INVALID_LOCAL;
                    err_cnt++;
                    continue;
                }
            }

            if (i<fixed_size) {  //** Use the fixed list for assignment
                rse = tbx_list_search(rss->rid_table, hints_list[i].fixed_rid_key);
                if (rse == NULL) {
                    log_printf(0, "Missing element in hints list[%d]=%s! Ignoring check.\n", i, hints_list[i].fixed_rid_key);
                    hints_list[i].status = RS_ERROR_FIXED_NOT_FOUND;
                    continue;   //** Skip the check
                }
                rnd_off = rse->slot;
            }
        }

        //** See if we use a restrictive list.  Ususally used when rebalancing space
        pick_from = (hints_list != NULL) ? hints_list[i].pick_from : NULL;
        rid_change = NULL;
        change = 0;
        for (k=0; k<req_size; k++) {
            if (req[k].rid_index == i) {
                change += req[k].size;
            }
        }

        for (j=0; j<rss->n_rids; j++) {
            slot = (rnd_off+j) % rss->n_rids;
            rse = rss->random_array[slot];
            if (pick_from != NULL) {
                rid_change = apr_hash_get(pick_from, rse->rid_key, APR_HASH_KEY_STRING);
                log_printf(15, "PICK_FROM != NULL i=%d j=%d slot=%d rse->rid_key=%s rse->status=%d rid_change=%p\n", i, j, slot, rse->rid_key, rse->status, rid_change);

                if (rid_change == NULL) continue;  //** Not in our list so skip to the next
                ex_off_t delta = rid_change->delta - change;
                log_printf(15, "PICK_FROM != NULL i=%d j=%d slot=%d rse->rid_key=%s rse->status=%d rc->state=%d (" XOT ") > " XOT "????\n", i, j, slot, rse->rid_key, rse->status, rid_change->state, delta, rid_change->tolerance);

                //** Make sure we don't overshoot the target
                if (rid_change->state == 1) continue;   //** Already converged RID
                if (rid_change->delta <= 0) continue;   //** Need to move data OFF this RID
                if ((change - rid_change->delta) > rid_change->tolerance) continue;  //**delta>0 if we made it here
            }

            log_printf(15, "i=%d j=%d slot=%d rse->rid_key=%s rse->status=%d\n", i, j, slot, rse->rid_key, rse->status);
            if ((rse->status != RS_STATUS_UP) && (i>=fixed_size)) continue;  //** Skip this if disabled and not in the fixed list

            tbx_stack_empty(stack, 1);
            q = query_global->head;
            kvq = &kvq_global;
            for (loop=0; loop<loop_end; loop++) {
                i_unique = 0;
                i_pickone = 0;
                while (q != NULL) {
                    state = -1;
                    switch (q->op) {
                    case RSQ_BASE_OP_KV:
                        state = rss_test(q, rse, i, kvq->unique[i_unique], &(kvq->pickone[i_pickone]));
                        log_printf(0, "KV: key=%s val=%s i_unique=%d i_pickone=%d loop=%d rss_test=%d rse->rid_key=%s\n", q->key, q->val, i_unique, i_pickone, loop, state, rse->rid_key);
                        tbx_log_flush();
                        if ((q->key_op & RSQ_BASE_KV_UNIQUE) || (q->val_op & RSQ_BASE_KV_UNIQUE)) i_unique++;
                        if ((q->key_op & RSQ_BASE_KV_PICKONE) || (q->val_op & RSQ_BASE_KV_PICKONE)) i_pickone++;
                        break;
                    case RSQ_BASE_OP_NOT:
                        a = (int *)tbx_stack_pop(stack);
                        state = (*a == 0) ? 1 : 0;
                        //log_printf(0, "NOT(%d)=%d\n", *a, state);
                        free(a);
                        break;
                    case RSQ_BASE_OP_AND:
                        a = (int *)tbx_stack_pop(stack);
                        b = (int *)tbx_stack_pop(stack);
                        state = (*a) && (*b);
                        //log_printf(0, "%d AND %d = %d\n", *a, *b, state);
                        free(a);
                        free(b);
                        break;
                    case RSQ_BASE_OP_OR:
                        a = (int *)tbx_stack_pop(stack);
                        b = (int *)tbx_stack_pop(stack);
                        state = a || b;
                        //log_printf(0, "%d OR %d = %d\n", *a, *b, state);
                        free(a);
                        free(b);
                        break;
                    }

                    tbx_type_malloc(op_state, int, 1);
                    *op_state = state;
                    tbx_stack_push(stack, (void *)op_state);
                    log_printf(15, " stack_size=%d loop=%d push state=%d\n",tbx_stack_count(stack), loop, state);
                    tbx_log_flush();
                    q = q->next;
                }

                if (query_local != NULL) {
                    q = query_local->head;
                    kvq = &kvq_local;
                }
            }

            op_state = (int *)tbx_stack_pop(stack);
            state = -1;
            if (op_state != NULL) {
                state = *op_state;
                free(op_state);
            }

            if (op_state == NULL) {
                log_printf(1, "rs_simple_request: ERROR processing i=%d EMPTY STACK\n", i);
                found = 0;
                status.op_status = OP_STATE_FAILURE;
                status.error_code = RS_ERROR_EMPTY_STACK;
            } else if  (state == 1) { //** Got one
                log_printf(15, "rs_simple_request: processing i=%d ds_key=%s\n", i, rse->ds_key);
                found = 1;
                if ((i<fixed_size) && hints_list) hints_list[i].status = RS_ERROR_OK;

                for (k=0; k<req_size; k++) {
                    if (req[k].rid_index == i) {
                        log_printf(15, "rs_simple_request: i=%d ds_key=%s, rid_key=%s size=" XOT "\n", i, rse->ds_key, rse->rid_key, req[k].size);
                        req[k].rid_key = strdup(rse->rid_key);
                        req[k].gop = ds_allocate(rss->ds, rse->ds_key, da, req[k].size, caps[k], timeout);
                        opque_add(que, req[k].gop);
                    }
                }

                if (rid_change != NULL) { //** Flag that I'm tweaking things.  The caller does the source pending/delta half
                    rid_change->delta -= change;
                    rid_change->state = ((llabs(rid_change->delta) <= rid_change->tolerance) || (rid_change->tolerance == 0)) ? 1 : 0;
                }
                break;  //** Got one so exit the RID scan and start the next one
            } else if (i<fixed_size) {  //** This should have worked so flag an error
                if (hints_list) {
                   log_printf(1, "Match fail in fixed list[%d]=%s!\n", i, hints_list[i].fixed_rid_key);
                   hints_list[i].status = RS_ERROR_FIXED_MATCH_FAIL;
                } else {
                   log_printf(1, "Match fail in fixed list and no hints are provided!\n");
                }
                status.op_status = OP_STATE_FAILURE;
                status.error_code = RS_ERROR_FIXED_MATCH_FAIL;
                if (ignore_fixed_err == 0) err_cnt++;
                break;  //** Skip to the next in the list
            } else {
                found = 0;
            }
        }

        if ((found == 0) && (i>=fixed_size)) break;

    }


    //** Clean up
    log_printf(15, "FREE j=%d\n", unique_size);
    for (i=0; i<unique_size; i++) {
        free(kvq_global.unique[i]);
    }
    free(kvq_global.unique);
    free(kvq_global.pickone);

    free(kvq_local.unique[0]);
    free(kvq_local.unique);
    free(kvq_local.pickone);

    tbx_stack_free(stack, 1);

    log_printf(15, "rs_simple_request: END n_rid=%d\n", n_rid);

//callback_t *cb = (callback_t *)que->qd.list->top->data;
//op_generic_t *gop = (op_generic_t *)cb->priv;
//log_printf(15, "top gid=%d reg=%d\n", gop_id(gop), gop_id(req[0].gop));

    apr_thread_mutex_unlock(rss->lock);

    if ((found == 0) || (err_cnt>0)) {
        opque_free(que, OP_DESTROY);

        if (status.error_code == 0) {
            log_printf(1, "rs_simple_request: Can't find enough RIDs! requested=%d found=%d err_cnt=%d\n", n_rid, found, err_cnt);
            status.op_status = OP_STATE_FAILURE;
            status.error_code = RS_ERROR_NOT_ENOUGH_RIDS;
        }
        return(gop_dummy(status));
    }

    return(opque_get_gop(que));
}