    void DefaultZone::_findNodes( const Ray &t, 
							      PCZSceneNodeList &list, 
                                  PortalList &visitedPortals,
						 	      bool includeVisitors,
							      bool recurseThruPortals,
							      PCZSceneNode *exclude )
    {
		// if this zone has an enclosure, check against the enclosure AABB first
		if (mEnclosureNode)
		{
			std::pair<bool, Real> nsect = t.intersects(mEnclosureNode->_getWorldAABB());
			if (!nsect.first)
			{
				// AABB of zone does not intersect t, just return.
				return;
			}
		}

		// check nodes at home in this zone
	    PCZSceneNodeList::iterator it = mHomeNodeList.begin();
	    while ( it != mHomeNodeList.end() )
	    {
			PCZSceneNode * pczsn = *it;
			if ( pczsn != exclude )
			{
				// make sure node is not already in the list (might have been added in another
				// zone it was visiting)
				PCZSceneNodeList::iterator it2 = list.find(pczsn);
				if (it2 == list.end())
				{
					std::pair<bool, Real> nsect = t.intersects( pczsn -> _getWorldAABB() );
					if ( nsect.first )
					{
						list.insert( pczsn );
					}
				}
			}
		    ++it;
	    }

		if (includeVisitors)
		{
			// check visitor nodes
			PCZSceneNodeList::iterator iter = mVisitorNodeList.begin();
			while ( iter != mVisitorNodeList.end() )
			{
				PCZSceneNode * pczsn = *iter;
				if ( pczsn != exclude )
				{
					// make sure node is not already in the list (might have been added in another
					// zone it was visiting)
					PCZSceneNodeList::iterator it2 = list.find(pczsn);
					if (it2 == list.end())
					{
						std::pair<bool, Real> nsect = t.intersects( pczsn -> _getWorldAABB() );
						if ( nsect.first )
						{
							list.insert( pczsn );
						}
					}
				}
				++iter;
			}
		}

		// if asked to, recurse through portals
		if (recurseThruPortals)
		{
			PortalList::iterator pit = mPortals.begin();
			while ( pit != mPortals.end() )
			{
				Portal * portal = *pit;
				// check portal versus bounding box
				if (portal->intersects(t))
				{
					// make sure portal hasn't already been recursed through
					PortalList::iterator pit2 = std::find(visitedPortals.begin(), visitedPortals.end(), portal);
					if (pit2 == visitedPortals.end())
					{
						// save portal to the visitedPortals list
						visitedPortals.push_front(portal);
						// recurse into the connected zone 
						portal->getTargetZone()->_findNodes(t, 
															list, 
															visitedPortals,
															includeVisitors, 
															recurseThruPortals, 
															exclude);
					}
				}
				pit++;
			}
		}

	}