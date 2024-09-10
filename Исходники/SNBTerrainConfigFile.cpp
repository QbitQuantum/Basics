// Parses the configuration file
HRESULT ParseConfigurationFile( LPCWSTR ConfigFilePath )
{
	g_DX11PatchRenderParams.m_bAsyncModeWorkaround = true;

    FILE *pConfigFile = NULL;
    if( _wfopen_s( &pConfigFile, ConfigFilePath, L"r" ) != 0 )
    {
        CHECK_HR_RET(E_FAIL, "Failed to open the configuration file (%s)", ConfigFilePath);
    }
    
    while( !feof(pConfigFile) )
    {
        WCHAR Parameter[128];
        WCHAR EqualSign[128];

        fwscanf_s( pConfigFile, L"%s", Parameter, _countof(Parameter));
        fwscanf_s( pConfigFile, L"%s", EqualSign, _countof(EqualSign));
        if( wcscmp(EqualSign, L"=") != 0 )
        {
            // LOG_ERROR( "Equal sign (=) is missing for parameter \"%s\"", Parameter);
            goto ERROR_EXIT;
        }

        // Directories
        if( wcscmp(L"RawDEMDataFile", Parameter) == 0 )
        {
            ParseParameterString(g_strRawDEMDataFile, MAX_PATH_LENGTH, pConfigFile);
        }
        else if( wcscmp(L"EncodedRQTTriangFile", Parameter) == 0 )
        {
            ParseParameterString(g_strEncodedRQTTriangFile, MAX_PATH_LENGTH, pConfigFile);
        }
		else if( wcscmp(L"CameraTrack", Parameter) == 0 )
        {
            ParseParameterString(g_strCameraTrackPath, MAX_PATH_LENGTH, pConfigFile);
        }
        else if( wcscmp(L"TexturingMode", Parameter) == 0 )
        {
            WCHAR Value[128];
            ParseParameterString(Value, _countof(Value), pConfigFile);
            /*if( wcscmp(L"HeightBased", Value) == 0 )
                g_DX11PatchRenderParams.m_TexturingMode = CAdaptiveModelDX11Render::TM_HEIGHT_BASED;
            else ;*/
                // LOG_ERROR( "Unknown texturing mode (%s)\n"
                           //"Only the following modes are recognized:\n"
                           //"HeightBased\n", Value);
        }
        else
        {
            WCHAR Value[128];
            fwscanf_s( pConfigFile, L"%s", Value, _countof(Value));

            // Parameters
            if( wcscmp(L"ForceRecreateTriang", Parameter) == 0 )
            {
                if( FAILED(ParseParameterBool( Value, g_bForceRecreateTriang ) ) )
                {
                    // LOG_ERROR( "Failed to parse value of the parameter \"%s\"", Parameter);
                    goto ERROR_EXIT;
                }
            }
            else if( wcscmp(L"ElevationSamplingInterval", Parameter) == 0 )
            {
                g_fElevationSamplingInterval = ParseParameterFloat( Value );
            }
			else if(  wcscmp(L"ScalingFactor", Parameter) == 0 )
			{
				g_fElevationScale = ParseParameterFloat( Value );
			}
            else if( wcscmp(L"NumColumns", Parameter) == 0 )
            {
                g_iNumColumns = ParseParameterInt( Value );
            }
            else if( wcscmp(L"NumRows", Parameter) == 0 )
            {
                g_iNumRows = ParseParameterInt( Value );
            }
            else if( wcscmp(L"PatchSize", Parameter) == 0 )
            {
                g_iPatchSize = ParseParameterInt( Value );
            }
            else if( wcscmp(L"ScreenSpaceThreshold", Parameter) == 0 )
            {
                g_TerrainRenderParams.m_fScrSpaceErrorBound = ParseParameterFloat( Value );
            }
		    else if( wcscmp(L"AsyncModeWorkaround", Parameter) == 0 )
            {
                if( FAILED(ParseParameterBool( Value, g_DX11PatchRenderParams.m_bAsyncModeWorkaround) ) )
                {
                    // LOG_ERROR( "Failed to parse value of the parameter \"%s\"", Parameter);
                    goto ERROR_EXIT;
                }
            }
        }
    }

    fclose(pConfigFile);

    return S_OK;

ERROR_EXIT:

    fclose(pConfigFile);

    return E_FAIL;
}