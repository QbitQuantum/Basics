bool UBWindowsMediaFile::init(const QString& videoFileName, const QString& profileData, int pFramesPerSecond
                , int pixelWidth, int pixelHeight, int bitsPerPixel)
{
    mFramesPerSecond = pFramesPerSecond;
    mVideoFileName = videoFileName;

    CoInitialize(0);

    if (FAILED(WMCreateProfileManager(&mWMProfileManager)))
    {
        setLastErrorMessage("Unable to create a WMProfileManager");
        close();
        return false;
    }

    IWMProfileManager2 *wmProfileManager = 0;

    if (FAILED(mWMProfileManager->QueryInterface(IID_IWMProfileManager2, (void**) &wmProfileManager)))
    {
        setLastErrorMessage("Unable to query the WMProfileManager for interface WMProfileManager2");
        close();
        return false;
    }

    HRESULT hr = wmProfileManager->SetSystemProfileVersion(WMT_VER_9_0);
    wmProfileManager->Release();

    if (FAILED(hr))
    {
        setLastErrorMessage("Unable to set WMProfileManager SystemProfileVersion");
        close();
        return false;
    }

    if (FAILED(mWMProfileManager->LoadProfileByData((LPCTSTR) profileData.utf16(), &mWMProfile)))
    {
        setLastErrorMessage("Unable to load WMProfileManager custom profile");
        close();
        return false;
    }

    DWORD streamCount = -1;

    if (FAILED(mWMProfile->GetStreamCount(&streamCount)))
    {
        setLastErrorMessage("Unable to read mWMProfile stream count");
        close();
        return false;
    }

    if (FAILED(WMCreateWriter(NULL, &mWMWriter)))
    {
        setLastErrorMessage("Unable to create WMMediaWriter Object");
        close();
        return false;
    }

    if (FAILED(mWMWriter->SetProfile(mWMProfile)))
    {
        setLastErrorMessage("Unable to set WMWriter system profile");
        close();
        return false;
    }

    DWORD mediaInputCount = 0;

    if (FAILED(mWMWriter->GetInputCount(&mediaInputCount)))
    {
        setLastErrorMessage("Unable to get input count for profile");
        close();
        return false;
    }

    for (DWORD i = 0; i < mediaInputCount; i++)
    {
        IWMInputMediaProps* wmInoutMediaProps = 0;

        if (FAILED(mWMWriter->GetInputProps(i, &wmInoutMediaProps)))
        {
            setLastErrorMessage("Unable to get WMWriter input properties");
            close();
            return false;
        }

        GUID guidInputType;

        if (FAILED(wmInoutMediaProps->GetType(&guidInputType)))
        {
            setLastErrorMessage("Unable to get WMWriter input property type");
            close();
            return false;
        }

        if (guidInputType == WMMEDIATYPE_Video)
        {
            mWMInputVideoProps = wmInoutMediaProps;
            mVideoInputIndex = i;
        }
        else if (guidInputType == WMMEDIATYPE_Audio)
        {
            mWMInputAudioProps = wmInoutMediaProps;
            mAudioInputIndex = i;
        }
        else
        {
            wmInoutMediaProps->Release();
            wmInoutMediaProps = 0;
        }
    }

    if (mWMInputVideoProps == 0)
    {
        setLastErrorMessage("Profile does not accept video input");
        close();
        return false;
    }

    if (mWMInputAudioProps == 0)
    {
        setLastErrorMessage("Profile does not accept audio input");
        close();
        return false;
    }

    if (FAILED(mWMWriter->SetOutputFilename((LPCTSTR) videoFileName.utf16())))
    {
        setLastErrorMessage("Unable to set the output filename");
        close();
        return false;
    }

    if(!initVideoStream(pixelWidth, pixelHeight, bitsPerPixel))
    {
        close();
        return false;
    }

    if (FAILED(mWMWriter->BeginWriting()))
    {
        setLastErrorMessage("Unable to initialize video frame writing");
        return false;
    }

    return true;
}