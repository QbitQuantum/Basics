	EngineState::EngineState() :
#if defined(_PROFILE) | defined(_DEBUG)
		m_displayShadowMaps(false),
		m_displayShadowFrustum(false),
		m_displayShadowBuffer(false),
#endif
		m_BackBufferDesc({ 1280, 720, 
			DXGI_FORMAT_R16G16B16A16_FLOAT, 
			{ 1, 0 } }),
		m_Viewport({ 0.0f, 0.0f, 
			static_cast<float>(m_BackBufferDesc.Width), 
			static_cast<float>(m_BackBufferDesc.Height), 
			0.0f, 1.0f}),
		m_Light(-0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f),
		m_LightDirection(XMVector3Normalize(XMVectorSet(1.f, 0.5f, 0.3f, 0.f))),

		m_fovy(XM_PI / 3.f),
		m_aspect(m_Viewport.Width / m_Viewport.Height),
		m_znear(0.1f),
		m_zfar(200.f),

		m_LightShafts(true),
		m_DepthOfField(true),
		m_Bloom(true),
		m_AmbientOcclusion(true),
		m_Fxaa(true),

		m_ShadowMapSize(2048),
		m_ShadowMapCount(3),
		m_ShadowMapQuality(1),
		m_ShadowMapType(2),

		m_fullScreen(false),
		m_vsync(true),
		m_refreshRate({60,1})
	{
		NvGsaApplication app;
		NvGsaStatus status;

		const NvGsaNamedOption *options = NULL;
		size_t numOptions = 0;

		const NvGsaResolution *resolutions = NULL;
		size_t numResolutions = 0;

		NvGsaVersion runtimeVersion = GFSDK_GSA_GetVersion();

		// Print the GSA compile time version
		wprintf(L"Compiled against GSA version: ");
		printGsaVersion(&NvGsaCurrentVersion);
		wprintf(L"\n");

		// Print the GSA run time version
		wprintf(L"Running against GSA version: ");
		printGsaVersion(&runtimeVersion);
		wprintf(L"\n");

		// Initialize the application
		LPWSTR *szArglist;
		int nArgs = 0;
		szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
		if (nArgs < 1 || !initApplication(&app, szArglist[0])) {
			wprintf(L"Failed to initialize the application, exiting!");
			return;
		}
		GlobalFree(szArglist);

		// Initialize the GSA SDK
		status = GFSDK_GSA_InitializeSDK(&app, &NvGsaCurrentVersion);
		releaseApplication(&app);
		if (status != NV_GSA_STATUS_OK) {
			wprintf(L"Failed to initialize the GSA SDK, exiting!");
			return;
		}

		if (initOptions(&options, &numOptions) &&
			initResolutions(&resolutions, &numResolutions)) {

			//status = GFSDK_GSA_SaveConfigFile(NV_GSA_SAVE_ALL);

			NvGsaResolution currentResolution;
			size_t i;

			// Register the options
			for (i = 0; i < numOptions; ++i) {
				GFSDK_GSA_RegisterOption(&options[i]);
			}

			// Register the resolutions
			GFSDK_GSA_RegisterResolutions(resolutions, (int)numResolutions);

			// Load the config file
			status = GFSDK_GSA_LoadConfigFile();
			if (status == NV_GSA_STATUS_FILENOTFOUND) {
				GFSDK_GSA_SetResolution(&resolutions[0]);
			}

			// Print and cycle the options
			for (i = 0; i < numOptions; ++i) {
				NvGsaVariant value;
				value.type = options[i].value.type;
				status = GFSDK_GSA_GetOptionValue(&value, options[i].name);
				if (status == NV_GSA_STATUS_OK) {

					switch (str2int(options[i].name))
					{
					case str2int(L"Field_Of_View"):
						m_fovy = value.asFloat;
						break;
					case str2int(L"Near_Plane"):
						m_znear = value.asFloat;
						break;
					case str2int(L"Far_Plane"):
						m_zfar = value.asFloat;
						break;
					case str2int(L"LightShafts"):
						m_LightShafts = value.asBool;
						break;
					case str2int(L"DepthOfField"):
						m_DepthOfField = value.asBool;
						break;
					case str2int(L"Bloom"):
						m_Bloom = value.asBool;
						break;
					case str2int(L"AmbientOcclusion"):
						m_AmbientOcclusion = value.asBool;
						break;
					case str2int(L"Fxaa"):
						m_Fxaa = value.asBool;
						break;
					case str2int(L"FullScreen"):
						m_fullScreen = value.asBool;
						break;
					case str2int(L"V-Sync"):
						m_vsync = value.asBool;
						break;
					case str2int(L"ShadowMapSize"):
						switch (str2int(value.asEnum))
						{
						case str2int(L"512"):
							m_ShadowMapSize = 512;
							break;
						case str2int(L"1024"):
							m_ShadowMapSize = 1024;
							break;
						case str2int(L"2048"):
							m_ShadowMapSize = 2048;
							break;
						case str2int(L"4096"):
							m_ShadowMapSize = 4096;
							break;
						}
						break;
					case str2int(L"ShadowMapCount"):
						m_ShadowMapCount = value.asInt;
						break;
					case str2int(L"ShadowMapQuality"):
						switch (str2int(value.asEnum))
						{
						case str2int(L"Low_Hard"):
							m_ShadowMapQuality = 0;
							m_ShadowMapType = 0;
							break;
						case str2int(L"Medium_Hard"):
							m_ShadowMapQuality = 1;
							m_ShadowMapType = 0;
							break;
						case str2int(L"High_Hard"):
							m_ShadowMapQuality = 2;
							m_ShadowMapType = 0;
							break;
						case str2int(L"Low_PCF"):
							m_ShadowMapQuality = 0;
							m_ShadowMapType = 1;
							break;
						case str2int(L"Medium_PCF"):
							m_ShadowMapQuality = 1;
							m_ShadowMapType = 1;
							break;
						case str2int(L"High_PCF"):
							m_ShadowMapQuality = 2;
							m_ShadowMapType = 1;
							break;
						case str2int(L"Low_PCSS"):
							m_ShadowMapQuality = 0;
							m_ShadowMapType = 2;
							break;
						case str2int(L"Medium_PCSS"):
							m_ShadowMapQuality = 1;
							m_ShadowMapType = 2;
							break;
						case str2int(L"High_PCSS"):
							m_ShadowMapQuality = 2;
							m_ShadowMapType = 2;
							break;
						}
						break;
					}
					GFSDK_GSA_ReleaseVariant(&value);
				}
			}

			// Print and increment the resolution
			status = GFSDK_GSA_GetResolution(&currentResolution);
			if (status == NV_GSA_STATUS_OK) {
				m_refreshRate.Numerator = (UINT)round(currentResolution.refreshRate);
				WindowSizeChanged(currentResolution.width, currentResolution.height);
			}
		}

		// Cleanup
		releaseOptions(options);
		releaseResolutions(resolutions);

		m_Camera.SetProjParams(m_fovy, m_aspect, m_znear, m_zfar);
		m_Camera.SetViewParams(XMVectorSet(0.f, 0.f, 0.f, 1.f), XMVectorSet(0.f, 0.f, 1.f, 1.f));
	}