	PathNode* Pop()
	{
		#ifdef USE_LIST
		assert( sentinel->next != sentinel );
		PathNode* pNode = sentinel->next;
		pNode->Unlink();
			#ifdef DEBUG
				sentinel->CheckList();
			#endif
		#else
		PathNode* pNode = heapVector[0];

		const int size = heapVector.size();
		int found = 0;
		for( int i=1; i<size; ++i ) {
	   		if ( heapVector[i]->totalCost < pNode->totalCost ) {
	   			pNode = heapVector[i];
	   			found = i;
			}				
		}   
		if ( found < size-1 ) 
			memcpy( &heapVector[found], &heapVector[found+1], sizeof( PathNode* ) * (size-found-1) );
		heapVector.pop_back();
		#endif

		assert( pNode->inClosed == 0 );
		assert( pNode->inOpen == 1 );
		pNode->inOpen = 0;

		#ifdef DEBUG_PATH_DEEP
			printf( "Open Pop: " );
			graph->PrintStateInfo( pNode->state );
			printf( " total=%.1f\n", pNode->totalCost );		
		#endif

		return pNode;
	}