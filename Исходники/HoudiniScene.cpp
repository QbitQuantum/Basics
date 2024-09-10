bool HoudiniScene::hasTag( const Name &name, bool includeChildren ) const
{
	const OP_Node *node = retrieveNode();
	if ( !node )
	{
		return false;
	}
	
	// check for user supplied tags if we're not inside a SOP
	if ( !m_contentIndex && node->hasParm( pTags.getToken() ) )
	{
		UT_String parmTags;
		node->evalString( parmTags, pTags.getToken(), 0, 0 );
		if ( UT_String( name.c_str() ).multiMatch( parmTags ) )
		{
			return true;
		}
	}
	
	// check with the registered tag readers
	std::vector<CustomTagReader> &tagReaders = customTagReaders();
	for ( std::vector<CustomTagReader>::const_iterator it = tagReaders.begin(); it != tagReaders.end(); ++it )
	{
		if ( it->m_has( node, name ) )
		{
			return true;
		}
	}
	
	// check tags based on primitive groups
	OBJ_Node *contentNode = retrieveNode( true )->castToOBJNode();
	if ( contentNode && contentNode->getObjectType() == OBJ_GEOMETRY && m_splitter )
	{
		GU_DetailHandle newHandle = m_splitter->split( contentPathValue() );
		if ( !newHandle.isNull() )
		{
			GU_DetailHandleAutoReadLock readHandle( newHandle );
			if ( const GU_Detail *geo = readHandle.getGdp() )
			{
				GA_Range prims = geo->getPrimitiveRange();
				for ( GA_GroupTable::iterator<GA_ElementGroup> it=geo->primitiveGroups().beginTraverse(); !it.atEnd(); ++it )
				{
					GA_PrimitiveGroup *group = static_cast<GA_PrimitiveGroup*>( it.group() );
					if ( group->getInternal() || group->isEmpty() )
					{
						continue;
					}
					
					const UT_String &groupName = group->getName();
					if ( groupName.startsWith( tagGroupPrefix ) && group->containsAny( prims ) )
					{
						UT_String tag;
						groupName.substr( tag, tagGroupPrefix.length() );
						tag.substitute( "_", ":" );
						if ( tag.equal( name.c_str() ) )
						{
							return true;
						}
					}
				}
			}
		}
	}
	
	return false;
}