CStdString UrlSerializer::FindClass(CStdString& input)
{
	CStdString result;
	int equalsPostion = input.Find('=');
	if (equalsPostion != -1)
	{
		int ampersandPostion = input.Find('&');
		if (ampersandPostion > equalsPostion)
		{
			// there is at least one parameter
			result = input.Mid(equalsPostion+1, ampersandPostion-equalsPostion-1);
		}
		else
		{
			// there is no parameter
			result = input.Mid(equalsPostion+1, input.GetLength() - equalsPostion - 1);
		}
	}
	result.ToLower();
	return result;
}