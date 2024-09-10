MMatrix  sgLockAngleMatrix::getsgLockAngleMatrix( const MMatrix& inputMatrix, unsigned char axis, double angle )
{
	MStatus status;

	angle = angle/180 * PI;
	bool minusAxis = false;

	if( axis > 2 )
	{
		minusAxis = true;
		axis -= 3;
	}
	unsigned int upAxis = ( axis+1 ) % 3;
	unsigned int crossAxis = ( axis+2 ) % 3;

	MVector vDefault( 0,0,0 );
	vDefault[ axis ] = 1;
	MVector vAxis = inputMatrix[ axis ];
	vAxis.normalize();

	double dotValue = vAxis * vDefault;
	double cuAngle = acos( dotValue );

	if( angle > cuAngle ) angle = cuAngle;

	MVector vCross = vDefault ^ vAxis;
	MVector vUp    = vCross ^ vDefault;

	vUp.normalize();
	MVector vEdit = sin( angle ) * vUp + cos( angle ) * vDefault;

	if( minusAxis ) vEdit *= -1;

	MVector vUpEdit;
	vUpEdit[ axis ] = -vEdit[ upAxis ];
	vUpEdit[ upAxis ] = vEdit[ axis ];
	vUpEdit[ crossAxis ] = 0;

	MVector vCrossEdit = vEdit ^ vUpEdit;
	vUpEdit = vCrossEdit ^ vEdit;

	vEdit.normalize();
	vUpEdit.normalize();
	vCrossEdit.normalize();

	MMatrix returnMtx;

	returnMtx( axis, 0 ) = vEdit.x;
	returnMtx( axis, 1 ) = vEdit.y;
	returnMtx( axis, 2 ) = vEdit.z;
	returnMtx( upAxis, 0 ) = vUpEdit.x;
	returnMtx( upAxis, 1 ) = vUpEdit.y;
	returnMtx( upAxis, 2 ) = vUpEdit.z;
	returnMtx( crossAxis, 0 ) = vCrossEdit.x;
	returnMtx( crossAxis, 1 ) = vCrossEdit.y;
	returnMtx( crossAxis, 2 ) = vCrossEdit.z;

	return returnMtx;
}