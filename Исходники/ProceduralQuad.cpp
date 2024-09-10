void ProceduralQuad::GetNormals(void * data_start, unsigned int byte_stride)
{
	Eigen::Vector3f normal = (corners[1]-corners[0]).cross(corners[2]-corners[0]);
	normal.normalize();

	float * dest = (float *) data_start;

	unsigned int vertex_count = GetVertexCount();
	for (unsigned int i = 0; i < vertex_count; ++i)
	{
		dest[0] = normal[0];
		dest[1] = normal[1];
		dest[2] = normal[2];
		dest = (float *) ((char *) dest + byte_stride);
	}
}