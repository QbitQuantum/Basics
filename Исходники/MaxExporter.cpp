int	MaxExporter::DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{

	/*if(!suppressPrompts)
		DialogBoxParam(hInstance, 
				MAKEINTRESOURCE(IDD_PANEL), 
				GetActiveWindow(), 
				MaxExporterOptionsDlgProc, (LPARAM)this);*/

	#pragma message(TODO("return TRUE If the file is exported properly"))

	Node::s_nextID = 1;
	ofstream myFile;
	myFile.open("DebugExporter.txt");
	wstring wFileName( name );
	string fileName( wFileName.begin(), wFileName.end() );
	//f= fopen( fileName.c_str(),"wb");
	BinaryFile = loadSave( fileName.c_str() );
	//BinaryFile.saveInt( 5 );
	//BinaryFile.close();
	myFile << "Start Export\n";

	IGameScene* gameScene = GetIGameInterface();
	gameScene->InitialiseIGame();
	int nodeCount = gameScene->GetTopLevelNodeCount();
	myFile << "Number of top level nodes: " << nodeCount << "\n";
	//get all of the materials
	for( int nodeNumber = 0; nodeNumber < nodeCount; ++nodeNumber)
	{
		IGameNode* gameNode = gameScene->GetTopLevelNode( nodeNumber );
		
		Node* myNode = new Node( gameNode );
		m_NodeList.push_back( myNode );
		findFaces( myNode, myFile );
		
	}

	myFile << "Number of materials\n";
	myFile << m_materialSet.size() << "\n";
	

	int totalBatches = 0;
	//myFile<< "Number of triangleBatchMaps: " << m_triangleBatchesPerNode.size() << "\n";
	for( auto nodeIter = m_NodeList.begin(); nodeIter != m_NodeList.end(); ++nodeIter )
	{
		std::map< IGameMaterial*, TriangleBatch* > triangleBatches = (*nodeIter)->m_triangleBatchesPerMaterial;
		myFile << "Invidiual triangleBatch size: " << triangleBatches.size() << "\n";

		for( auto materialIter = m_materialSet.begin(); materialIter != m_materialSet.end(); ++materialIter )
		{
			auto found = triangleBatches.find( * materialIter );
			if( found != triangleBatches.end() )
			{
				++totalBatches;
			}
		}
	}

	BinaryFile.saveInt( m_NodeList.size() );
	myFile << "Number of Nodes: " << m_NodeList.size() << "\n";
	
	for( auto nodeIter = m_NodeList.begin(); nodeIter != m_NodeList.end(); ++nodeIter )
	{
		std::map< IGameMaterial*, TriangleBatch* > triangleBatches = (*nodeIter)->m_triangleBatchesPerMaterial;
		std::map<IGameMaterial*, std::vector< NodeFace > > facesPerMaterial = (*nodeIter)->m_facesPerMaterial;
		IGameNode* currentNode = (*nodeIter)->m_gameNode;
		IGameNode* parentNode;
		GMatrix parentWTM;
		GMatrix toParentMatrix;
		GMatrix worldTM;
		GMatrix localTM;
		int time = gameScene->GetSceneStartTime();
		for( ; time < gameScene->GetSceneEndTime(); time += 4800/30 )
		{
			if( (*nodeIter)->m_parentID != 0 )
			{
				myFile << "Trying to find parent... \n";
				parentNode = (*nodeIter)->m_parent->m_gameNode;
				if( parentNode != nullptr )
				{
					myFile << "Parent found \n";
					parentWTM = parentNode->GetWorldTM( time );
					toParentMatrix = parentWTM.Inverse();

					worldTM = currentNode->GetWorldTM(  time ) * toParentMatrix;

				}

			}
			else
			{
				worldTM = currentNode->GetWorldTM( time );
				
			}
			(*nodeIter)->m_toParentMatrix.push_back( Matrix4x4( worldTM[0], worldTM[1], worldTM[2], worldTM[3] ) );
		}


		localTM = currentNode->GetWorldTM().Inverse();
		(*nodeIter)->m_worldToLocal = Matrix4x4(  localTM[0], localTM[1], localTM[2], localTM[3] );
		

		//Save the node
		BinaryFile.saveNode( *nodeIter, myFile );
		BinaryFile.saveInt( (*nodeIter)->m_triangleBatchesPerMaterial.size() );
	
		for( auto materialIter = m_materialSet.begin(); materialIter != m_materialSet.end(); ++materialIter )
		{
			//Set the current material's VBO and IBO
			//
			IGameMaterial* currentMaterial = *materialIter;
			TriangleBatch* currentBatch = triangleBatches[ currentMaterial ];
			
			GMatrix localTMNoTrans = localTM;
			localTMNoTrans.SetRow( 3, Point4( 0,0,0,1) );
			if( currentBatch != nullptr )
			{
				
				MaxMaterial* currentMaxMaterial = currentBatch->m_material;
				VBO* currentVBO = currentBatch->m_vbo;
				IBO* currentIBO = currentBatch->m_ibo;
				vector< NodeFace >& faceVector = facesPerMaterial.find( currentMaterial )->second;

				//Get texture materials and export them
				//
				if( currentMaterial != nullptr )
				{
					int numOfTexMaps = currentMaterial->GetNumberOfTextureMaps();
					myFile << "Number of texture maps: " << numOfTexMaps << "\n";
					for( int i = 0; i < numOfTexMaps; ++i )
					{
						IGameTextureMap* gameTextureMap = currentMaterial->GetIGameTextureMap( i );
						
						if( gameTextureMap != nullptr && gameTextureMap->IsEntitySupported() )
						{
							int stdMapSlot = gameTextureMap->GetStdMapSlot();
							if( stdMapSlot == ID_DI )
							{
								wstring wBitmapFileName;
								wBitmapFileName = gameTextureMap->GetBitmapFileName();
								if( wBitmapFileName.size() > 0 )
								{
									BitmapInfo bi( gameTextureMap->GetBitmapFileName() );
									BMMGetFullFilename( &bi );
									wBitmapFileName = bi.Name();
									std::string fullBitmapFileName( wBitmapFileName.begin(), wBitmapFileName.end() );
									if( fullBitmapFileName.size() > 0 )
									{
										int lastSlash = fullBitmapFileName.find_last_of('\\') + 1;
										if( lastSlash != string::npos )
										{
											const std::string bitmapFileName = fullBitmapFileName.substr( lastSlash );
											wstring nameAsWString( name );
											std::string nameAsString( nameAsWString.begin(), nameAsWString.end() );
											const std::string extension = nameAsString.substr( 0, nameAsString.find_last_of('\\') + 1 );
											std::string newFileName = extension;
											newFileName.append( bitmapFileName );
											wstring wNewFileName(newFileName.begin(), newFileName.end());
											if( CopyFile( wBitmapFileName.c_str(), wNewFileName.c_str(), false ) )
											{
												if( stdMapSlot == ID_DI )
												{
													currentMaxMaterial->m_diffuseTexture = bitmapFileName;
													currentMaxMaterial->bHasDiffuseTexture = true;
												}
											//BinaryFile.saveString( bitmapFileName );
											}
											else
											{
												myFile << GetLastError() << "\n";
												myFile << "copying the file FAILED.\n";
											}
										}
									}	
								}
							}
						}
					}
				}
				
				myFile<< "Number of faces for this material: " << faceVector.size() << "\n";
				for( int face = 0; face < faceVector.size(); ++face )
				{
					FaceEx* meshFace = faceVector[face].m_face;
					IGameMesh* gameMesh = faceVector[face].m_mesh;
					IGameSkin* gameSkin = gameMesh->GetIGameSkin();
					int position, normal, color, texCoordinate, maxPosition;
					for( int i = 0; i < 3; ++i)
					{
						
						maxPosition = (int)meshFace->vert[i];
						
						Point3 tempPos = gameMesh->GetVertex( maxPosition );
						tempPos = tempPos * localTM;
						Vector3D positionVec3( tempPos.x, tempPos.y, tempPos.z );
						position = currentVBO->insertPosition(positionVec3);

						normal = (int)meshFace->norm[i];
						Point3 tempNormal = gameMesh->GetNormal( normal );
						tempNormal = tempNormal * localTMNoTrans;
						tempNormal = tempNormal.Normalize();
						
						Vector3D normalVec3( tempNormal.x, tempNormal.y, tempNormal.z );
						normal = currentVBO->insertNormal(normalVec3);

						//IBO
						texCoordinate = (int)meshFace->texCoord[i];
						Point2 tempTexCoord = gameMesh->GetTexVertex( texCoordinate );
						Vector2 texCoordVec2( tempTexCoord.x, tempTexCoord.y );
						texCoordinate = currentVBO->insertTexCoord(texCoordVec2);
						VertexIndex VI( position, normal, texCoordinate );
						if( gameSkin != nullptr )
						{
							int numberOfBones = gameSkin->GetNumberOfBones( maxPosition );
							for( int boneIndex = 0; boneIndex < numberOfBones; ++boneIndex )
							{
								float boneWeight = gameSkin->GetWeight( maxPosition, boneIndex );
								IGameNode* bone = gameSkin->GetIGameBone( maxPosition, boneIndex );
								myFile << "Bone node ID: " << bone->GetNodeID() << "\n";
								int nodeIDForBone = m_boneIDToNodeID[ bone->GetNodeID() ];
								myFile << "Node ID: " << nodeIDForBone << "\n";
								VI.addBoneWeight( nodeIDForBone, boneWeight );

								/*for( auto boneIter = m_NodeList.begin(); boneIter != m_NodeList.end(); ++boneIter )
								{
									if( (*boneIter)->m_gameNode == bone )
									{
										myFile << "Found the bone!\n"; 
										
									}
								}*/
								
							}
							VI.topBoneWeights();
						}

						int vertIndex = currentVBO->insertVertex( VI );
						currentIBO->addIndex( vertIndex );

					}

				}
				
				BinaryFile.saveTriangleMesh( currentBatch, myFile );
			}
		}

	}
	myFile.close();

	for( int nodeNumber = 0; nodeNumber < nodeCount; ++nodeNumber)
	{
		IGameNode* gameNode = gameScene->GetTopLevelNode( nodeNumber );
		if( gameNode != nullptr )
		{
			tearDown( gameNode );
		}
		
	}

	BinaryFile.close();
	return TRUE;

	//return FALSE;
}