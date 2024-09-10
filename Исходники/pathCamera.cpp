void PathCamera::calculateAim(Point3F currentPosition)
{
	if(mAimTarget == -1 && mAimOffset == Point3F(0.f, 0.f, 0.f))	
	{
		calculateLookDirMat(mLookDirVector);
		return;
	}

	Point3F dir = mAimOffset;

	if(mAimTarget > 0)
	{	
		SceneObject* obj = NULL;
		Sim::findObject(mAimTarget, obj);
		if(obj)
			dir += obj->getPosition();
	}

	dir = dir - currentPosition;
	dir.normalize();
	calculateLookDirMat(dir);
}