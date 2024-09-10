void VideoBackend::PopulateList()
{
	VideoBackend* backends[4] = { NULL };

	// D3D9 > D3D11 > OGL > SW
#ifdef _WIN32
	g_available_video_backends.push_back(backends[0] = new DX9::VideoBackend);
	if (IsWindowsVistaOrGreater())
	{
		g_available_video_backends.push_back(backends[1] = new DX11::VideoBackend);
		//if (IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN10), LOBYTE(_WIN32_WINNT_WIN10), 0))
		{
			g_available_video_backends.push_back(backends[2] = new DX12::VideoBackend);
		}
	}
#endif
// disable OGL video Backend while is merged from master
#if !defined(USE_GLES) || USE_GLES3
	g_available_video_backends.push_back(backends[2] = new OGL::VideoBackend);
#endif
	g_available_video_backends.push_back(backends[3] = new SW::VideoSoftware);

	for (int i = 0; i < 4; ++i)
	{
		if (backends[i])
		{
			s_default_backend = g_video_backend = backends[i];
			break;
		}
	}
}