void CSWICertStoreTool::LogArgL(const TDesC8& aName, const TDesC& aValue)
	{
	TBuf8<KMaxLineLength> buf;
	buf.Copy(aValue);
	LogL(KLogParameterTemplate, &aName, &buf);
	}