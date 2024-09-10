void Joint::GetFrame(float frame, Vec3& position, Quat& rotation)
{
	if (positionKeys.size() > 0)
	{
		PositionKey prePosition, nextPosition;
		GetPositionKeyFramesAtFrame(frame, &prePosition, &nextPosition);
		if (prePosition.frame != nextPosition.frame)
		{
			float t = (float)(frame - prePosition.frame) / (nextPosition.frame - prePosition.frame);
			position = prePosition.position + (nextPosition.position - prePosition.position)*t;
		}
		else
		{
			position = prePosition.position;
		}
	}

	if (rotationKeys.size() > 0)
	{
		RotationKey preRotation, nextRotation;
		GetRotationKeyFramesAtFrame(frame, &preRotation, &nextRotation);
		if (preRotation.frame != nextRotation.frame)
		{
			float t = (frame - preRotation.frame) / (nextRotation.frame - preRotation.frame);
			rotation.Slerp(preRotation.rotation, nextRotation.rotation, t);
		}
		else
		{
			rotation = preRotation.rotation;
		}
	}
}