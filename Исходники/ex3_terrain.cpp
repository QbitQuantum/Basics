void MouseMotion(int x, int y )
{
	if(g_isButtonDown[0] || g_isButtonDown[2])
	{
		int dx = g_last_x - x;
		int dy = g_last_y - y;

		g_CameraForward.normalize();
		g_CameraRight.cross(g_CameraForward, NxVec3(0,1,0));

		NxQuat qx(NxPiF32 * dx * 20/ 180.0f, NxVec3(0,1,0));
		qx.rotate(g_CameraForward);
		NxQuat qy(NxPiF32 * dy * 20/ 180.0f, g_CameraRight);
		qy.rotate(g_CameraForward);

		g_last_x = x;
		g_last_y = y;
	}

	if (g_isButtonDown[1])
	{
		float dt = 0.1f;

		if ((float) (x-g_last_x)>0)
		{
			g_CameraPos -= g_CameraRight*g_Speed*dt;
		}
		else if ((float) (x-g_last_x)<0)
		{
			g_CameraPos += g_CameraRight*g_Speed*dt;
		}

		if ((float) (y-g_last_y)>0)
		{
			g_CameraPos +=NxVec3(0.0f,1.0f,0.0f)*g_Speed*dt;
		}
		else if ((float) (y-g_last_y)<0)
		{
			g_CameraPos -=NxVec3(0.0f,1.0f,0.0f)*g_Speed*dt;
		}

		g_last_x = x;
		g_last_y = y;
	}
	glutPostRedisplay();
}