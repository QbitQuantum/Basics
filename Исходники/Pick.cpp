bool FrustumPickVisitor::AddHitTriangle(const Vector3& v0,const Vector3& v1,const Vector3& v2)
{
	float32_t dot = 0.f;
	Vector3 normal ( (v2 - v1).Cross (v1 - v0) );

	if (m_Camera->GetShadingMode() != ShadingMode::Wireframe && m_Camera->IsBackFaceCulling())
	{
		Vector3 cameraDir;
		m_Camera->GetDirection (cameraDir);
		m_CurrentInverseWorldTransform.TransformNormal (cameraDir);
		dot = normal.Dot (cameraDir);
	}

	if ( dot >= 0.f )
	{
		// allocate a hit
		PickHit* hit = AddHit();

		// our intersection point is center of the triangle (HACK)
		Vector3 intersection ( ( v0 + v1 + v2 ) / 3.f );
		// transform values into world space
		m_CurrentWorldTransform.TransformVertex(intersection);

		// set intersection in world space (we use FLT_MAX for the distance since the distance is spacial)
		if (!HasFlags(PickFlags::IgnoreIntersection))
		{
			hit->SetIntersection( intersection );
		}

		return true;
	}

	return false;
}