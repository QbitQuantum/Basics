// not 'static', because used in ExportPsa()
void CAnimTrack::GetBonePosition(float Frame, float NumFrames, bool Loop, CVec3 &DstPos, CQuat &DstQuat) const
{
	guard(CAnimTrack::GetBonePosition);

	// fast case: 1 frame only
	if (KeyTime.Num() == 1 || NumFrames == 1 || Frame == 0)
	{
		if (KeyPos.Num())  DstPos  = KeyPos[0];
		if (KeyQuat.Num()) DstQuat = KeyQuat[0];
		return;
	}

	// data for lerping
	int posX, rotX;			// index of previous frame
	int posY, rotY;			// index of next frame
	float posF, rotF;		// fraction between X and Y for lerping

	int NumTimeKeys = KeyTime.Num();
	int NumPosKeys  = KeyPos.Num();
	int NumRotKeys  = KeyQuat.Num();

	if (NumTimeKeys)
	{
		// here: KeyPos and KeyQuat sizes either equals to 1 or equals to KeyTime size
		assert(NumPosKeys <= 1 || NumPosKeys == NumTimeKeys);
		assert(NumRotKeys == 1 || NumRotKeys == NumTimeKeys);

		GetKeyParams(KeyTime, Frame, NumFrames, Loop, posX, posY, posF);
		rotX = posX;
		rotY = posY;
		rotF = posF;

		if (NumPosKeys <= 1)
		{
			posX = posY = 0;
			posF = 0;
		}
		if (NumRotKeys == 1)
		{
			rotX = rotY = 0;
			rotF = 0;
		}
	}
	else
	{
		// empty KeyTime array - keys are evenly spaced on a time line
		// note: KeyPos and KeyQuat sizes can be different
		if (KeyPosTime.Num())
		{
			GetKeyParams(KeyPosTime, Frame, NumFrames, Loop, posX, posY, posF);
		}
		else if (NumPosKeys > 1)
		{
			float Position = Frame / NumFrames * NumPosKeys;
			posX = appFloor(Position);
			posF = Position - posX;
			posY = posX + 1;
			if (posY >= NumPosKeys)
			{
				if (!Loop)
				{
					posY = NumPosKeys - 1;
					posF = 0;
				}
				else
					posY = 0;
			}
		}
		else
		{
			posX = posY = 0;
			posF = 0;
		}

		if (KeyQuatTime.Num())
		{
			GetKeyParams(KeyQuatTime, Frame, NumFrames, Loop, rotX, rotY, rotF);
		}
		else if (NumRotKeys > 1)
		{
			float Position = Frame / NumFrames * NumRotKeys;
			rotX = appFloor(Position);
			rotF = Position - rotX;
			rotY = rotX + 1;
			if (rotY >= NumRotKeys)
			{
				if (!Loop)
				{
					rotY = NumRotKeys - 1;
					rotF = 0;
				}
				else
					rotY = 0;
			}
		}
		else
		{
			rotX = rotY = 0;
			rotF = 0;
		}
	}

	// get position
	if (posF > 0)
		Lerp(KeyPos[posX], KeyPos[posY], posF, DstPos);
	else if (NumPosKeys)		// do not change DstPos when no keys
		DstPos = KeyPos[posX];
	// get orientation
	if (rotF > 0)
		Slerp(KeyQuat[rotX], KeyQuat[rotY], rotF, DstQuat);
	else if (NumRotKeys)		// do not change DstQuat when no keys
		DstQuat = KeyQuat[rotX];

	unguard;
}