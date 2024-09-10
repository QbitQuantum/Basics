MMatrix retargetLocator::getAimMatrix( MMatrix inputAimMatrix )
{
	MVector aimVector( inputAimMatrix(3,0), inputAimMatrix(3,1), inputAimMatrix(3,2) );
	aimVector -= discOffset;

	MVector upVector( -aimVector.y - aimVector.z, aimVector.x, aimVector.x );
	MVector otherVector = aimVector^upVector;
	upVector = otherVector^aimVector;

	MVector normalizeAim = aimVector.normal();
	upVector.normalize();
	otherVector.normalize();

	aimVector += discOffset;
	double buildMatrix[4][4] = { normalizeAim.x, normalizeAim.y, normalizeAim.z, 0,
	                             upVector.x,  upVector.y,  upVector.z,  0,
	                             otherVector.x, otherVector.y, otherVector.z, 0,
								 aimVector.x, aimVector.y, aimVector.z, 1 };
	return MMatrix( buildMatrix );
}