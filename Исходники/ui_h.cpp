int32 UI_CheckObjectMask(int32 nMessage, AActor* oTarget)
{
	int32 nDispMask = GetM2DAInt(TABLE_UI_MESSAGES, "ObjectMask", nMessage);

	if (nDispMask != 0)
	{
		int32 bShow = ((nDispMask & 0xffffff) == 0xffffff);

		if (!bShow)
		{
			bShow = ((nDispMask & GetObjectType(oTarget)) == GetObjectType(oTarget));
		}

		return bShow;
	}
	return FALSE_;
}