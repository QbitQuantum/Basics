//-----------------------------------------------------------------------------
// Copies the texture coordinate system from pFrom into pTo. Then it rotates 
// the texture around the edge until it's as close to pTo's normal as possible.
//-----------------------------------------------------------------------------
void CFaceEditMaterialPage::CopyTCoordSystem( const CMapFace *pFrom, CMapFace *pTo )
{
	Vector		axis[2], vEdge, vEdgePt, vOrigin;
	Vector		vFromPt, vNextFromPt;
	Vector		vToPt, vPrevToPt;
	Vector		vTestTextureNormal, vTextureNormal;
	VMatrix		mEdgeRotation, mOriginRotation, mTranslation;
	float		fAngle, fDot;
	bool		bRotate;
	float		fShift[2];
	Vector		vProjTexNormal;
	Vector		vProjPolyNormal;

	// The edge vector lies on both planes.
	vEdge = pFrom->plane.normal.Cross(pTo->plane.normal);
	VectorNormalize( vEdge );

	// To find a point on the plane, we make a plane from the edge vector and find the intersection
	// between the three planes (without the third plane, there are an infinite number of solutions).
	if( PlaneIntersection( VPlane(pFrom->plane.normal, pFrom->plane.dist),
		                   VPlane(pTo->plane.normal, pTo->plane.dist),
		                   VPlane(vEdge, 0.0f), vEdgePt ) )
	{
		bRotate = true;
	}
	else
	{
		// Ok, in this case, the planes are parallel so we don't need to rotate around the edge anyway!
		bRotate = false;
	}

	// Copy the texture coordinate system.
	axis[0] = pFrom->texture.UAxis.AsVector3D();
	axis[1] = pFrom->texture.VAxis.AsVector3D();
	fShift[0] = pFrom->texture.UAxis[3];
	fShift[1] = pFrom->texture.VAxis[3];
	vOrigin = axis[0]*fShift[0]*pFrom->texture.scale[0] + axis[1]*fShift[1]*pFrom->texture.scale[1];
	
	vTextureNormal = axis[0].Cross(axis[1]);
	VectorNormalize(vTextureNormal);
	if(bRotate)
	{
		// Project texture normal and poly normal into the plane of rotation
		// to get the angle between them.
		vProjTexNormal = vTextureNormal - vEdge * vEdge.Dot(vTextureNormal);
		vProjPolyNormal = pTo->plane.normal - vEdge * vEdge.Dot(pTo->plane.normal);

		VectorNormalize( vProjTexNormal );
		VectorNormalize( vProjPolyNormal );

		fDot = vProjTexNormal.Dot(vProjPolyNormal);
		fAngle = (float)(acos(fDot) * (180.0f / M_PI));
		if(fDot < 0.0f)
			fAngle = 180.0f - fAngle;

		// Ok, rotate them for the final values.
		mEdgeRotation = SetupMatrixAxisRot(vEdge, fAngle);
		axis[0] = mEdgeRotation.ApplyRotation(axis[0]);
		axis[1] = mEdgeRotation.ApplyRotation(axis[1]);

		// Origin needs translation and rotation to rotate around the edge.
		mTranslation = SetupMatrixTranslation(vEdgePt);
		mOriginRotation = ~mTranslation * mEdgeRotation * mTranslation;
		vOrigin = mOriginRotation * vOrigin;
	}

	pTo->texture.UAxis.AsVector3D() = axis[0];
	pTo->texture.VAxis.AsVector3D() = axis[1];

	pTo->texture.UAxis[3] = axis[0].Dot(vOrigin) / pFrom->texture.scale[0];
	pTo->texture.VAxis[3] = axis[1].Dot(vOrigin) / pFrom->texture.scale[1];
	pTo->NormalizeTextureShifts();

	pTo->texture.scale[0] = pFrom->texture.scale[0];
	pTo->texture.scale[1] = pFrom->texture.scale[1];

	// rotate is only for UI purposes, it doesn't actually do anything.
	pTo->texture.rotate = 0.0f;

	pTo->CalcTextureCoords();
}