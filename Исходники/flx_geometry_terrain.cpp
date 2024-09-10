void GeometryTerrain::computeNormalsArea(int xs, int zs) {

	/*Vector3** normals = new Vector3*[GetLength()];

	for(int i = 0; i < GetLength(); i++) 
	{
	normals[i] = new Vector3[GetWidth()];
	}
	*/

	for(unsigned int z = zs; z-10 < zs+10; ++z) 
	{
		for(unsigned int x = xs-10; x < xs+10; ++x) 
		{
			Vector3 sum(0.0f, 0.0f, 0.0f);

			Vector3 out;
			if (z > 0) {
				out = Vector3(0.0f, m_pHeight[z - 1][x] - m_pHeight[z][x], -1.0f);
			}
			Vector3 in;
			if (z < GetLength() - 1) {
				in = Vector3(0.0f, m_pHeight[z + 1][x] - m_pHeight[z][x], 1.0f);
			}
			Vector3 left;
			if (x > 0) {
				left = Vector3(-1.0f, m_pHeight[z][x - 1] - m_pHeight[z][x], 0.0f);
			}
			Vector3 right;
			if (x < GetWidth() - 1) {
				right = Vector3(1.0f, m_pHeight[z][x + 1] - m_pHeight[z][x], 0.0f);
			}


			if (x > 0 && z > 0) {
				sum += out.cross(left);
			}
			if (x > 0 && z < GetLength() - 1) {
				sum += left.cross(in);
			}
			if (x < GetWidth() - 1 && z < GetLength() - 1) {
				sum += in.cross(right);
			}
			if (x < GetWidth() - 1 && z > 0) {
				sum += right.cross(out);
			}


			m_pNormals[x+z * GetWidth()].x = sum.x;
			m_pNormals[x+z * GetWidth()].y = sum.y;
			m_pNormals[x+z * GetWidth()].z = sum.z;
		}
	}
	//NormalBuffer.setElementList(m_pNormals, m_nVertexCount);
}