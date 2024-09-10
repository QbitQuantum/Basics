static void KeyboardCallback(unsigned char key, int x, int y)
	{
	switch (key)
		{
		case 27:	exit(0); break;
		case '1':			CreateCube(NxVec3(-40.0f, 60.0f, -18.0f)); break;
		case '2':			CreateCube(NxVec3(0.0f, 60.0f, -18.0f)); break;
		case '3':			CreateCube(NxVec3(40.0f, 60.0f, -18.0f)); break;

		case '4':			CreateCube(NxVec3(-40.0f, 60.0f, 40.0f)); break;
		case '5':			CreateCube(NxVec3(0.0f, 60.0f, 40.0f)); break;
		case '6':			CreateCube(NxVec3(40.0f, 60.0f, 40.0f)); break;

		case 'p':			gPause = !gPause; break;
		case 101: 			Eye += Dir * 2.0f; break;
		case 103: 			Eye -= Dir * 2.0f; break;
		case 100: 			Eye -= N * 2.0f; break;
		case 102: 			Eye += N * 2.0f; break;
		case 'w':
			{
			NxVec3 t = Eye;
			NxVec3 Vel = Dir;
			Vel.normalize();
			Vel*=100.0f;
			CreateCube(t, &Vel);
			}
			break;
		}
	
	}