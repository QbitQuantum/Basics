/*! \param lookDir
 *  \param plump
 *  \return an upVector
 */
SbVec3f kCamera::calcPerfectUpVector(const SbVec3f lookDir, const SbVec3f plump)
{
	return lookDir.cross(plump.cross(lookDir));
}