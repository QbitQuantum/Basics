//-----------------------------------------------------------------------
bool gkObjectManager::checkSelected( uint8 type, f32 size, bool draging )
{
	// first of all, get the 3 axis end point at screenspace [8/25/2011 Kaiming-Desktop]
	Vec2 vCursor = GetIEditor()->getMainViewport()->getCursorOnClientScreen();
	Vec3 vAxis3D;
	Vec3 vCenter3D;

	Vec3 vCenterReal = ms_pCurrentPick->getWorldPosition();
	Vec3 vDirReal(0,0,0);

	vCenter3D = gEnv->pRenderer->ProjectScreenPos( vCenterReal );

	switch(type)
	{
	case GKSTUDIO_AXIS_X:
		vDirReal = ms_pCurrentPick->getOrientation().GetColumn0();
		break;
	case GKSTUDIO_AXIS_Y:
		vDirReal = ms_pCurrentPick->getOrientation().GetColumn1();
		break;
	case GKSTUDIO_AXIS_Z:
		vDirReal = ms_pCurrentPick->getOrientation().GetColumn2();
		break;
	}

	vAxis3D = gEnv->pRenderer->ProjectScreenPos( ms_pCurrentPick->getWorldPosition() + size * vDirReal );

	// make two 2D vector
	Vec2 vCenter(vCenter3D.x, vCenter3D.y);
	Vec2 vAxis(vAxis3D.x, vAxis3D.y);

	Vec2 vPoint = vCursor - vCenter;
	Vec2 vAxisPoint = vAxis - vCenter;

	ms_dragInvertX = vAxisPoint.x > 0 ? 1 : -1;
	ms_dragInvertY = vAxisPoint.y > 0 ? 1 : -1;

	// judge this
	if (vPoint.GetLength() - vAxisPoint.GetLength() < size + 2.0f)
	{
		vPoint.Normalize();
		vAxisPoint.Normalize();

		if (vPoint.Dot(vAxisPoint) > 0.95f)
			return true;
	}

	return false;
}