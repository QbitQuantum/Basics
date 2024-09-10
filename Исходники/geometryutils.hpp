/* 
 Given a point, camera position and direction, plus a threshold, determine
 if the point is visible from the camera.
 */
bool checkVisibility(const Point3<T>& p, const Point3<T>& camPos, const Vector3<T>& camDir, float thres)
{
	Vector3<T> camToP(camPos, p);
	camToP.normalize();

	return (-camDir.dot(camToP) > thres);
}