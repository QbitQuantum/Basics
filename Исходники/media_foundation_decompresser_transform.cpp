std::unique_ptr<MediaFoundation_DecompresserTransform> MediaFoundation_DecompresserTransform::getInstance(int width, int height, PixelFormat inputPixelFormat, PixelFormat outputPixelFormat, RESULT &result)
{
    CComPtr<IMFTransform> transform;

    GUID inputSubtype;
    bool ok = MediaFoundation_Utils::pixelFormatToVideoFormat(inputPixelFormat, inputSubtype);
    if (!ok) {
        result = RESULT::UNSUPPORTED_INPUT;
        return nullptr;
    }

    GUID outputSubtype;
    ok = MediaFoundation_Utils::pixelFormatToVideoFormat(outputPixelFormat, outputSubtype);
    if (!ok) {
        result = RESULT::UNSUPPORTED_OUTPUT_FOR_INPUT;
        return nullptr;
    }

    MFT_REGISTER_TYPE_INFO inputFilter = {MFMediaType_Video, inputSubtype};
    MFT_REGISTER_TYPE_INFO outputFilter = {MFMediaType_Video, outputSubtype};

    IMFActivate **activateArr;
    UINT32 activateCount;

    // TODO(nurupo): maybe prioritize hardware decoders first?
    HRESULT hr = MFTEnumEx(MFT_CATEGORY_VIDEO_DECODER, MFT_ENUM_FLAG_ALL, &inputFilter, &outputFilter, &activateArr, &activateCount);
    if (FAILED(hr) || activateCount < 1) {
        DEBUG_PRINT_HR_ERROR("Couldn't find an appropriate transform.", hr);
        CoTaskMemFree(activateArr);

        // check whether it's RESULT::UNSUPPORTED_INPUT or RESULT::UNSUPPORTED_OUTPUT_FOR_INPUT
        hr = MFTEnumEx(MFT_CATEGORY_VIDEO_DECODER, MFT_ENUM_FLAG_ALL, &inputFilter, nullptr, &activateArr, &activateCount);
        if (FAILED(hr) || activateCount < 1) {
            // there is no transform for such input
            result = RESULT::UNSUPPORTED_INPUT;
        } else {
            // there is some transform for this input, but not this output
            for (UINT32 i = 0; i < activateCount; i ++) {
                activateArr[i]->Release();
            }
            result = RESULT::UNSUPPORTED_OUTPUT_FOR_INPUT;
        }
        CoTaskMemFree(activateArr);

        return nullptr;
    }

    // release all but 1st transform
    for (UINT32 i = 1; i < activateCount; i ++) {
        activateArr[i]->Release();
    }

    // Activate 1st transform
    IMFActivate *activate = activateArr[0];
    CoTaskMemFree(activateArr);
    hr = activate->ActivateObject(IID_PPV_ARGS(&transform));
    if (FAILED(hr)) {
        DEBUG_PRINT_HR_ERROR("Couldn't activate a transform.", hr);
        activate->Release();
        result = RESULT::FAILURE;
        return nullptr;
    }

    std::unique_ptr<MediaFoundation_PixelFormatTransform> pixelFormatTransform = MediaFoundation_PixelFormatTransform::getInstance(transform, width, height, inputPixelFormat, outputPixelFormat, result);

    if (result != RESULT::OK) {
        activate->ShutdownObject();
        return nullptr;
    }

    result = RESULT::OK;

    return std::unique_ptr<MediaFoundation_DecompresserTransform>(new MediaFoundation_DecompresserTransform(pixelFormatTransform, activate));
}