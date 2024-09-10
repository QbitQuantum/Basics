void create_vertex_buffers_from_model(LLModel* model, std::vector<LLPointer <LLVertexBuffer> >& vertex_buffers)
{
#if 0 //VECTORIZE THIS ?
	vertex_buffers.clear();
	
	for (S32 i = 0; i < model->getNumVolumeFaces(); ++i)
	{
		const LLVolumeFace &vf = model->getVolumeFace(i);
		U32 num_vertices = vf.mNumVertices;
		U32 num_indices = vf.mNumIndices;

		if (!num_vertices || ! num_indices)
		{
			continue;
		}

		LLVertexBuffer* vb =
			new LLVertexBuffer(LLVertexBuffer::MAP_VERTEX | LLVertexBuffer::MAP_NORMAL | LLVertexBuffer::MAP_TEXCOORD0, 0);
		
		vb->allocateBuffer(num_vertices, num_indices, TRUE);

		LLStrider<LLVector3> vertex_strider;
		LLStrider<LLVector3> normal_strider;
		LLStrider<LLVector2> tc_strider;
		LLStrider<U16> index_strider;

		vb->getVertexStrider(vertex_strider);
		vb->getNormalStrider(normal_strider);
		vb->getTexCoord0Strider(tc_strider);

		vb->getIndexStrider(index_strider);

		// build vertices and normals
		for (U32 i = 0; (S32)i < num_vertices; i++)
		{
			*(vertex_strider++) = vf.mVertices[i].mPosition;
			*(tc_strider++) = vf.mVertices[i].mTexCoord;
			LLVector3 normal = vf.mVertices[i].mNormal;
			normal.normalize();
			*(normal_strider++) = normal;
		}

		// build indices
		for (U32 i = 0; i < num_indices; i++)
		{
			*(index_strider++) = vf.mIndices[i];
		}


		vertex_buffers.push_back(vb);
	}
#endif
}