void ContractionHierarchiesClient::computeStep( Heap* heapForward, Heap* heapBackward, const EdgeAllowed& edgeAllowed, const StallEdgeAllowed& stallEdgeAllowed, NodeIterator* middle, int* targetDistance ) {

	const NodeIterator node = heapForward->DeleteMin();
	const int distance = heapForward->GetKey( node );

	if ( heapForward->GetData( node ).stalled )
		return;

	if ( heapBackward->WasInserted( node ) && !heapBackward->GetData( node ).stalled ) {
		const int newDistance = heapBackward->GetKey( node ) + distance;
		if ( newDistance < *targetDistance ) {
			*middle = node;
			*targetDistance = newDistance;
		}
	}

	if ( distance > *targetDistance ) {
		heapForward->DeleteAll();
		return;
	}
	for ( EdgeIterator edge = m_graph.edges( node ); edge.hasEdgesLeft(); ) {
		m_graph.unpackNextEdge( &edge );
		const NodeIterator to = edge.target();
		const int edgeWeight = edge.distance();
		assert( edgeWeight > 0 );
		const int toDistance = distance + edgeWeight;

		if ( stallEdgeAllowed( edge.forward(), edge.backward() ) && heapForward->WasInserted( to ) ) {
			const int shorterDistance = heapForward->GetKey( to ) + edgeWeight;
			if ( shorterDistance < distance ) {
				//perform a bfs starting at node
				//only insert nodes when a sub-optimal path can be proven
				//insert node into the stall queue
				heapForward->GetKey( node ) = shorterDistance;
				heapForward->GetData( node ).stalled = true;
				m_stallQueue.push( node );

				while ( !m_stallQueue.empty() ) {
					//get node from the queue
					const NodeIterator stallNode = m_stallQueue.front();
					m_stallQueue.pop();
					const int stallDistance = heapForward->GetKey( stallNode );

					//iterate over outgoing edges
					for ( EdgeIterator stallEdge = m_graph.edges( stallNode ); stallEdge.hasEdgesLeft(); ) {
						m_graph.unpackNextEdge( &stallEdge );
						//is edge outgoing/reached/stalled?
						if ( !edgeAllowed( stallEdge.forward(), stallEdge.backward() ) )
							continue;
						const NodeIterator stallTo = stallEdge.target();
						if ( !heapForward->WasInserted( stallTo ) )
							continue;
						if ( heapForward->GetData( stallTo ).stalled == true )
							continue;

						const int stallToDistance = stallDistance + stallEdge.distance();
						//sub-optimal path found -> insert stallTo
						if ( stallToDistance < heapForward->GetKey( stallTo ) ) {
							if ( heapForward->WasRemoved( stallTo ) )
								heapForward->GetKey( stallTo ) = stallToDistance;
							else
								heapForward->DecreaseKey( stallTo, stallToDistance );

							m_stallQueue.push( stallTo );
							heapForward->GetData( stallTo ).stalled = true;
						}
					}
				}
				break;
			}
		}

		if ( edgeAllowed( edge.forward(), edge.backward() ) ) {
			//New Node discovered -> Add to Heap + Node Info Storage
			if ( !heapForward->WasInserted( to ) )
				heapForward->Insert( to, toDistance, node );

			//Found a shorter Path -> Update distance
			else if ( toDistance <= heapForward->GetKey( to ) ) {
				heapForward->DecreaseKey( to, toDistance );
				//new parent + unstall
				heapForward->GetData( to ).parent = node;
				heapForward->GetData( to ).stalled = false;
			}
		}
	}
}