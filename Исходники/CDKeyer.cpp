int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR commandLine, int nCmdShow)
{
	if (strlen(commandLine) <= 0)
	{
		return -1;
	}

    WONCDKey::ClientCDKey aCDKey("Homeworld");
    
	if (aCDKey.Init(_strupr(commandLine)))
	{
		if (aCDKey.IsValid())
		{
			if (aCDKey.Save())
			{
				__int64 rawdata = aCDKey.AsRaw();	// just for debugging purposes
				WriteCDKeyToRegistryUnencrypted(commandLine);
				return 0;
			}
		}
	}

	return -1;
}