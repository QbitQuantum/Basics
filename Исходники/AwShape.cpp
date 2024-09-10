//----------------------------------------------------------------------------
AwTextureTarget *AwShape::processAwesomiumHit (const Point3F &start, const Point3F &end)
{
	if (!mTextureTarget)
	{
		return NULL;
	}

	Point3F localStart, localEnd;
	MatrixF mat = getTransform();
	mat.scale (Point3F (getScale ()));
	mat.inverse ();

	mat.mulP (start, &localStart);
	mat.mulP (end, &localEnd);

	RayInfo info;
	info.generateTexCoord = true;
	if (!mShapeInstance || !mShapeInstance->castRayOpcode (0, localStart, localEnd, &info))
	{
		return NULL;
	}

	if (info.texCoord.x != -1 && info.texCoord.y != -1 && info.material == mMatInstance)
	{
		Point2I pnt (info.texCoord.x * mTextureTarget->getResolution ().x, info.texCoord.y * mTextureTarget->getResolution ().y);
		
		AwManager::sCursor->setPosition (pnt);

		if (mIsMouseDown)
		{
			mTextureTarget->injectMouseDown ();
		}
		else
		{
			mTextureTarget->injectMouseUp ();
		}

		return mTextureTarget;
	}
	return NULL;
}