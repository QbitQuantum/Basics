	System* VpdRetriever::getComponentTree( )
	{
		System *root = db->fetch( );
		if (root)
			buildSubTree( root );
		else
		{
			Logger logger;
			logger.log( "Failed to fetch VPD DB, it may be corrupt.", LOG_ERR );
			VpdException ve( "Failed to fetch VPD DB, it may be corrupt." );
			throw ve;
		}

		return root;
	}