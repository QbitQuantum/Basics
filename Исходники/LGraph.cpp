void clGraph::From2DGrid( const LVector3& Center, const LVector3& V1, const LVector3& V2, float SizeX, float SizeY, int Nx, int Ny, int Conn )
{
	ClearGraph();

	LVector3 N = V1.Cross( V2 );

	// common orientation for all nodes
	LQuaternion Orientation;
	Orientation.FromAxisAngle( N, 0.0f );

	float CellX = SizeX / Nx;
	float CellY = SizeY / Ny;

	FOriented = false;

	FLocalOrientations.resize( Nx * Ny );
	FVertices.resize( Nx * Ny );

	for ( int i = 0 ; i < Nx ; i++ )
	{
		for ( int j = 0 ; j < Ny ; j++ )
		{
			int ThisNode = NodeForPair( i, j, Nx, Ny );

			FLocalOrientations[ThisNode] = Orientation;

			FVertices[ThisNode] = Center + V1 * static_cast<float>( i - Nx / 2 ) * CellX + V2 * static_cast<float>( j - Ny / 2 ) * CellY;

			// add 4-connected edges
			int West  = NodeForPair( i - 1, j, Nx, Ny );
			int East  = NodeForPair( i + 1, j, Nx, Ny );
			int North = NodeForPair( i, j - 1, Nx, Ny );
			int South = NodeForPair( i, j - 1, Nx, Ny );

			if ( West > -1 )  { FEdge0.push_back( ThisNode ); FEdge1.push_back( West );  }

			if ( East > -1 )  { FEdge0.push_back( ThisNode ); FEdge1.push_back( East );  }

			if ( North > -1 ) { FEdge0.push_back( ThisNode ); FEdge1.push_back( North ); }

			if ( South > -1 ) { FEdge0.push_back( ThisNode ); FEdge1.push_back( South ); }

			if ( Conn > 4 )
			{
				int NW = NodeForPair( i - 1, j - 1, Nx, Ny );
				int NE = NodeForPair( i + 1, j - 1, Nx, Ny );
				int SW = NodeForPair( i - 1, j + 1, Nx, Ny );
				int SE = NodeForPair( i + 1, j + 1, Nx, Ny );

				if ( NW > -1 ) { FEdge0.push_back( ThisNode ); FEdge1.push_back( NW ); }

				if ( NE > -1 ) { FEdge0.push_back( ThisNode ); FEdge1.push_back( NE ); }

				if ( SW > -1 ) { FEdge0.push_back( ThisNode ); FEdge1.push_back( SW ); }

				if ( SE > -1 ) { FEdge0.push_back( ThisNode ); FEdge1.push_back( SE ); }
			}
		}
	}
}