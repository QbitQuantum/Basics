/**
 *	Pass the sample list through the CSG node.
 *	The sample list will contain only the relevant entry and exit points for
 *	the resulting surface for this operation, and they will be promoted to
 *	this node for further processing up the tree.
 *
 *	@param	samples	Array of samples to process.
 */
void CqCSGTreeNode::ProcessSampleList( std::vector<SqImageSample>& samples )
{
	// First process any children nodes.
	// Process all nodes depth first.
	std::list<boost::weak_ptr<CqCSGTreeNode> >::const_iterator
	ii = lChildren().begin(), ie = lChildren().end();
	for (; ii != ie; ++ii)
	{
		// If the node is a primitive, no need to process it.
		// In fact as the primitive, just nulls out its owned samples
		// this would break the CSG code.
		boost::shared_ptr<CqCSGTreeNode> pChild = ii->lock()
		        ;
		if ( pChild.get() && pChild->NodeType() != CSGNodeType_Primitive )
			pChild->ProcessSampleList( samples );
	}

	std::vector<bool> abChildState( cChildren() );
	std::vector<TqInt> aChildIndex( samples.size() );
	TqInt iChild;
	for ( iChild = 0; iChild < cChildren(); iChild++ )
		abChildState[ iChild ] = false;

	// Now get the initial state
	bool bCurrentI = false;

	// Find out if the camera is starting inside a solid. This is the case if you
	// see an odd number of walls for that solid when looking out.
	std::vector<SqImageSample>::iterator i;
	TqInt j = 0;
	for ( i = samples.begin(); i != samples.end(); ++i, ++j )
	{
		if ( ( aChildIndex[j] = isChild( i->csgNode.get() ) ) >= 0 )
		{
			if ( ((i->csgNode.get())->NodeType() == CSGNodeType_Primitive ) &&
			        ((i->csgNode.get())->NodeType() == CSGNodeType_Union ) )
			{
				abChildState[ aChildIndex[j] ] = !abChildState[ aChildIndex[j] ];
			}
		}
	}

	bCurrentI = EvaluateState( abChildState );

	// Now go through samples, clearing any where the state doesn't change, and
	// promoting any where it does to this node.
	for ( i = samples.begin(), j = 0; i != samples.end(); ++j )
	{
		// Find out if sample is in out children nodes, if so are we entering or leaving.
		if ( aChildIndex[j] >= 0 )
			abChildState[ aChildIndex[j] ] = !abChildState[ aChildIndex[j] ];
		else
		{
			++i;
			continue;
		}

		// Work out the new state
		bool bNewI = EvaluateState( abChildState );

		// If it hasn't changed, remove the sample.
		if ( bNewI == bCurrentI )
			i = samples.erase( i );
		else
			// Otherwise promote it to this node unless we are a the top.
		{
			bCurrentI = bNewI;
			if ( pParent() )
			{
				i->csgNode = shared_from_this();
			}
			else
			{
				i->csgNode = boost::shared_ptr<CqCSGTreeNode>();
			}
			i++;
		}
	}
}