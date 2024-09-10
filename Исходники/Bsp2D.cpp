	Tree::PortalBuilder::SuperPlane* Tree::PortalBuilder::createSuperPlane( Node* node , Vec2f const& max , Vec2f const& min )
	{
		assert( !node->isLeaf() );

		SuperPlane* splane = new SuperPlane;
		splane->node  = node;
		splane->plane = mTree->getEdge( node->idxEdge ).plane;
		splane->tag   = mSPlanes.size();

		Portal portal;
		portal.con[0] = 0;
		portal.con[1] = 0;

		Vec2f v[4] = { max , Vec2f( min.x , max.y ) , min , Vec2f( max.x , min.y ) };
		for( int i = 0 , prev = 3 ; i < 4 ; prev = i++ )
		{
			Vec2f dir = v[ i ] - v[ prev ];
			float dot = dir.dot( splane->plane.normal );
			if ( abs( dot ) < FLOAT_EPSILON )
				continue;
			float t = ( v[i].dot( splane->plane.normal ) + splane->plane.d ) / dot;
			Vec2f p = v[i] + t * dir;
		}
	


		Node* cur = node->parent;
		while( cur )
		{




			cur = cur->parent;
		}

		return splane;
	}