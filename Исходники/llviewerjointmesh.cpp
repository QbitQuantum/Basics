void LLViewerJointMesh::updateGeometry()
{
	if (!(mValid
		  && mMesh
		  && mFace
		  && mMesh->hasWeights()
		  && mFace->mVertexBuffer.notNull()
		  && LLShaderMgr::getVertexShaderLevel(LLShaderMgr::SHADER_AVATAR) == 0))
	{
		return;
	}
	
	uploadJointMatrices();

	LLStrider<LLVector3> o_vertices;
	LLStrider<LLVector3> o_normals;

	//get vertex and normal striders
	LLVertexBuffer *buffer = mFace->mVertexBuffer;
	buffer->getVertexStrider(o_vertices,  0);
	buffer->getNormalStrider(o_normals,   0);

	F32 last_weight = F32_MAX;
	LLMatrix4 gBlendMat;
	LLMatrix3 gBlendRotMat;

	const F32* weights = mMesh->getWeights();
	const LLVector3* coords = mMesh->getCoords();
	const LLVector3* normals = mMesh->getNormals();
	for (U32 index = 0; index < mMesh->getNumVertices(); index++)
	{
		U32 bidx = index + mMesh->mFaceVertexOffset;
		
		// blend by first matrix
		F32 w = weights[index]; 
		
		// Maybe we don't have to change gBlendMat.
		// Profiles of a single-avatar scene on a Mac show this to be a very
		// common case.  JC
		if (w == last_weight)
		{
			o_vertices[bidx] = coords[index] * gBlendMat;
			o_normals[bidx] = normals[index] * gBlendRotMat;
			continue;
		}
		
		last_weight = w;

		S32 joint = llfloor(w);
		w -= joint;
		
		// No lerp required in this case.
		if (w == 1.0f)
		{
			gBlendMat = gJointMat[joint+1];
			o_vertices[bidx] = coords[index] * gBlendMat;
			gBlendRotMat = gJointRot[joint+1];
			o_normals[bidx] = normals[index] * gBlendRotMat;
			continue;
		}
		
		// Try to keep all the accesses to the matrix data as close
		// together as possible.  This function is a hot spot on the
		// Mac. JC
		LLMatrix4 &m0 = gJointMat[joint+1];
		LLMatrix4 &m1 = gJointMat[joint+0];
		
		gBlendMat.mMatrix[VX][VX] = lerp(m1.mMatrix[VX][VX], m0.mMatrix[VX][VX], w);
		gBlendMat.mMatrix[VX][VY] = lerp(m1.mMatrix[VX][VY], m0.mMatrix[VX][VY], w);
		gBlendMat.mMatrix[VX][VZ] = lerp(m1.mMatrix[VX][VZ], m0.mMatrix[VX][VZ], w);

		gBlendMat.mMatrix[VY][VX] = lerp(m1.mMatrix[VY][VX], m0.mMatrix[VY][VX], w);
		gBlendMat.mMatrix[VY][VY] = lerp(m1.mMatrix[VY][VY], m0.mMatrix[VY][VY], w);
		gBlendMat.mMatrix[VY][VZ] = lerp(m1.mMatrix[VY][VZ], m0.mMatrix[VY][VZ], w);

		gBlendMat.mMatrix[VZ][VX] = lerp(m1.mMatrix[VZ][VX], m0.mMatrix[VZ][VX], w);
		gBlendMat.mMatrix[VZ][VY] = lerp(m1.mMatrix[VZ][VY], m0.mMatrix[VZ][VY], w);
		gBlendMat.mMatrix[VZ][VZ] = lerp(m1.mMatrix[VZ][VZ], m0.mMatrix[VZ][VZ], w);

		gBlendMat.mMatrix[VW][VX] = lerp(m1.mMatrix[VW][VX], m0.mMatrix[VW][VX], w);
		gBlendMat.mMatrix[VW][VY] = lerp(m1.mMatrix[VW][VY], m0.mMatrix[VW][VY], w);
		gBlendMat.mMatrix[VW][VZ] = lerp(m1.mMatrix[VW][VZ], m0.mMatrix[VW][VZ], w);

		o_vertices[bidx] = coords[index] * gBlendMat;
		
		LLMatrix3 &n0 = gJointRot[joint+1];
		LLMatrix3 &n1 = gJointRot[joint+0];
		
		gBlendRotMat.mMatrix[VX][VX] = lerp(n1.mMatrix[VX][VX], n0.mMatrix[VX][VX], w);
		gBlendRotMat.mMatrix[VX][VY] = lerp(n1.mMatrix[VX][VY], n0.mMatrix[VX][VY], w);
		gBlendRotMat.mMatrix[VX][VZ] = lerp(n1.mMatrix[VX][VZ], n0.mMatrix[VX][VZ], w);

		gBlendRotMat.mMatrix[VY][VX] = lerp(n1.mMatrix[VY][VX], n0.mMatrix[VY][VX], w);
		gBlendRotMat.mMatrix[VY][VY] = lerp(n1.mMatrix[VY][VY], n0.mMatrix[VY][VY], w);
		gBlendRotMat.mMatrix[VY][VZ] = lerp(n1.mMatrix[VY][VZ], n0.mMatrix[VY][VZ], w);

		gBlendRotMat.mMatrix[VZ][VX] = lerp(n1.mMatrix[VZ][VX], n0.mMatrix[VZ][VX], w);
		gBlendRotMat.mMatrix[VZ][VY] = lerp(n1.mMatrix[VZ][VY], n0.mMatrix[VZ][VY], w);
		gBlendRotMat.mMatrix[VZ][VZ] = lerp(n1.mMatrix[VZ][VZ], n0.mMatrix[VZ][VZ], w);
		
		o_normals[bidx] = normals[index] * gBlendRotMat;
	}
}