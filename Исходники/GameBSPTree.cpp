GameBSPTree::GameBSPTree( io::InputStreamArchive* arch, sg::Node* geometry, 
	const lang::String& bspFileName, int bspBuildPolySkip, 
	const Vector<P(GameSurface)>& collisionMaterialTypes, bsp::BSPTree* cachedBSPTree ) :
	m_tree( cachedBSPTree ),
	m_models( Allocator<MeshModelPair>(__FILE__) ),
	m_boundSphere( 0.f )
{
	if ( !m_tree )
	{
		// Construct BSP tree for collision detection if not found on disk
		if ( !File(bspFileName).exists() )
		{
			m_tree = buildBSP( geometry, bspBuildPolySkip );
			FileOutputStream output( bspFileName );
			BSPFile collisiontree( m_tree, &output );
		}
		else
		{
			P(InputStream) in = arch->getInputStream( bspFileName );
			BSPFile	collisiontree( in );
			m_tree = collisiontree.tree();
		}
	}

	// Find all (mesh,model) pairs in the hierarchy
	int modelPolys = 0;
	for ( Node* it = geometry ; it ; it = it->nextInHierarchy() )
	{
		Mesh* mesh = dynamic_cast<Mesh*>( it );

		if ( isCollidable(mesh) )
		{
			for ( int i = 0; i < mesh->primitives(); ++i )
			{
				Model* model = dynamic_cast<Model*>( mesh->getPrimitive(i) );

				if ( model )
				{
					// get collision material type
					P(GameSurface) surface = getCollisionMaterialType( model->shader()->name(), collisionMaterialTypes );
					MeshModelPair pair( mesh, model, surface );
					m_models.add( pair );
					modelPolys += model->indices()/3;
				}
			}
		}
	}
	Debug::println( "BSP {0} has {1} source polygons", bspFileName, modelPolys );

	// remove collision meshes
	for ( Node* it = geometry ; it ; it = it->nextInHierarchy() )
	{
		if ( !isVisual(it) )
		{
			Debug::println( "Removed collision object {0} from visual scene {1}", it->name(), geometry->name() );
			it->unlink();
			it = geometry;
		}
	}

	/*// DEBUG: count duplicate polygons
	Debug::println( "Computing BSP tree {0} polygon stats...", bspFileName );
	Vector<BSPPolygon> polys( Allocator<BSPPolygon>(__FILE__) );
	getPolys( m_root, polys );
	int bsppolys = polys.size();
	int dups = 0;
	for ( int i = 0 ; i < polys.size() ; ++i )
	{
		for ( int j = i+1 ; j < polys.size() ; ++j )
		{
			if ( polys[i] == polys[j] )
			{
				polys.remove( j-- );
				++dups;
			}
		}
	}
	Debug::println( "BSP tree has {1} polys ({0} unique, {2} duplicates), potential memsave={3,#}KB", polys.size(), bsppolys, dups, dups*sizeof(BSPPolygon)/1000 );
	*/

	m_boundSphere = computeBoundSphereRecurse( m_tree->root(), 0.f );
}