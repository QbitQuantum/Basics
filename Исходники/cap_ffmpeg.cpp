    icvInitFFMPEG()
    {
    #if defined _WIN32
        const wchar_t* module_name_ = L"opencv_ffmpeg"
            CVAUX_STRW(CV_MAJOR_VERSION) CVAUX_STRW(CV_MINOR_VERSION) CVAUX_STRW(CV_SUBMINOR_VERSION)
        #if (defined _MSC_VER && defined _M_X64) || (defined __GNUC__ && defined __x86_64__)
            L"_64"
        #endif
            L".dll";
    # ifdef WINRT
        icvFFOpenCV = LoadPackagedLibrary( module_name_, 0 );
    # else
        const std::wstring module_name(module_name_);

        const wchar_t* ffmpeg_env_path = _wgetenv(L"OPENCV_FFMPEG_DLL_DIR");
        std::wstring module_path =
                ffmpeg_env_path
                ? ((std::wstring(ffmpeg_env_path) + L"\\") + module_name)
                : module_name;

        icvFFOpenCV = LoadLibraryW(module_path.c_str());
        if(!icvFFOpenCV && !ffmpeg_env_path)
        {
            HMODULE m = cv_GetCurrentModule();
            if (m)
            {
                wchar_t path[MAX_PATH];
                const size_t path_size = sizeof(path)/sizeof(*path);
                size_t sz = GetModuleFileNameW(m, path, path_size);
                /* Don't handle paths longer than MAX_PATH until that becomes a real issue */
                if (sz > 0 && sz < path_size)
                {
                    wchar_t* s = wcsrchr(path, L'\\');
                    if (s)
                    {
                        s[0] = 0;
                        module_path = (std::wstring(path) + L"\\") + module_name;
                        icvFFOpenCV = LoadLibraryW(module_path.c_str());
                    }
                }
            }
        }
    # endif

        if( icvFFOpenCV )
        {
            icvCreateFileCapture_FFMPEG_p =
                (CvCreateFileCapture_Plugin)GetProcAddress(icvFFOpenCV, "cvCreateFileCapture_FFMPEG");
            icvReleaseCapture_FFMPEG_p =
                (CvReleaseCapture_Plugin)GetProcAddress(icvFFOpenCV, "cvReleaseCapture_FFMPEG");
            icvGrabFrame_FFMPEG_p =
                (CvGrabFrame_Plugin)GetProcAddress(icvFFOpenCV, "cvGrabFrame_FFMPEG");
            icvRetrieveFrame_FFMPEG_p =
                (CvRetrieveFrame_Plugin)GetProcAddress(icvFFOpenCV, "cvRetrieveFrame_FFMPEG");
            icvSetCaptureProperty_FFMPEG_p =
                (CvSetCaptureProperty_Plugin)GetProcAddress(icvFFOpenCV, "cvSetCaptureProperty_FFMPEG");
            icvGetCaptureProperty_FFMPEG_p =
                (CvGetCaptureProperty_Plugin)GetProcAddress(icvFFOpenCV, "cvGetCaptureProperty_FFMPEG");
            icvCreateVideoWriter_FFMPEG_p =
                (CvCreateVideoWriter_Plugin)GetProcAddress(icvFFOpenCV, "cvCreateVideoWriter_FFMPEG");
            icvReleaseVideoWriter_FFMPEG_p =
                (CvReleaseVideoWriter_Plugin)GetProcAddress(icvFFOpenCV, "cvReleaseVideoWriter_FFMPEG");
            icvWriteFrame_FFMPEG_p =
                (CvWriteFrame_Plugin)GetProcAddress(icvFFOpenCV, "cvWriteFrame_FFMPEG");

#if 0
            if( icvCreateFileCapture_FFMPEG_p != 0 &&
                icvReleaseCapture_FFMPEG_p != 0 &&
                icvGrabFrame_FFMPEG_p != 0 &&
                icvRetrieveFrame_FFMPEG_p != 0 &&
                icvSetCaptureProperty_FFMPEG_p != 0 &&
                icvGetCaptureProperty_FFMPEG_p != 0 &&
                icvCreateVideoWriter_FFMPEG_p != 0 &&
                icvReleaseVideoWriter_FFMPEG_p != 0 &&
                icvWriteFrame_FFMPEG_p != 0 )
            {
                printf("Successfully initialized ffmpeg plugin!\n");
            }
            else
            {
                printf("Failed to load FFMPEG plugin: module handle=%p\n", icvFFOpenCV);
            }
#endif
        }
    #elif defined HAVE_FFMPEG
        icvCreateFileCapture_FFMPEG_p = (CvCreateFileCapture_Plugin)cvCreateFileCapture_FFMPEG;
        icvReleaseCapture_FFMPEG_p = (CvReleaseCapture_Plugin)cvReleaseCapture_FFMPEG;
        icvGrabFrame_FFMPEG_p = (CvGrabFrame_Plugin)cvGrabFrame_FFMPEG;
        icvRetrieveFrame_FFMPEG_p = (CvRetrieveFrame_Plugin)cvRetrieveFrame_FFMPEG;
        icvSetCaptureProperty_FFMPEG_p = (CvSetCaptureProperty_Plugin)cvSetCaptureProperty_FFMPEG;
        icvGetCaptureProperty_FFMPEG_p = (CvGetCaptureProperty_Plugin)cvGetCaptureProperty_FFMPEG;
        icvCreateVideoWriter_FFMPEG_p = (CvCreateVideoWriter_Plugin)cvCreateVideoWriter_FFMPEG;
        icvReleaseVideoWriter_FFMPEG_p = (CvReleaseVideoWriter_Plugin)cvReleaseVideoWriter_FFMPEG;
        icvWriteFrame_FFMPEG_p = (CvWriteFrame_Plugin)cvWriteFrame_FFMPEG;
    #endif
    }