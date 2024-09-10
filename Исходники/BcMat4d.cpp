//////////////////////////////////////////////////////////////////////////
// lookAt
void BcMat4d::lookAt( const BcVec3d& Position, const BcVec3d& LookAt, const BcVec3d& UpVec )
{
	const BcVec3d Front = ( Position - LookAt ).normal();
	const BcVec3d Side = Front.cross( UpVec ).normal();
	const BcVec3d Up = Side.cross( Front ).normal();

	BcMat4d RotMatrix( BcVec4d( Side.x(),		Up.x(),		-Front.x(),		0.0f ),
	                   BcVec4d( Side.y(),		Up.y(),		-Front.y(),		0.0f ),
	                   BcVec4d( Side.z(),		Up.z(),		-Front.z(),		0.0f ),
	                   BcVec4d( 0.0f,			0.0f,			0.0f,		1.0f ) );

	BcMat4d TransMatrix( BcVec4d( 1.0f,			0.0f,			0.0f,		0.0f ),
	                   BcVec4d( 0.0f,			1.0f,			0.0f,		0.0f ),
	                   BcVec4d( 0.0f,			0.0f,			1.0f,		0.0f ),
	                   BcVec4d( -Position.x(), -Position.y(), -Position.z(),  1.0f ) );

	(*this) = TransMatrix * RotMatrix;
}