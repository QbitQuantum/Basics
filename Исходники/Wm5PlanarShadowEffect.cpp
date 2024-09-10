//----------------------------------------------------------------------------
bool PlanarShadowEffect::GetProjectionMatrix (int i, HMatrix& projection)
{
	// Compute the equation for the shadow plane in world coordinates.
	APoint vertex[3];
	mPlanes[i]->GetWorldTriangle(0, vertex);
	HPlane worldPlane(vertex[0], vertex[1], vertex[2]);

	// This is a conservative test to see whether a shadow should be cast.
	// This can cause incorrect results if the caster is large and intersects
	// the plane, but ordinarily we are not trying to cast shadows in such
	// situations.
	if (mShadowCaster->WorldBound.WhichSide(worldPlane) < 0)
	{
		// The shadow caster is on the far side of plane, so it cannot cast
		// a shadow.
		return false;
	}

	// Compute the projection matrix for the light source.
	Light* projector = mProjectors[i];
	AVector normal = worldPlane.GetNormal();
	if (projector->GetType() == Light::LT_DIRECTIONAL)
	{
		float NdD = normal.Dot(projector->DVector);
		if (NdD >= 0.0f)
		{
			// The projection must be onto the "positive side" of the plane.
			return false;
		}

		projection.MakeObliqueProjection(vertex[0], normal,
		                                 projector->DVector);
	}
	else if (projector->GetType() == Light::LT_POINT
	         ||  projector->GetType() == Light::LT_SPOT)
	{
		float NdE = projector->Position.Dot(normal);
		if (NdE <= 0.0f)
		{
			// The projection must be onto the "positive side" of the plane.
			return false;
		}

		projection.MakePerspectiveProjection(vertex[0], normal,
		                                     projector->Position);
	}
	else
	{
		assertion(false, "Light type not supported.\n");
		return false;
	}

	return true;
}