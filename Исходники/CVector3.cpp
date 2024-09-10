// Return distance from one point to another - non-member version
TFloat32 Distance
(
	const CVector3& p1,
	const CVector3& p2
)
{
	TFloat32 distX = p1.x - p2.x;
	TFloat32 distY = p1.y - p2.y;
	TFloat32 distZ = p1.z - p2.z;
	return Sqrt( distX*distX + distY*distY + distZ*distZ );
}