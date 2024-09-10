/**Populates qMatrixes based on the planes surrounding each vertex
   in the mesh m - Ankit*/
void QuadricErrorSimplification::generateQMatrices(STTriangleMesh* mesh){
	STVector3 i, j, k;
	STVector3 n;
	float d = 0;
	float area = 0;
	STFace* f;
	STVertex* vert;
	
	for (size_t v = 0; v < mesh->mVertices.size(); ++v)
	{
	    qMatrixes.push_back(new STMatrix4());
	}
	for (size_t v = 0; v < mesh->mVertices.size(); ++v)
	{
	        //memset(m_vertices[v].m_Q, 0, 10 * sizeof(Float));
	        vert = mesh->mVertices[v];
		//find all the faces that contain this vertex
		for (size_t itT = 0; itT < mesh->mFaces.size(); ++itT)
		{
		        f = mesh->mFaces[itT];
			if (vertexEquals(f->v[0], vert) || vertexEquals(f->v[1], vert) || vertexEquals(f->v[2], vert)){
			  i = vertex2Vector3(f->v[0]);
			  j = vertex2Vector3(f->v[1]);
			  k = vertex2Vector3(f->v[2]);
			  n = STVector3::Cross(j - i, k - i);
			  area = n.Length();
			  n.Normalize();
			  d = -(STVector3::Dot(vertex2Vector3(mesh->mVertices[v]), n));
			  
			  qMatrixes[v]->table[0][0] += area * (n.x * n.x);
			  qMatrixes[v]->table[0][1] += area * (n.x * n.y);
			  qMatrixes[v]->table[0][2] += area * (n.x * n.z);
			  qMatrixes[v]->table[0][3] += area * (n.x * d);
			  qMatrixes[v]->table[1][0] += area * (n.y * n.x);
			  qMatrixes[v]->table[1][1] += area * (n.y * n.y);
			  qMatrixes[v]->table[1][2] += area * (n.y * n.z);
			  qMatrixes[v]->table[1][3] += area * (n.y * d);
			  qMatrixes[v]->table[2][0] += area * (n.z * n.x);
			  qMatrixes[v]->table[2][1] += area * (n.z * n.y);
			  qMatrixes[v]->table[2][2] += area * (n.z * n.z);
			  qMatrixes[v]->table[2][3] += area * (n.z * d);
			  qMatrixes[v]->table[3][0] += area * (d * n.x);
			  qMatrixes[v]->table[3][1] += area * (d * n.y);
			  qMatrixes[v]->table[3][2] += area * (d * n.z);
			  qMatrixes[v]->table[3][3] += area * (d * d);
			}
		}
	}
}