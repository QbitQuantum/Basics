HRESULT KinectSpeechRecognizer::CreateRecognizer()
{
    ISpObjectToken *engineToken = NULL;

    //Create singleton instance of Speech Recognizer
    HRESULT hr = CoCreateInstance(CLSID_SpInprocRecognizer, NULL, CLSCTX_INPROC_SERVER, __uuidof(ISpRecognizer), (void**)&speechRecognizer);

    if (SUCCEEDED(hr))
    {
        speechRecognizer->SetInput(speechStream, TRUE);

        // If this fails here, you have not installed the acoustic models for Kinect
        hr = SpFindBestToken(SPCAT_RECOGNIZERS, L"Language=409;Kinect=True", NULL, &engineToken);

        if (SUCCEEDED(hr))
        {
            speechRecognizer->SetRecognizer(engineToken);
            hr = speechRecognizer->CreateRecoContext(&speechContext);

            // For long recognition sessions (a few hours or more), it may be beneficial to turn off adaptation of the acoustic model.
            // This will prevent recognition accuracy from degrading over time.
            if (SUCCEEDED(hr))
            {
                hr = speechRecognizer->SetPropertyNum(L"AdaptationOn", 0);
            }
        }
    }

    //Release the engine token
    if(engineToken)
    {
        engineToken->Release();
        engineToken = NULL;
    }

    return hr;
}