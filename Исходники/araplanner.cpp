void ARAPlanner::BuildNewOPENList(ARASearchStateSpace_t* pSearchStateSpace)
{
    ARAState *state;
    CKey key;
    CHeap* pheap = pSearchStateSpace->heap;
    CList* pinconslist = pSearchStateSpace->inconslist;

    //move incons into open
    while (pinconslist->firstelement != NULL) {
        state = (ARAState*)pinconslist->firstelement->liststate;

        //compute f-value
        key.key[0] = state->g + (int)(pSearchStateSpace->eps * state->h);
        //key.key[1] = state->h;

        //insert into OPEN
        pheap->insertheap(state, key);
        //remove from INCONS
        pinconslist->remove(state, ARA_INCONS_LIST_ID);
    }
}