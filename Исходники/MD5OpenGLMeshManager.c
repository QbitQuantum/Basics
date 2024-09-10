/*
** updates the md5mesh of mesh according to the passed animation and the frame.
** updates geometry on host and opengl side according to the updated pose.
*/ 
static int MD5OpenGLMeshUpdatePoseWithAnimationFrame(
	MD5OpenGLMesh* mesh,
	const FxsMD5Animation* animation, 
	unsigned int frame
)
{
	int i = 0, j = 0, k = 0, l = 0;
	FxsMD5Mesh* md5mesh = mesh->md5mesh;
	FxsMD5SubMesh* md5submesh = NULL;
	FxsMD5Face* face = NULL;
	FxsMD5Vertex* vertex = NULL;
	FxsMD5Weight* weight = NULL;	
	FxsMD5Joint* joint = NULL;
	FxsVector3* vertPosition = NULL;
	FxsVector4 weightPosition;
	unsigned int* vertexIds = NULL;
	MD5OpenGLSubMesh* glsubmesh = NULL;
	int count = 0;	

	if (!FxsMD5MeshUpdatePoseWithAnimationFrame(mesh->md5mesh, animation, frame))
	{
		return 0;
	}

	mesh->min.x = FLT_MAX;
	mesh->min.y = FLT_MAX;
	mesh->min.z = FLT_MAX;
	mesh->max.x = FLT_MIN;
	mesh->max.y = FLT_MIN;
	mesh->max.z = FLT_MIN;

	/* for all submeshes of the md5mesh, let's update the host and opengl data
	** of the opengl submeshes geometry (positions ...)
	*/ 
	for (i = 0; i < md5mesh->numSubMeshes; i++) 
	{
		glsubmesh = &mesh->subMeshes[i]; 		
		md5submesh = &md5mesh->meshes[i];		
		count = 0;

		mesh->subMeshes[i].min.x = FLT_MAX;
		mesh->subMeshes[i].min.y = FLT_MAX;
		mesh->subMeshes[i].min.z = FLT_MAX;
		mesh->subMeshes[i].max.x = FLT_MIN;
		mesh->subMeshes[i].max.y = FLT_MIN;
		mesh->subMeshes[i].max.z = FLT_MIN;

		/* for each face in the md5submesh ... */
		for (j = 0; j < md5submesh->numFaces; j++) 
		{
			face = &md5submesh->faces[j];		
			vertexIds = &face->v1;
		
			/* ... update each vertex */
			for (k = 0; k < 3; k++)
			{
				vertex = &md5submesh->vertices[vertexIds[k]];

				/* make the current vertex position zero */
				vertPosition = &mesh->subMeshes[i].positionsHost[count];
				FxsVector3MakeZero(vertPosition);

				/* update the position of each vertex by interation over
				** each of its weights
				*/
				for (l = 0; l < vertex->numWeights; l++)
				{
					weight = &md5submesh->weights[vertex->weightId + l];	
					joint = &md5mesh->currentPose.joints[weight->jointId];		
					
					FxsMatrix4MultiplyVector3(
						&weightPosition, 
						&joint->transform,
						&weight->position
					);

					/* add up all weight positions to compute the final
					** vertex position.
					*/
					vertPosition->x += weight->value*weightPosition.x;
					vertPosition->y += weight->value*weightPosition.y;
					vertPosition->z += weight->value*weightPosition.z;					
				}	

				/* update the bounding box */
				mesh->subMeshes[i].min.x = fminf(
						mesh->subMeshes[i].min.x, vertPosition->x
					);

				mesh->subMeshes[i].min.y = fminf(
						mesh->subMeshes[i].min.y, vertPosition->y
					);

				mesh->subMeshes[i].min.z = fminf(
						mesh->subMeshes[i].min.z, vertPosition->z
					);
		
				mesh->subMeshes[i].max.x = fmaxf(
						mesh->subMeshes[i].max.x, vertPosition->x
					);

				mesh->subMeshes[i].max.y = fmaxf(
						mesh->subMeshes[i].max.y, vertPosition->y
					);

				mesh->subMeshes[i].max.z = fmaxf(
						mesh->subMeshes[i].max.z, vertPosition->z
					);

				count++;
			}
		}
		
		mesh->min.x = fminf(mesh->subMeshes[i].min.x, mesh->min.x);
		mesh->min.y = fminf(mesh->subMeshes[i].min.y, mesh->min.y);
		mesh->min.z = fminf(mesh->subMeshes[i].min.z, mesh->min.z);

		mesh->max.x = fmaxf(mesh->subMeshes[i].max.x, mesh->max.x);
		mesh->max.y = fmaxf(mesh->subMeshes[i].max.y, mesh->max.y);
		mesh->max.z = fmaxf(mesh->subMeshes[i].max.z, mesh->max.z);

		/* update the opengl data for the sub mesh */
		glBindBuffer(GL_ARRAY_BUFFER, mesh->subMeshes[i].positions);  
	
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
		 	sizeof(FxsVector3)*mesh->subMeshes[i].numPositions,
			mesh->subMeshes[i].positionsHost
		);
		
//		glGenVertexArrays(1, &(*glmesh)->subMeshes[i].vao);
//		glBindVertexArray((*glmesh)->subMeshes[i].vao);
//		glBindBuffer(GL_ARRAY_BUFFER, (*glmesh)->subMeshes[i].positions);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
		if (GL_NO_ERROR != glGetError()) 
		{
			sprintf(errMsg, "Warning: opengl failed. Could not update md5mesh");
			ERR_MSG(errMsg);	
			return 0;		    
		}	
	}
	
	return 1;
}