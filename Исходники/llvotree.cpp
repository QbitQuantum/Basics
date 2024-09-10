void LLVOTree::appendMesh(LLStrider<LLVector3>& vertices, 
						 LLStrider<LLVector3>& normals, 
						 LLStrider<LLVector2>& tex_coords, 
						 LLStrider<U16>& indices,
						 U16& cur_idx,
						 LLMatrix4& matrix,
						 LLMatrix4& norm_mat,
						 S32 vert_start,
						 S32 vert_count,
						 S32 index_count,
						 S32 index_offset)
{
	LLStrider<LLVector3> v;
	LLStrider<LLVector3> n;
	LLStrider<LLVector2> t;
	LLStrider<U16> idx;

	mReferenceBuffer->getVertexStrider(v);
	mReferenceBuffer->getNormalStrider(n);
	mReferenceBuffer->getTexCoord0Strider(t);
	mReferenceBuffer->getIndexStrider(idx);
	
	//copy/transform vertices into mesh - check
	for (S32 i = 0; i < vert_count; i++)
	{ 
		U16 index = vert_start + i;
		*vertices++ = v[index] * matrix;
		LLVector3 norm = n[index] * norm_mat;
		norm.normalize();
		*normals++ = norm;
		*tex_coords++ = t[index];
	}

	//copy offset indices into mesh - check
	for (S32 i = 0; i < index_count; i++)
	{
		U16 index = index_offset + i;
		if (idx[index] >= vert_start + vert_count ||
			idx[index] < vert_start)
		{
			llerrs << "WTF?" << llendl;
		}
		*indices++ = idx[index]-vert_start+cur_idx;
	}

	//increment index offset - check
	cur_idx += vert_count;
}