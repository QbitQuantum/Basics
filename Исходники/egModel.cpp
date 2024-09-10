void ModelNode::updateStageAnimations( uint32 stage, const string &startNode )
{
	AnimationResource *anim = _animStages[stage]->anim;
	if( anim == 0x0 )
	{	
		for( size_t i = 0, s = _nodeList.size(); i < s; ++i ) 
		{
			_nodeList[i].animEntities[stage] = 0x0;
		}
		
		return;
	}

	// Find animation resource entries for nodes
	for( size_t i = 0, s = _nodeList.size(); i < s; ++i )
	{
		bool includeNode = true;
		
		if( startNode != "" )
		{
			includeNode = false;
			
			SceneNode *node = _nodeList[i].node;
			while( node->getType() != SceneNodeTypes::Model )
			{
				if( node->getName() == startNode )
				{
					includeNode = true;
					break;
				}
				node = node->getParent();
			}
		}
		
		if( includeNode )
			_nodeList[i].animEntities[stage] = anim->findEntity( _nodeList[i].node->getParamstr( SceneNodeParams::Name ) );
		else
			_nodeList[i].animEntities[stage] = 0x0;
	}
}