void ADPlanner::BuildNewOPENList(ADSearchStateSpace_t* pSearchStateSpace)
{
	ADState *state;
	CKey key;
	CHeap* pheap = pSearchStateSpace->heap;
	CList* pinconslist = pSearchStateSpace->inconslist; 
		
	//move incons into open
	while(pinconslist->firstelement != NULL)
	  {
	    state = (ADState*)pinconslist->firstelement->liststate;
	    
	    //compute f-value
		key = ComputeKey(state);
	    
	    //insert into OPEN
	    pheap->insertheap(state, key);
	    //remove from INCONS
	    pinconslist->remove(state, AD_INCONS_LIST_ID);
	  }
}