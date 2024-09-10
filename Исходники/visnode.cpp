//
// attachChild
//
bool VisNode::attachChild( shared_ptr<Visible> child )
{
	// Attaching myself as a child will cause an infinite loop, disallow
	if ( child.get() == this ) return false;

	// Setup the Hierarchy
	child->setParent( this->shared_from_this() );

	/// Add it to our node array
	m_children.push_back( child );
	
	return true;
}