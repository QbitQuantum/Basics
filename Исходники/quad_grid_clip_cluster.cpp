// ***************************************************************************
void		CQuadGridClipClusterQTreeNode::clip(CClipTrav *clipTrav)
{
	// if empty (test important for branch and leave clusters)
	if(Empty)
		return;

	H_BEFORE( NL3D_QuadClip_NodeClip );

	// Then clip against pyramid
	bool	unspecified= false;
	bool	visible= true;
	for(sint i=0;i<(sint)clipTrav->WorldPyramid.size();i++)
	{
		// We are sure that pyramid has normalized plane normals.
		if(!BBoxExt.clipBack(clipTrav->WorldPyramid[i]))
		{
			visible= false;
			break;
		}
		// else test is the bbox is partially or fully in the plane
		else if(!unspecified)
		{
			// if clipFront AND clipBack, it means partially.
			if(BBoxExt.clipFront(clipTrav->WorldPyramid[i]))
				unspecified= true;
		}
	}

	H_AFTER( NL3D_QuadClip_NodeClip );

	// if visible, parse sons
	if(visible)
	{
		// clip sons or cluster sons
		if(unspecified)
		{
			if( LeafNode)
			{
				// clip DistMax.
				CVector		c= BBoxExt.getCenter();
				float		dist= (c - clipTrav->CamPos).norm();
				dist-= BBoxExt.getRadius();
				sint	minDistSetup= (sint)floor(Owner->_NumDist*dist/Owner->_DistMax);
				// NB if too far, set _NumDist (ie will clip only the infinite objects ones)
				clamp(minDistSetup, 0, (sint)Owner->_NumDist);

				// clip the sons individually
				H_AUTO( NL3D_QuadClip_SonsClip );
				ListNode.clipSons(minDistSetup);
			}
			else
			{
				// clip cluster sons
				Sons[0]->clip(clipTrav);
				Sons[1]->clip(clipTrav);
				Sons[2]->clip(clipTrav);
				Sons[3]->clip(clipTrav);
			}
		}
		else
		{
			// udpdate the sons, but don't clip, because we know they are fully visible.
			clipTrav->ForceNoFrustumClip= true;

			// show all cluster sons or sons
			noFrustumClip(clipTrav);

			// reset flag
			clipTrav->ForceNoFrustumClip= false;
		}
	}
}