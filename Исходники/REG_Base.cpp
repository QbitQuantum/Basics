void MRegistryBase::ConnectLocal()
{
	if (bRemote)
	{
		if (sRemoteResource[0])
		{
			WNetCancelConnection2W(sRemoteResource, 0, 0);
		}
	}
	bRemote = false; sRemoteServer[0] = 0; sRemoteResource[0] = 0;
}