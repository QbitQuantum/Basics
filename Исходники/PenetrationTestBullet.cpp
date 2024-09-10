static void MotionCallback(int x, int y)
{
	int dx = mx - x;
	int dy = my - y;
	
	Dir = Dir.normalize();
	N = Dir.cross(btVector3(0,1,0));

	NxQuat qx(NxPiF32 * dx * 20/ 180.0f, btVector3(0,1,0));
	qx.rotate(Dir);
	NxQuat qy(NxPiF32 * dy * 20/ 180.0f, N);
	qy.rotate(Dir);

	mx = x;
	my = y;
}