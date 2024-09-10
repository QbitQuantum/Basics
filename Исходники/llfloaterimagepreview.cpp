void LLImagePreviewSculpted::setPreviewTarget(LLImageRaw* imagep, F32 distance)
{ 
	mCameraDistance = distance;
	mCameraZoom = 1.f;
	mCameraPitch = 0.f;
	mCameraYaw = 0.f;
	mCameraOffset.clearVec();

	if (imagep)
	{
		mVolume->sculpt(imagep->getWidth(), imagep->getHeight(), imagep->getComponents(), imagep->getData(), 0);
	}

	const LLVolumeFace &vf = mVolume->getVolumeFace(0);
	U32 num_indices = vf.mIndices.size();
	U32 num_vertices = vf.mVertices.size();

	mVertexBuffer = new LLVertexBuffer(LLVertexBuffer::MAP_VERTEX | LLVertexBuffer::MAP_NORMAL, 0);
	mVertexBuffer->allocateBuffer(num_vertices, num_indices, TRUE);

	LLStrider<LLVector3> vertex_strider;
	LLStrider<LLVector3> normal_strider;
	LLStrider<U16> index_strider;

	mVertexBuffer->getVertexStrider(vertex_strider);
	mVertexBuffer->getNormalStrider(normal_strider);
	mVertexBuffer->getIndexStrider(index_strider);

	// build vertices and normals
	for (U32 i = 0; (S32)i < num_vertices; i++)
	{
		*(vertex_strider++) = vf.mVertices[i].mPosition;
		LLVector3 normal = vf.mVertices[i].mNormal;
		normal.normalize();
		*(normal_strider++) = normal;
	}

	// build indices
	for (U16 i = 0; i < num_indices; i++)
	{
		*(index_strider++) = vf.mIndices[i];
	}
}