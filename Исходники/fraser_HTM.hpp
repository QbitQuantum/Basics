/*
 * [lyj] Disable the interpretation of "deleted" field.
 */
void fraser_insert(sl_intset_t *set, uint32_t v, bool lin)
{
    sl_node_t *NEW, *new_next, *pred, *succ, *succs[LEVELMAX], *preds[LEVELMAX];
    uint32_t i;
    uint32_t status;
   // uint32_t attempts = 0;
    NEW = sl_new_simple_node(v, get_rand_level(), lin);
retry:
    fraser_search(set, v, preds, succs);
    for (i = 0; i < NEW->toplevel; i++)
        NEW->nexts[i] = succs[i];
    /* Node is visible once inserted at lowest level */
    if (!ATOMIC_CAS_MB(&preds[0]->nexts[0], succs[0], NEW))
        goto retry;
    
//retry_HTM:
    status = _xbegin();
    if(status == _XBEGIN_STARTED)
    {
        for (i = 1; i < NEW->toplevel; i++) {
            if(preds[i]->nexts[i] == succs[i])
                preds[i]->nexts[i] = NEW;
            else
                _xabort(66);
        }
        _xend();
        return;
    }/*else
    {
        if ((status & _XABORT_EXPLICIT) && _XABORT_CODE(status) == 66) {
        }
        else if (++attempts < MAX_ATTEMPT_NUM) {
            goto retry_HTM;
        }
    }*/
    
    for (i = 1; i < NEW->toplevel; i++) {
        while (1) {
            pred = preds[i];
            succ = succs[i];
            /* Update the forward pointer if it is stale */
            new_next = NEW->nexts[i];
            if ((new_next != succ) &&
                (!ATOMIC_CAS_MB(&NEW->nexts[i], unset_mark((uint32_t)new_next), succ)))
                break;
            /* Give up if pointer is marked */
            /* We retry the search if the CAS fails */
            if (ATOMIC_CAS_MB(&pred->nexts[i], succ, NEW))
                break;
            fraser_search(set, v, preds, succs);
        }
    }
}