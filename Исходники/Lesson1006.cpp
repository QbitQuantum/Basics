void MotionCallback(int x, int y)
{
	int dx = mx - x;
	int dy = my - y;

	if (gMouseSphere) // Move the mouse sphere
	{
		NxVec3 pos;
		ViewUnProject(x,y, gMouseDepth, pos);
		gMouseSphere->setGlobalPosition(pos);
		gHitActor->wakeUp();
	}
	else if (gHitCloth) // Attach the cloth vertex
	{
		NxVec3 pos; 
		ViewUnProject(x,y, gMouseDepth, pos);
		gHitCloth->attachVertexToGlobalPosition(gHitClothVertex, pos);
	}
	else if (bLeftMouseButtonPressed) // Set camera
	{   
		gCameraForward.normalize();
		gCameraRight.cross(gCameraForward,NxVec3(0,1,0));

		NxQuat qx(NxPiF32 * dx * 20 / 180.0f, NxVec3(0,1,0));
		qx.rotate(gCameraForward);
		NxQuat qy(NxPiF32 * dy * 20 / 180.0f, gCameraRight);
		qy.rotate(gCameraForward);
	}

    mx = x;
    my = y;
}