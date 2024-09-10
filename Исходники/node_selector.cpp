//---------------------------------------------------------------------------
void NodeSelector::centerOfSelection( Vector3& centerOfSelection )
{
	if (selectionList_.size( ) == 0)
		return;

    centerOfSelection.setZero( );

    SceneNodeVector::iterator it  = selectionList_.begin( );
	SceneNodeVector::iterator end = selectionList_.end( );

    while ( it != end )
    {
        SceneNode *node = (*it);


        //accumulate location
        /*BoundingBox bb = node->boundingBox( );

        //transfrom bounding box to world coords
        bb.transformBy( node->worldTransform( ) );

        Vector3 centerOfNode = ( bb.minBounds() + bb.maxBounds() ) / 2.f;

        centerOfSelection += centerOfNode;*/

        centerOfSelection += node->worldTransform( ).applyToOrigin();

        it++;
    }

    // the height for center of selection is the height of the origin of the
    // last node in world space or what is in effect the current floor height
    //if ( selectionList_.size( ) )
	//    centerOfSelection[1] = (*(end-1))->worldTransform()[3][1];

	//size of vector is guaranteed not to be zero
	centerOfSelection /= selectionList_.size( );
}