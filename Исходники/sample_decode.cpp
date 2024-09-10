mfxStatus ParseInputString(msdk_char* strInput[], mfxU8 nArgNum, sInputParams* pParams)
{
    if (1 == nArgNum)
    {
        PrintHelp(strInput[0], NULL);
        return MFX_ERR_UNSUPPORTED;
    }

    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);

    // set default implementation
    pParams->bUseHWLib = true;
    pParams->bUseFullColorRange = false;
#if defined(LIBVA_SUPPORT)
    pParams->libvaBackend = MFX_LIBVA_DRM;
#endif

    for (mfxU8 i = 1; i < nArgNum; i++)
    {
        if (MSDK_CHAR('-') != strInput[i][0])
        {
            mfxStatus sts = StrFormatToCodecFormatFourCC(strInput[i], pParams->videoType);
            if (sts != MFX_ERR_NONE)
            {
                PrintHelp(strInput[0], MSDK_STRING("Unknown codec"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (!IsDecodeCodecSupported(pParams->videoType))
            {
                PrintHelp(strInput[0], MSDK_STRING("Unsupported codec"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (pParams->videoType == CODEC_MVC)
            {
                pParams->videoType = MFX_CODEC_AVC;
                pParams->bIsMVC = true;
            }
            continue;
        }

        if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-sw")))
        {
            pParams->bUseHWLib = false;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-hw")))
        {
            pParams->bUseHWLib = true;
        }
#if D3D_SURFACES_SUPPORT
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-d3d")))
        {
            pParams->memType = D3D9_MEMORY;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-d3d11")))
        {
            pParams->memType = D3D11_MEMORY;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-r")))
        {
            pParams->mode = MODE_RENDERING;
            // use d3d9 rendering by default
            if (SYSTEM_MEMORY == pParams->memType)
                pParams->memType = D3D9_MEMORY;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-wall")))
        {
            if(i + 6 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -wall key"));
                return MFX_ERR_UNSUPPORTED;
            }
            // use d3d9 rendering by default
            if (SYSTEM_MEMORY == pParams->memType)
                pParams->memType = D3D9_MEMORY;

            pParams->mode = MODE_RENDERING;

            msdk_opt_read(strInput[++i], pParams->nWallW);
            msdk_opt_read(strInput[++i], pParams->nWallH);
            msdk_opt_read(strInput[++i], pParams->nWallCell);
            msdk_opt_read(strInput[++i], pParams->nWallMonitor);

            mfxU32 nTitle;
            msdk_opt_read(strInput[++i], nTitle);

            pParams->bWallNoTitle = 0 == nTitle;

            msdk_opt_read(strInput[++i], pParams->nWallTimeout);
        }
#endif
#if defined(LIBVA_SUPPORT)
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-vaapi")))
        {
            pParams->memType = D3D9_MEMORY;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-r")))
        {
            pParams->memType = D3D9_MEMORY;
            pParams->mode = MODE_RENDERING;
            pParams->libvaBackend = MFX_LIBVA_X11;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-rwld")))
        {
            pParams->memType = D3D9_MEMORY;
            pParams->mode = MODE_RENDERING;
            pParams->libvaBackend = MFX_LIBVA_WAYLAND;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-perf")))
        {
            pParams->bPerfMode = true;
        }
        else if (0 == msdk_strncmp(strInput[i], MSDK_STRING("-rdrm"), 5))
        {
            pParams->memType = D3D9_MEMORY;
            pParams->mode = MODE_RENDERING;
            pParams->libvaBackend = MFX_LIBVA_DRM_MODESET;
            if (strInput[i][5]) {
                if (strInput[i][5] != '-') {
                    PrintHelp(strInput[0], MSDK_STRING("unsupported monitor type"));
                    return MFX_ERR_UNSUPPORTED;
                }
                pParams->monitorType = getMonitorType(&strInput[i][6]);
                if (pParams->monitorType >= MFX_MONITOR_MAXNUMBER) {
                    PrintHelp(strInput[0], MSDK_STRING("unsupported monitor type"));
                    return MFX_ERR_UNSUPPORTED;
                }
            } else {
                pParams->monitorType = MFX_MONITOR_AUTO; // that's case of "-rdrm" pure option
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-window")))
        {
            if(i +4 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -window key"));
                return MFX_ERR_UNSUPPORTED;
            }
            msdk_opt_read(strInput[++i], pParams->nRenderWinX);
            msdk_opt_read(strInput[++i], pParams->nRenderWinY);
            msdk_opt_read(strInput[++i], pParams->Width);
            msdk_opt_read(strInput[++i], pParams->Height);

            if (0 == pParams->Width)
                pParams->Width = 320;
            if (0 == pParams->Height)
                pParams->Height = 240;

            pParams->bRenderWin = true;
        }
#endif
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-low_latency")))
        {
            switch (pParams->videoType)
            {
                case MFX_CODEC_HEVC:
                case MFX_CODEC_AVC:
                case MFX_CODEC_JPEG:
                {
                    pParams->bLowLat = true;
                    if (!pParams->bIsMVC)
                        break;
                }
                default:
                {
                     PrintHelp(strInput[0], MSDK_STRING("-low_latency mode is suppoted only for H.264 and JPEG codecs"));
                     return MFX_ERR_UNSUPPORTED;
                }
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-jpeg_rotate")))
        {
            if(MFX_CODEC_JPEG != pParams->videoType)
                return MFX_ERR_UNSUPPORTED;

            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -jpeg_rotate key"));
                return MFX_ERR_UNSUPPORTED;
            }

            msdk_opt_read(strInput[++i], pParams->nRotation);
            if((pParams->nRotation != 90)&&(pParams->nRotation != 180)&&(pParams->nRotation != 270))
            {
                PrintHelp(strInput[0], MSDK_STRING("-jpeg_rotate is supported only for 90, 180 and 270 angles"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-calc_latency")))
        {
            switch (pParams->videoType)
            {
                case MFX_CODEC_HEVC:
                case MFX_CODEC_AVC:
                case MFX_CODEC_JPEG:
                {
                    pParams->bCalLat = true;
                    if (!pParams->bIsMVC)
                        break;
                }
                default:
                {
                     PrintHelp(strInput[0], MSDK_STRING("-calc_latency mode is suppoted only for H.264 and JPEG codecs"));
                     return MFX_ERR_UNSUPPORTED;
                }
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-async")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -async key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nAsyncDepth))
            {
                PrintHelp(strInput[0], MSDK_STRING("async is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-di")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -di key"));
                return MFX_ERR_UNSUPPORTED;
            }
            msdk_char diMode[4] = {};
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], diMode))
            {
                PrintHelp(strInput[0], MSDK_STRING("deinterlace value is not set"));
                return MFX_ERR_UNSUPPORTED;
            }

            if (0 == msdk_strcmp(diMode, MSDK_CHAR("bob")))
            {
                pParams->eDeinterlace = MFX_DEINTERLACING_BOB;
            }
            else if (0 == msdk_strcmp(diMode, MSDK_CHAR("adi")))
            {
                pParams->eDeinterlace = MFX_DEINTERLACING_ADVANCED;
            }
            else
            {
                PrintHelp(strInput[0], MSDK_STRING("deinterlace value is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gpucopy::on")))
        {
            pParams->gpuCopy = MFX_GPUCOPY_ON;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-gpucopy::off")))
        {
            pParams->gpuCopy = MFX_GPUCOPY_OFF;
        }
#if !defined(_WIN32) && !defined(_WIN64)
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-threads_num")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -threads_num key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nThreadsNum))
            {
                PrintHelp(strInput[0], MSDK_STRING("threads_num is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-threads_schedtype")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -threads_schedtype key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_thread_get_schedtype(strInput[++i], pParams->SchedulingType))
            {
                PrintHelp(strInput[0], MSDK_STRING("threads_schedtype is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-threads_priority")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -threads_priority key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->Priority))
            {
                PrintHelp(strInput[0], MSDK_STRING("threads_priority is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
#endif // #if !defined(_WIN32) && !defined(_WIN64)
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-f")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -f key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nMaxFPS))
            {
                PrintHelp(strInput[0], MSDK_STRING("rendering frame rate is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-scr:w")))
        {
            if (i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -scr:w key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->scrWidth))
            {
                PrintHelp(strInput[0], MSDK_STRING("screen width rate is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-scr:h")))
        {
            if (i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -scr:h key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->scrHeight))
            {
                PrintHelp(strInput[0], MSDK_STRING("screen height is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-w")))
        {
            if (i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -w key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->Width))
            {
                PrintHelp(strInput[0], MSDK_STRING("width is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-h")))
        {
            if (i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -h key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->Height))
            {
                PrintHelp(strInput[0], MSDK_STRING("height is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-n")))
        {
            if(i + 1 >= nArgNum)
            {
                PrintHelp(strInput[0], MSDK_STRING("Not enough parameters for -n key"));
                return MFX_ERR_UNSUPPORTED;
            }
            if (MFX_ERR_NONE != msdk_opt_read(strInput[++i], pParams->nFrames))
            {
                PrintHelp(strInput[0], MSDK_STRING("rendering frame rate is invalid"));
                return MFX_ERR_UNSUPPORTED;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-jpeg_rgb")))
        {
            if(MFX_CODEC_JPEG == pParams->videoType)
            {
               pParams->chromaType = MFX_JPEG_COLORFORMAT_RGB;
            }
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-i420")))
        {
            pParams->fourcc = MFX_FOURCC_NV12;
            pParams->outI420 = true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-nv12")))
        {
            pParams->fourcc = MFX_FOURCC_NV12;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-rgb4")))
        {
            pParams->fourcc = MFX_FOURCC_RGB4;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-rgb4_fcr")))
        {
            pParams->fourcc = MFX_FOURCC_RGB4;
            pParams->bUseFullColorRange = true;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-p010")))
        {
            pParams->fourcc = MFX_FOURCC_P010;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-a2rgb10")))
        {
            pParams->fourcc = MFX_FOURCC_A2RGB10;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-path")))
        {
            i++;
#if defined(_WIN32) || defined(_WIN64)
            msdk_char wchar[MSDK_MAX_FILENAME_LEN];
            msdk_opt_read(strInput[i], wchar);
            std::wstring wstr(wchar);
            std::string str(wstr.begin(), wstr.end());

            strcpy_s(pParams->pluginParams.strPluginPath, str.c_str());
#else
            msdk_opt_read(strInput[i], pParams->pluginParams.strPluginPath);
#endif
            pParams->pluginParams.type = MFX_PLUGINLOAD_TYPE_FILE;
        }
        else if (0 == msdk_strcmp(strInput[i], MSDK_STRING("-i:null")))
        {
            ;
        }
        else // 1-character options
        {
            switch (strInput[i][1])
            {
            case MSDK_CHAR('p'):
                if (++i < nArgNum) {
                   if (MFX_ERR_NONE == ConvertStringToGuid(strInput[i], pParams->pluginParams.pluginGuid))
                    {
                        pParams->pluginParams.type = MFX_PLUGINLOAD_TYPE_GUID;
                    }
                    else
                    {
                        PrintHelp(strInput[0], MSDK_STRING("Unknown options"));
                    }
                 }
                else {
                    msdk_printf(MSDK_STRING("error: option '-p' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('i'):
                if (++i < nArgNum) {
                    msdk_opt_read(strInput[i], pParams->strSrcFile);
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-i' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('o'):
                if (++i < nArgNum) {
                    pParams->mode = MODE_FILE_DUMP;
                    msdk_opt_read(strInput[i], pParams->strDstFile);
                }
                else {
                    msdk_printf(MSDK_STRING("error: option '-o' expects an argument\n"));
                }
                break;
            case MSDK_CHAR('?'):
                PrintHelp(strInput[0], NULL);
                return MFX_ERR_UNSUPPORTED;
            default:
                {
                    std::basic_stringstream<msdk_char> stream;
                    stream << MSDK_STRING("Unknown option: ") << strInput[i];
                    PrintHelp(strInput[0], stream.str().c_str());
                    return MFX_ERR_UNSUPPORTED;
                }
            }
        }
    }

    if (0 == msdk_strlen(pParams->strSrcFile) && MFX_CODEC_CAPTURE != pParams->videoType)
    {
        msdk_printf(MSDK_STRING("error: source file name not found"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_CODEC_CAPTURE == pParams->videoType)
    {
        if (!pParams->scrWidth || !pParams->scrHeight)
        {
            msdk_printf(MSDK_STRING("error: for screen capture, width and height must be specified manually (-scr:w and -scr:h)"));
            return MFX_ERR_UNSUPPORTED;
        }
    }
    else if (pParams->scrWidth || pParams->scrHeight)
    {
        msdk_printf(MSDK_STRING("error: width and height parameters are supported only by screen capture decoder"));
        return MFX_ERR_UNSUPPORTED;
    }

    if ((pParams->mode == MODE_FILE_DUMP) && (0 == msdk_strlen(pParams->strDstFile)))
    {
        msdk_printf(MSDK_STRING("error: destination file name not found"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (MFX_CODEC_MPEG2   != pParams->videoType &&
        MFX_CODEC_AVC     != pParams->videoType &&
        MFX_CODEC_HEVC    != pParams->videoType &&
        MFX_CODEC_VC1     != pParams->videoType &&
        MFX_CODEC_JPEG    != pParams->videoType &&
        MFX_CODEC_CAPTURE != pParams->videoType &&
        CODEC_VP8         != pParams->videoType)
    {
        PrintHelp(strInput[0], MSDK_STRING("Unknown codec"));
        return MFX_ERR_UNSUPPORTED;
    }

    if (pParams->nAsyncDepth == 0)
    {
        pParams->nAsyncDepth = 4; //set by default;
    }

    return MFX_ERR_NONE;
}