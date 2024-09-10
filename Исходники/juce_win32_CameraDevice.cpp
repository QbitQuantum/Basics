    bool createFileCaptureFilter (const File& file, int quality)
    {
        removeFileCaptureFilter();
        file.deleteFile();
        mediaControl->Stop();
        firstRecordedTime = Time();
        recordNextFrameTime = true;
        previewMaxFPS = 60;

        HRESULT hr = asfWriter.CoCreateInstance (CLSID_WMAsfWriter);

        if (SUCCEEDED (hr))
        {
            ComSmartPtr <IFileSinkFilter> fileSink;
            hr = asfWriter.QueryInterface (fileSink);

            if (SUCCEEDED (hr))
            {
                hr = fileSink->SetFileName (file.getFullPathName().toWideCharPointer(), 0);

                if (SUCCEEDED (hr))
                {
                    hr = graphBuilder->AddFilter (asfWriter, _T("AsfWriter"));

                    if (SUCCEEDED (hr))
                    {
                        ComSmartPtr <IConfigAsfWriter> asfConfig;
                        hr = asfWriter.QueryInterface (asfConfig);
                        asfConfig->SetIndexMode (true);
                        ComSmartPtr <IWMProfileManager> profileManager;
                        hr = WMCreateProfileManager (profileManager.resetAndGetPointerAddress());

                        // This gibberish is the DirectShow profile for a video-only wmv file.
                        String prof ("<profile version=\"589824\" storageformat=\"1\" name=\"Quality\" description=\"Quality type for output.\">"
                                       "<streamconfig majortype=\"{73646976-0000-0010-8000-00AA00389B71}\" streamnumber=\"1\" "
                                                     "streamname=\"Video Stream\" inputname=\"Video409\" bitrate=\"894960\" "
                                                     "bufferwindow=\"0\" reliabletransport=\"1\" decodercomplexity=\"AU\" rfc1766langid=\"en-us\">"
                                         "<videomediaprops maxkeyframespacing=\"50000000\" quality=\"90\"/>"
                                         "<wmmediatype subtype=\"{33564D57-0000-0010-8000-00AA00389B71}\" bfixedsizesamples=\"0\" "
                                                      "btemporalcompression=\"1\" lsamplesize=\"0\">"
                                         "<videoinfoheader dwbitrate=\"894960\" dwbiterrorrate=\"0\" avgtimeperframe=\"$AVGTIMEPERFRAME\">"
                                             "<rcsource left=\"0\" top=\"0\" right=\"$WIDTH\" bottom=\"$HEIGHT\"/>"
                                             "<rctarget left=\"0\" top=\"0\" right=\"$WIDTH\" bottom=\"$HEIGHT\"/>"
                                             "<bitmapinfoheader biwidth=\"$WIDTH\" biheight=\"$HEIGHT\" biplanes=\"1\" bibitcount=\"24\" "
                                                               "bicompression=\"WMV3\" bisizeimage=\"0\" bixpelspermeter=\"0\" biypelspermeter=\"0\" "
                                                               "biclrused=\"0\" biclrimportant=\"0\"/>"
                                           "</videoinfoheader>"
                                         "</wmmediatype>"
                                       "</streamconfig>"
                                     "</profile>");

                        const int fps[] = { 10, 15, 30 };
                        int maxFramesPerSecond = fps [jlimit (0, numElementsInArray (fps) - 1, quality & 0xff)];

                        if ((quality & 0xff000000) != 0) // (internal hacky way to pass explicit frame rates for testing)
                            maxFramesPerSecond = (quality >> 24) & 0xff;

                        prof = prof.replace ("$WIDTH", String (width))
                                   .replace ("$HEIGHT", String (height))
                                   .replace ("$AVGTIMEPERFRAME", String (10000000 / maxFramesPerSecond));

                        ComSmartPtr <IWMProfile> currentProfile;
                        hr = profileManager->LoadProfileByData (prof.toWideCharPointer(), currentProfile.resetAndGetPointerAddress());
                        hr = asfConfig->ConfigureFilterUsingProfile (currentProfile);

                        if (SUCCEEDED (hr))
                        {
                            ComSmartPtr <IPin> asfWriterInputPin;

                            if (getPin (asfWriter, PINDIR_INPUT, asfWriterInputPin, "Video Input 01"))
                            {
                                hr = graphBuilder->Connect (smartTeeCaptureOutputPin, asfWriterInputPin);

                                if (SUCCEEDED (hr) && ok && activeUsers > 0
                                     && SUCCEEDED (mediaControl->Run()))
                                {
                                    previewMaxFPS = (quality < 2) ? 15 : 25; // throttle back the preview comps to try to leave the cpu free for encoding

                                    if ((quality & 0x00ff0000) != 0)  // (internal hacky way to pass explicit frame rates for testing)
                                        previewMaxFPS = (quality >> 16) & 0xff;

                                    return true;
                                }
                            }
                        }
                    }
                }
            }