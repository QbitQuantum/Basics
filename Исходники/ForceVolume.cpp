//given a capsule specified with a transform, two points, and a radius, this will approximate how much is submerged
//and distribute that force to the appropriate points on the capsule
static bool ApplyCapsuleBuoyancy(const LTVector& vPt1, const LTVector& vPt2, float fLength, float fRadius, 
								 const LTPlane& WSPlane, float& fVolume, LTVector& vApplyAt,
								 float& fSurfaceArea)
{
	//convert the capsule to an OBB and apply it
	
	//determine information about the main axis
	LTVector vMainAxis = vPt2 - vPt1;
	LTASSERT( fLength > 0.0f, "Invalid capsule length." );
	LTVector vUnitAxis = vMainAxis / fLength;

	//we can now build up a rotation given the plane normal and the axis to build our transform
	LTVector vUp = WSPlane.Normal();
	if(fabsf(vUp.Dot(vUnitAxis)) > 0.99f)
	{
		//too close to use, built an arbitrary orthonormal
		vUp = vUnitAxis.BuildOrthonormal();
	}

	LTMatrix3x4 mTemp;
	LTVector vRight = vUnitAxis.Cross(vUp);
	vRight.Normalize( );
	LTVector vTrueUp = vRight.Cross( vUnitAxis );
	mTemp.SetBasisVectors(vRight, vTrueUp, vUnitAxis);

	LTRotation rRot;
	rRot.ConvertFromMatrix(mTemp);

	//now we can form our transform
	LTRigidTransform tTransform((vPt1 + vPt2) * 0.5f, rRot);
	LTVector vHalfDims(fRadius, fRadius, fLength * 0.5f + fRadius);

	return ApplyOBBBuoyancy(tTransform, vHalfDims, WSPlane, fVolume, vApplyAt, fSurfaceArea);
}