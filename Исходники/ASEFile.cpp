void AseFile::ComputeTangentBinormal()
{
	for(int i=0; i<this->objects.size(); i++)
	{
		if(!objects[i].numOfTexVerts || !objects[i].numOfFaces)continue;

		vec* faceTangent;
		zASE_Object *obj;
		obj = &objects[i];

		faceTangent = new vec[obj->numOfFaces];		if(faceTangent==NULL)return;
		obj->pTangent = new vec[obj->numOfVerts];	if(obj->pTangent==NULL)return;
		obj->pBinormal = new vec[obj->numOfVerts];	if(obj->pBinormal==NULL)return;

		for(int j=0; j<obj->numOfFaces; j++)
		{
			tangent( obj->pVerts[obj->pFaces[j].index[0]],
					 obj->pVerts[obj->pFaces[j].index[1]],
					 obj->pVerts[obj->pFaces[j].index[2]],
					 obj->pTexVerts[obj->pFaceCoord[j].index[0]],
					 obj->pTexVerts[obj->pFaceCoord[j].index[1]],
					 obj->pTexVerts[obj->pFaceCoord[j].index[2]],
					 faceTangent[j] );
		}

		for(j=0; j<obj->numOfVerts; j++)			// Go through all of the vertices
		{
			obj->pTangent[j].clear();
			for(int k=0; k<obj->numOfFaces; k++)	// Go through all of the triangles
			{										// Check if the vertex is shared by another face
				if( obj->pFaces[k].index[0]==j || 
					obj->pFaces[k].index[1]==j ||
					obj->pFaces[k].index[2]==j )
				{
					obj->pTangent[j] += faceTangent[k];
				}
			}
			obj->pTangent[j].Normalize();
			obj->pBinormal[j] = Normalize( CROSS( obj->pNormals[j], obj->pTangent[j] ));
		}
		if(faceTangent!=NULL)delete [] faceTangent;
	}
}