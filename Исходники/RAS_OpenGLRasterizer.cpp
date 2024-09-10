bool RAS_OpenGLRasterizer::RayHit(struct KX_ClientObjectInfo *client, KX_RayCast *result, float *oglmatrix)
{
	if (result->m_hitMesh) {

		RAS_Polygon* poly = result->m_hitMesh->GetPolygon(result->m_hitPolygon);
		if (!poly->IsVisible())
			return false;

		MT_Vector3 resultnormal(result->m_hitNormal);
		MT_Vector3 left(oglmatrix[0],oglmatrix[1],oglmatrix[2]);
		MT_Vector3 dir = -(left.cross(resultnormal)).safe_normalized();
		left = (dir.cross(resultnormal)).safe_normalized();
		// for the up vector, we take the 'resultnormal' returned by the physics

		float maat[16] = {left[0],         left[1],         left[2],         0,
			               dir[0],          dir[1],          dir[2],          0,
		                  resultnormal[0], resultnormal[1], resultnormal[2], 0,
		                  0,               0,               0,               1};

		glTranslatef(oglmatrix[12],oglmatrix[13],oglmatrix[14]);
		//glMultMatrixd(oglmatrix);
		glMultMatrixf(maat);
		return true;
	}
	else {
		return false;
	}
}