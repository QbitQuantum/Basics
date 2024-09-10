void ComputeNormals(Loader3ds *pt3ds) 
{ 
 int i,j,index; 
 int shared=0; 
	float	v1x=0.0,v1y=0.0,v1z=0.0, 
			v2x=0.0,v2y=0.0,v2z=0.0, 
			vnx=0.0,vny=0.0,vnz=0.0, 
			vp0x=0.0,vp0y=0.0,vp0z=0.0, 
			vp1x=0.0,vp1y=0.0,vp1z=0.0, 
			vp2x=0.0,vp2y=0.0,vp2z=0.0, 
			*pNormals=NULL, 
			*pTempNormals=NULL, 
			vSumx = 0.0,vSumy = 0.0,vSumz = 0.0;	 
 	Objects *cur_obj; 

	// If there are no objects, we can skip this part 
	if(pt3ds->NBobjects <= 0) 
		return; 
 
	// Go through each of the objects to calculate their normals 
	cur_obj = pt3ds->objects; 
	for(index = 0; index < pt3ds->NBobjects; index++) 
	{ 
		pNormals		= (float*)malloc(sizeof(float) *(3*cur_obj->NBFaces)); 
		pTempNormals	= (float*)malloc(sizeof(float) * (3*cur_obj->NBFaces)); 
		cur_obj->Normal = (float*)malloc(sizeof(float) * (3*cur_obj->NBvert)); 
 
 
		// Go though all of the faces of this object 
		for(i=0; i < cur_obj->NBFaces; i++) 
		  {
			vp0x=cur_obj->vert[0+3*cur_obj->Faces[i*3]]; 
			vp0y=cur_obj->vert[1+3*cur_obj->Faces[i*3]]; 
			vp0z=cur_obj->vert[2+3*cur_obj->Faces[i*3]]; 
 
			vp1x=cur_obj->vert[0+3*cur_obj->Faces[i*3+1]]; 
			vp1y=cur_obj->vert[1+3*cur_obj->Faces[i*3+1]]; 
			vp1z=cur_obj->vert[2+3*cur_obj->Faces[i*3+1]]; 
 
			vp2x=cur_obj->vert[0+3*cur_obj->Faces[i*3+2]]; 
			vp2y=cur_obj->vert[1+3*cur_obj->Faces[i*3+2]]; 
			vp2z=cur_obj->vert[2+3*cur_obj->Faces[i*3+2]]; 
  
			Vector(	vp0x,vp0y,vp0z, 
					vp2x,vp2y,vp2z, 
					&v1x,&v1y,&v1z);		// Get the vector of the polygon (we just need 2 sides for the normal) 
 
			Vector(	vp2x,vp2y,vp2z, 
					vp1x,vp1y,vp1z, 
					&v2x,&v2y,&v2z);		// Get a second vector of the polygon 
			 
			Cross(	v1x,v1y,v1z, 
					v2x,v2y,v2z, 
					&vnx,&vny,&vnz);		// Return the cross product of the 2 vectors (normalize vector, but not a unit vector) 
 
			pTempNormals[3*i] = vnx;					// Save the un-normalized normal for the vertex normals 
			pTempNormals[3*i+1] = vny;					// Save the un-normalized normal for the vertex normals 
			pTempNormals[3*i+2] = vnz;					// Save the un-normalized normal for the vertex normals 
 
			Normalize(&vnx,&vny,&vnz);				// Normalize the cross product to give us the polygons normal 
 
			pNormals[3*i] = vnx;						// Assign the normal to the list of normals 
			pNormals[3*i+1] = vny;						// Assign the normal to the list of normals 
			pNormals[3*i+2] = vnz;						// Assign the normal to the list of normals 
		} 
 
		//////////////// Now Get The Vertex Normals ///////////////// 
 
		vSumx = 0.0;vSumy = 0.0;vSumz = 0.0;		 
		shared=0; 
 
		for (i = 0; i < cur_obj->NBvert; i++)			// Go through all of the vertices 
		{ 
			for (j = 0; j < cur_obj->NBFaces; j++)	// Go through all of the triangles 
			{												// Check if the vertex is shared by another face 
				if (cur_obj->Faces[j*3]   == i ||  
					cur_obj->Faces[j*3+1] == i ||  
					cur_obj->Faces[j*3+2] == i) 
				{ 
					AddVector(	vSumx,vSumy,vSumz, 
								pTempNormals[j*3],pTempNormals[j*3+1],pTempNormals[j*3+2], 
								&vSumx,&vSumy,&vSumz);// Add the un-normalized normal of the shared face 
					shared++;								// Increase the number of shared triangles 
				} 
			}       
			 
			// Get the normal by dividing the sum by the shared.  We negate the shared so it has the normals pointing out. 
			 DivideVectorByScaler(	vSumx,vSumy,vSumz, 
									&(cur_obj->Normal[i*3]), 
									&(cur_obj->Normal[i*3+1]), 
									&(cur_obj->Normal[i*3+2]), 
									-(float)shared); 
 
			// Normalize the normal for the final vertex normal 
			Normalize(	&(cur_obj->Normal[i*3]), 
						&(cur_obj->Normal[i*3+1]), 
						&(cur_obj->Normal[i*3+2]));	 
 
			vSumx = 0.0;vSumy = 0.0;vSumz = 0.0;			// Reset the sum 
			shared = 0;										// Reset the shared 
		} 
		 
	if (pNormals) free(pNormals); 
	if (pTempNormals) free(pTempNormals); 
	cur_obj=cur_obj->next; 
	}//end for index 
} 