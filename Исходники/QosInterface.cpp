const FString& FQosInterface::GetDefaultRegionString()
{
	static FString RegionString = TEXT("");
	if (RegionString.IsEmpty())
	{
		FString OverrideRegion;
		if (FParse::Value(FCommandLine::Get(), TEXT("McpRegion="), OverrideRegion))
		{
			// Region specified on command line
			RegionString = OverrideRegion.ToUpper();
		}
		else
		{
			FString DefaultRegion;
			if (GConfig->GetString(TEXT("Qos"), TEXT("DefaultRegion"), DefaultRegion, GGameIni))
			{
				// Region specified in ini file
				RegionString = DefaultRegion.ToUpper();
			}
			else
			{
				// No Region specified. Assume USA.
				RegionString = TEXT("USA");
			}
		}
	}

	return RegionString;
}