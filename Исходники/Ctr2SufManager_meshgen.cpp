void Ctr2SufManager::ctr2sufProc(vector<vector<Point_3> >& MeshBoundingProfile3D,vector<Point_3>& vecTestPoint)
{
	clock_t   start   =   clock();   
	struct __timeb64 timebuffer;
	char *timeline;
	_ftime64( &timebuffer );
	timeline = _ctime64( & ( timebuffer.time ) );
	printf( "The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20] );

	//common line case
	//compute the common line
	if( isComnCase )	
	{
		float tempparam[ 8 ];
		for( int i = 0; i < 8; i ++)
		{
			tempparam[ i  ] = pparam[ i ];
		}

		//////////////////////////////////////////////////////////////////////////
		/*for( int i = 0 ; i < 8; i ++ )
		{
			cout<<tempparam[ i ]<<",";
		}
		cout<<endl;*/
		//////////////////////////////////////////////////////////////////////////

		computeComnLine( tempparam, tempparam + 4, comndir, comnpt);
		//////////////////////////////////////////////////////////////////////////
		/*for( int i = 0 ; i < 8; i ++ )
		{
			cout<<tempparam[ i ]<<",";
		}
		cout<<endl;*/
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//writeComnLineDB( tempparam, tempparam + 4, comndir, comnpt);
		//////////////////////////////////////////////////////////////////////////
	}

	//////////////////////////////////////////////////////////////////////////
	/*for( int i = 0; i < planenum + 4; i ++ )
	{
		cout<<pparam[ 4* i ]<<","
			<<pparam[ 4*i + 1]<<","
			<<pparam[ 4*i + 2]<<","
			<<pparam[ 4*i + 3]<<endl;
	}
	cout<<endl;*/
	//////////////////////////////////////////////////////////////////////////

	//preprocess data first
	int** pctrvermark;

	if( !ispreproced || isComnCase)
	{
		pctrvermark = preProcData(isComnCase);
		//reset showcontourvers
		for( int i = 0; i < showplanenum; i ++)
			delete []showctrvers[ i ];
		delete []showctrvers;

		//copy the data from processed data, and reset size
		showplanenum = planenum;
		showctrvers = new float*[ showplanenum ];
		showctredgenum = new int[ showplanenum ];
		showctredges = new int*[ showplanenum ];
		for( int i = 0; i < showplanenum; i++ )
		{
			int versize = pctrvernum[ i ]*3; 
			showctrvers[ i ] = new float[ versize ];
			for( int j = 0 ; j < versize;  j ++ )
				showctrvers[ i ][ j ] = pctrvers[ i ][ j ]*DIM/PROCSIZE;

			showctredgenum[ i ] = pctredgenum[ i ];
			int edgesize = pctredgenum[ i ] * 2;			
			showctredges[ i ] = new int[ edgesize ];
			for( int  j = 0; j < showctredgenum[ i ]; j ++)
			{
				showctredges[ i ][ 2*j ] = pctredges[ i ][ 4*j ];
				showctredges[ i ][ 2*j + 1 ] = pctredges[ i ][ 4*j + 1];
			}
		}

		for( int i = 0; i < planenum; i ++)
		{
			int iVerIndBase=0;
			vector<Point_3> CurrentProfile3D;
			for( int j = 0;j < showctredgenum[ i ]; j++)
			{

				int v1 = showctredges[ i ][ 2*j ];
				int v2 = showctredges[ i ][ 2*j + 1 ];

				CurrentProfile3D.push_back(Point_3(showctrvers[ i ][ v1* 3],
					showctrvers[ i ][ v1* 3+1],
					showctrvers[ i ][ v1* 3+2]));

				if (v2==iVerIndBase)
				{
					iVerIndBase=iVerIndBase+CurrentProfile3D.size();
					MeshBoundingProfile3D.push_back(CurrentProfile3D);
					CurrentProfile3D.clear();
				}
			}
		}
		//for( int i = 0; i < planenum; i ++)
		//{	
		//	vector<Point_3> CurrentProfile3D;
		//	for( int j = 0;j < showctredgenum[ i ]; j++)
		//	{
		//		int v1 = showctredges[ i ][ 2*j ];
		//		glVertex3fv( &showctrvers[ i ][ v1* 3] );
		//		CurrentProfile3D.push_back(Point_3(showctrvers[ i ][ v1* 3],
		//								showctrvers[ i ][ v1* 3+1],
		//								showctrvers[ i ][ v1* 3+2]));
		//	}
		//	MeshBoundingProfile3D.push_back(CurrentProfile3D);
		//}

	}
	//////////////////////////////////////////////////////////////////////////
	//for( int i = 0; i < planenum + 4; i ++ )
	//{
	//	cout<<pparam[ 4* i ]<<","
	//		<<pparam[ 4*i + 1]<<","
	//		<<pparam[ 4*i + 2]<<","
	//		<<pparam[ 4*i + 3]<<endl;
	//}
	//cout<<endl;
	//////////////////////////////////////////////////////////////////////////
	//partition
//	cout<<"------------------ PARTITION ------------------"<<endl;
//	cout<<"Starting............"<<endl;
	partition();	

	///////////////////////////////////////////////////////////B///////////////
	/*writePartitionOut("mmdebug/partition.txt");*/
	//////////////////////////////////////////////////////////////////////////
//	cout<<"DONE!"<<endl<<endl;
	
	//process data
//	cout<<"------------------ PUT CONTOUR INTO FACE ------------------"<<endl;
	putContourIntoFace( pctrvermark );

	//SaveCtr2FaceInfo();


	if( isComnCase )
	{
		for( int i = 0; i < planenum; i ++ )
			delete []pctrvermark[ i ];
		delete []pctrvermark;
	}

	//////////////////////////////////////////////////////////////////////////
//	ContourHandler::writeContourInFace( ssfacenum, ctrfvernum, ctrfverpos, ctrfvertype, 
//		ctrfverval, ctrfedgenum, ctrfedge, ctrfedgetype, ctrfedgeval );	
	//////////////////////////////////////////////////////////////////////////
//	cout<<"DONE!"<<endl<<endl;

	
	//go through each subspace to generate mesh
//	cout<<"-------- GENERATING MESH IN EACH SUBSPACE ------------"<<endl;
	//kw noted: vertices, edges and faces in each subspace
	//stitch them together finally
	floatvector* subMeshVer;
	intvector* subMeshEdge;
	intvector* subMeshFace;
	subMeshVer = new floatvector[ ssspacenum ];
	subMeshEdge = new intvector[ ssspacenum ];
	subMeshFace = new intvector[ ssspacenum ];

	//initialize registration informaiton for stitching
	sverreg = new intvector[ ssvernum ];
	sedgereg = new vector<intvector>[ ssedgenum ];
	sedgesubedgemark = new intvector[ ssedgenum ];
	sfacectrei = new intset[ ssfacenum ];
	sfacespaci = new int[ ssfacenum * 2 ];
	sfaceregface = new vector<intvector>[ ssfacenum ];
	sfaceregver = new intvector[ ssfacenum ];
	sfaceregedgever = new intvector[ ssfacenum ];
	for( int i = 0; i < ssfacenum*2; i ++)
	{
		sfacespaci[ i ] = -1;
	}
	for( int spacei = 0; spacei < ssspacenum; spacei ++)
	{
		for( int facej = 0; facej < ssspacefacenum[ spacei ]; facej ++)
		{
			int facei = ssspace[ spacei ][ facej ];
			if( sfacespaci[ 2 * facei ] == -1)
				sfacespaci[ 2 * facei ] = spacei;
			else
				sfacespaci[ 2*facei + 1 ] = spacei;
		}
	}
	
	//////////////////////////////////////////////////////////////////////////
	/*ancestorlist.resize( ssfacenum * 2 );
	ancestorlist_split.resize( ssfacenum * 2 );*/
	//////////////////////////////////////////////////////////////////////////

	//return;

	dbSpaceNum = ssspacenum; 
	if( dbOneSpaceMode )
	{
		if( dbCurSpace < dbSpaceNum )
		{
			ctr2sufSubspaceProc( dbCurSpace, subMeshVer[ dbCurSpace ], subMeshEdge[ dbCurSpace ], subMeshFace[ dbCurSpace ]);

			//submeshedge is useless for stitching!
			subMeshEdge[ dbCurSpace ].clear();
		}
	}
	//kw: here can use multi-thread to compute each submesh in parallel
	else{
		//	for( int i = 7; i< 8; i ++)

		for( int i = 0; i < ssspacenum; i ++)
			//	for( int i = 2; i < 3; i ++)
			//	for( int i = 54; i < 55; i ++)
			//	for(int i = 0; i < 12; i ++)
			//	for( int i = 14; i < 15; i ++)
		{
					cout<<"--- subspace " << i <<endl;
			ctr2sufSubspaceProc( i, subMeshVer[ i ], subMeshEdge[ i ], subMeshFace[ i ]);

			//submeshedge is useless for stitching!
			subMeshEdge[ i ].clear();
		}
	}

	delete []subMeshEdge;

	//////////////////////////////////////////////////////////////////////////
	//cout<<"before splitting, ancestors:"<<endl;
	//for( int i = 0; i < ssfacenum*2; i +=2 )
	//{
	//	if( ancestorlist[ i ].size() == 0 )
	//	{
	//		if( ancestorlist[ i + 1].size() == 0 )
	//			continue;
	//	}
	//	intset::iterator iter = ancestorlist[ i ].begin();
	////	intset::iterator iter2 = ancestorlist[ i + 1].begin();
	//	while( iter != ancestorlist[ i ].end() )
	//	{
	//		cout<<*iter<<" ";
	//		iter++;
	//	}
	//	cout<<endl;
	//	iter = ancestorlist[ i+1 ].begin();
	//	while( iter != ancestorlist[ i + 1 ].end() )
	//	{
	//		cout<<*iter <<" ";
	//		iter ++;
	//	}
	//	cout<<endl;
	//	cout<<"\n";
	//}
	//cout<<"=============================\n";
	//cout<<"after splitting ancestors:"<<endl;
	//for( int i= 0; i < ssfacenum*2; i += 2 )
	//{
	//	if( ancestorlist_split[ i ].size() == 0 )
	//	{
	//		if( ancestorlist_split[ i + 1].size() == 0)
	//			continue;
	//	}
	//	intset::iterator iter = ancestorlist_split[ i ].begin();
	//	while( iter != ancestorlist_split[ i ].end() )
	//	{
	//		cout<<*iter <<" ";
	//		iter++;
	//	//	cout<<endl;
	//	}
	//	cout<<endl;
	//	iter = ancestorlist_split[ i + 1].begin();
	//	while( iter != ancestorlist_split[ i + 1].end() )
	//	{
	//		cout<<*iter <<" ";
	//		iter ++;
	//	}
	//	cout<<endl<<endl;
	//}


	//////////////////////////////////////////////////////////////////////////
	//cout the faces registered on the contour edges 
	/*for( int i = 0; i < ssfacenum; i ++ )
	{
		int ctrnum = sfaceregface[ i ].size()/2;
		if( ctrnum == 0 )
			continue;
		intset::iterator iter = ancestorlist_split[2* i ].begin();
		for( int j = 0; j < ctrnum; j ++ )
		{
			cout<<"("<<*iter<<":"<<sfaceregface[ i ][ 2*j ] .size()<<","<<
				sfaceregface[ i ][ 2*j +1 ].size()<<")  ";
			iter++;
		}
		cout<<endl;
	}*/
	//////////////////////////////////////////////////////////////////////////

	//for( int i = 0; i < ssfacenum; i ++)
	//{
	//	ancestorlist[ i].clear();
	//	ancestorlist_split[ i ].clear();
	//}
	//ancestorlist_split.clear();
	//ancestorlist.clear();
	//////////////////////////////////////////////////////////////////////////


	//stitch all the subspaces together
	stitchMesh(subMeshVer,subMeshFace);

	clock_t   endt   =   clock();
	cout<<"time difference is:"<<endt - start<<endl;
//	struct __timeb64 timebuffer;
//	char *timeline;
	_ftime64( &timebuffer );
	timeline = _ctime64( & ( timebuffer.time ) );
	printf( "The time is %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[20] );


//	FaceGenerator::writeSubMeshOut( mver, mface, 99);

	//clear all the allocated space
	//for( int i = 0; i < ssspacenum; i ++)
	//{
	//	//subMeshVer[ i ].clear();
	////	subMeshEdge[ i ].clear();
	//	subMeshFace[ i ].clear();
	//}
	////delete []subMeshVer;
	////delete []subMeshEdge;
	//delete []subMeshFace;
	/*subMeshFace = NULL;
	subMeshVer = NULL;*/

	//clear the registration information for subspace vertex, edge and face
	//sverreg
	for( int i = 0; i < ssvernum; i ++)
		sverreg[ i ].clear();
	delete []sverreg;
	sverreg = NULL;

	//sedgereg
	for( int i= 0; i < ssedgenum; i ++)
	{
		for(unsigned int j = 0; j < sedgereg[ i ].size(); j ++)
			sedgereg[ i ][ j ].clear();
		sedgereg[ i ].clear();
	}
	delete []sedgereg;
	sedgereg = NULL;

	//sfacectrei, sfacespaci, sfaceregface, sfaceregver
	for( int i= 0; i < ssfacenum; i ++)
	{
		sfacectrei[ i ].clear();
		
	//	for( int j = 0; j < sfaceregface[ i ].size();  j ++ )
    //       sfaceregface[ i ][ j ].clear();
	//	sfaceregface[ i ].clear();
		sfaceregver[ i ].clear();
	}	
	delete []sfacectrei;
	delete []sfacespaci;
	//delete []sfaceregface;
	delete []sfaceregver;
	sfacectrei = NULL;
	sfacespaci = NULL;
	//sfaceregface = NULL;
	sfaceregver = NULL;

	//set the mesh
	//clear
	if( mesh!= NULL )
		delete mesh;

	//set
	mesh = new Mesh( mver, mface, ctrmedge, 
		center,  unitlen, PROCSIZE );
	
	////kw: get constrained vertices
	//set<int> ConstrVer;
	//for (unsigned int i=0;i<ctrmedge.size();i++)
	//{
	//	ConstrVer.insert(ctrmedge.at(i));
	//}
	//for (set<int>::iterator SetIter=ConstrVer.begin();SetIter!=ConstrVer.end();SetIter++)
	//{
	//	vecTestPoint.push_back(Point_3(mver.at(3*(*SetIter))*DIM/PROCSIZE,mver.at(3*(*SetIter)+1)*DIM/PROCSIZE,
	//		mver.at(3*(*SetIter)+2)*DIM/PROCSIZE));
	//}

	mesh->setGLParam( width, height, nearplane, farplane);

	//clear
	mver.clear();
	mface.clear();
	ctrmedge.clear();
}