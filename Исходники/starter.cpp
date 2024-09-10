/*
	doIdle - The idle-function that can be used to update the screen
*/
void doIdle()
{
	if (g_bRayTrace)
	{
		g_ScreenBuffer[g_Y][g_X] = g_RayTrace.CalculatePixel (g_X, g_Y);

		//printf ("Drawing %d, %d\n", g_X, g_Y);

		// Move to the next pixel
		g_X++;
		if (g_X >= Scene::WINDOW_WIDTH)
		{
			// Move to the next row
			g_X = 0;
			g_Y++;

			/* You can uncomment the next line 
				to see the raytrace "in-action" */
			glutPostRedisplay();
		}

		// Check for the end of the screen
		if (g_Y >= Scene::WINDOW_HEIGHT)
		{
			g_bRayTrace = false;
			glutPostRedisplay ();

			if (recording)
			{
				// ** Save frame
				std::string fileName ("frame_" + std::to_string(frame) +".jpg");
				char *file = const_cast<char*>(fileName.c_str());
				saveScreenshot(file);
				++frame;

				// ** Move to the next position
				Vector dir = g_RayTrace.m_Scene.m_Camera.GetTarget() - g_RayTrace.m_Scene.m_Camera.GetPosition();
				float tar_posDist = dir.Magnitude();
				dir.Normalize();
				Vector right = dir.Cross(g_RayTrace.m_Scene.m_Camera.GetUp());
				Vector tempVec;
				float turnSpeed = 0.01f;
				// - Turn Left -
				// Simulate a Left-Turn by finding a position just a little to the left of the direction
				tempVec = dir - right * turnSpeed;
				tempVec.Normalize();
				g_RayTrace.m_Scene.m_Camera.SetTarget(g_RayTrace.m_Scene.m_Camera.GetPosition() + tempVec * tar_posDist);

				// ** Start rendering again
				g_X = 0;
				g_Y = 0;
				g_bRayTrace = true;

				// ** Finish check
				if (frame > 650)
				{
					recording = false;
					g_bRayTrace = false;
				}
			}
		}
	}
	else
	{
		glutPostRedisplay ();
	}
}