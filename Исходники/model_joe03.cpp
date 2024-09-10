///fix invalid normals (my own fault, i suspect.  the DOF converter i wrote may have flipped Y & Z normals)
static bool NeedsNormalSwap(JOEObject & Object)
{
	bool need_normal_flip = false;
	for (int f = 0; f < Object.info.num_frames; f++)
	{
		int normal_flip_count = 0;
		for (int i = 0; i < Object.info.num_faces; i++)
		{
			MATHVECTOR <float,3> tri[3];
			MATHVECTOR <float,3> norms[3];
			for (unsigned int v = 0; v < 3; v++)
			{
				assert(Object.frames[f].faces[i].vertexIndex[v] < Object.frames[f].num_verts);
				assert(Object.frames[f].faces[i].normalIndex[v] < Object.frames[f].num_normals);
				tri[v].Set(Object.frames[f].verts[Object.frames[f].faces[i].vertexIndex[v]].vertex);
				norms[v].Set(Object.frames[f].normals[Object.frames[f].faces[i].normalIndex[v]].vertex);
			}
			MATHVECTOR <float,3> norm;
			for (unsigned int v = 0; v < 3; v++)
				norm = norm + norms[v];
			MATHVECTOR <float,3> tnorm = (tri[2] - tri[0]).cross(tri[1] - tri[0]);
			if (tnorm.Magnitude() > 0.0001 && norm.Magnitude() > 0.0001)
			{
				norm = norm.Normalize();
				tnorm = tnorm.Normalize();
				if (norm.dot(tnorm) < 0.5 && norm.dot(tnorm) > -0.5)
				{
					normal_flip_count++;
					//std::cout << norm.dot(tnorm) << std::endl;
					//std::cout << norm << " -- " << tnorm << std::endl;
				}
			}
		}

		if (normal_flip_count > Object.info.num_faces/4)
			need_normal_flip = true;
	}
	return need_normal_flip;
}