	HRESULT InitializeDXVAHD(IDirect3DDevice9Ex *pD3DDevice){
		HRESULT hr = S_OK;
		DWORD index = 0;

		DXVAHD_CONTENT_DESC desc;

		desc.InputFrameFormat = DXVAHD_FRAME_FORMAT_PROGRESSIVE;
		desc.InputFrameRate.Numerator = VIDEO_FPS;
		desc.InputFrameRate.Denominator = 1;
		desc.InputWidth = VIDEO_MAIN_WIDTH;
		desc.InputHeight = VIDEO_MAIN_HEIGHT;
		desc.OutputFrameRate.Numerator = VIDEO_FPS;
		desc.OutputFrameRate.Denominator = 1;
		desc.OutputWidth = VIDEO_MAIN_WIDTH;
		desc.OutputHeight = VIDEO_MAIN_HEIGHT;

		PDXVAHDSW_Plugin pSWPlugin = nullptr;

		hr = DXVAHD_CreateDevice(
			pD3DDevice,
			&desc,
			DXVAHD_DEVICE_USAGE_PLAYBACK_NORMAL,
			pSWPlugin,
			&m_pDXVAHD
			);
		if (FAILED(hr)){ 
			return hr ; 
		}

		// Get the DXVA-HD device caps.

		ZeroMemory(&caps, sizeof(caps));

		hr = m_pDXVAHD->GetVideoProcessorDeviceCaps(&caps);
		if (FAILED(hr)){ 
			return hr ; 
		}

		if (caps.MaxInputStreams < 1 + SUB_STREAM_COUNT){
			DBGMSG(L"Device only supports %d input streams.\n", caps.MaxInputStreams);
			return E_UNEXPECTED ;
		}

		// Check the output format.

		m_inputFormat.clear() ;
		m_inputFormat.resize(caps.OutputFormatCount) ;

		hr = m_pDXVAHD->GetVideoProcessorOutputFormats(caps.OutputFormatCount, &m_inputFormat[0]);
		if (FAILED(hr)){ 
			return hr ; 
		}

		for (index = 0; index < caps.OutputFormatCount; index++){
			if (m_inputFormat[index] == VIDEO_RENDER_TARGET_FORMAT){
				break;
			}
		}
		if (index == caps.OutputFormatCount){
			return E_UNEXPECTED ;
		}

		// Check the input formats.

		m_inputFormat.clear() ;
		m_inputFormat.resize(caps.InputFormatCount) ;

		hr = m_pDXVAHD->GetVideoProcessorInputFormats(caps.InputFormatCount, &m_inputFormat[0]);
		if (FAILED(hr)){ 
			return hr ; 
		}

		D3DFORMAT inputFormats[] = { VIDEO_MAIN_FORMAT, VIDEO_SUB_FORMAT };

		for (DWORD j = 0; j < 2; j++){
			for (index = 0; index < caps.InputFormatCount; index++){
				if (m_inputFormat[index] == inputFormats[j]){
					break;
				}
			}
			if (index == caps.InputFormatCount){
				return E_UNEXPECTED ;
			}
		}

		return S_OK ;
	}