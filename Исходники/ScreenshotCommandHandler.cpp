  HRESULT ScreenshotCommandHandler::GetBase64Data(std::string& data) {
    LOG(TRACE) << "Entering ScreenshotCommandHandler::GetBase64Data";

    if (this->image_ == NULL) {
      LOG(DEBUG) << "CImage was not initialized.";
      return E_POINTER;
    }

    CComPtr<IStream> stream;
    HRESULT hr = ::CreateStreamOnHGlobal(NULL, TRUE, &stream);
    if (FAILED(hr)) {
      LOGHR(WARN, hr) << "Error is occured during creating IStream";
      return hr;
    }

    GUID image_format = Gdiplus::ImageFormatPNG /*Gdiplus::ImageFormatJPEG*/;
    hr = this->image_->Save(stream, image_format);
    if (FAILED(hr)) {
      LOGHR(WARN, hr) << "Saving screenshot image is failed";
      return hr;
    }

    // Get the size of the stream.
    STATSTG statstg;
    hr = stream->Stat(&statstg, STATFLAG_DEFAULT);
    if (FAILED(hr)) {
      LOGHR(WARN, hr) << "No stat on stream is got";
      return hr;
    }

    HGLOBAL global_memory_handle = NULL;
    hr = ::GetHGlobalFromStream(stream, &global_memory_handle);
    if (FAILED(hr)) {
      LOGHR(WARN, hr) << "No HGlobal in stream";
      return hr;
    }

    // TODO: What if the file is bigger than max_int?
    int stream_size = static_cast<int>(statstg.cbSize.QuadPart);
    LOG(DEBUG) << "Size of screenshot image stream is " << stream_size;

    int length = ::Base64EncodeGetRequiredLength(stream_size, ATL_BASE64_FLAG_NOCRLF);
    if (length <= 0) {
      LOG(WARN) << "Got zero or negative length from base64 required length";
      return E_FAIL;
    }

    BYTE* global_lock = reinterpret_cast<BYTE*>(::GlobalLock(global_memory_handle));
    if (global_lock == NULL) {
      LOGERR(WARN) << "Unable to lock memory for base64 encoding";
      ::GlobalUnlock(global_memory_handle);      
      return E_FAIL;
    }

    char* data_array = new char[length + 1];
    if (!::Base64Encode(global_lock,
                        stream_size,
                        data_array,
                        &length,
                        ATL_BASE64_FLAG_NOCRLF)) {
      delete[] data_array;
      ::GlobalUnlock(global_memory_handle);
      LOG(WARN) << "Unable to encode image stream to base64";
      return E_FAIL;
    }
    data_array[length] = '\0';
    data = data_array;

    delete[] data_array;
    ::GlobalUnlock(global_memory_handle);

    return S_OK;
  }