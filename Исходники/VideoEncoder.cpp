// 创建sink writer. 返回流索引.
HRESULT VideoEncoder::CreateSinkWriter(IMFSinkWriter** ppSinkWriter, DWORD* pStreamIndex)
{
	HRESULT hr = S_OK;
	if (this->m_outputFile == L"")
	{
		return ERROR_FILE_INVALID;
	}

	// 创建sink writer.
	*ppSinkWriter = nullptr;	
	IMFSinkWriter *pSinkWriter = nullptr;
	IMFMediaType* pOutputMediaType = nullptr;
	IMFMediaType *pInMediaType = nullptr;   
	CheckHR(MFCreateSinkWriterFromURL(this->m_outputFile.c_str(), nullptr, nullptr, &pSinkWriter));

	// 创建和配置输出媒体类型.
	CheckHR(MFCreateMediaType(&pOutputMediaType));
	CheckHR(pOutputMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
	CheckHR(pOutputMediaType->SetGUID(MF_MT_SUBTYPE, this->m_outputVideoFormat));
	CheckHR(pOutputMediaType->SetUINT32(MF_MT_AVG_BITRATE, this->m_videoBitRate));
	CheckHR(pOutputMediaType->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive));

	CheckHR(MFSetAttributeSize(pOutputMediaType, MF_MT_FRAME_SIZE, this->m_frameWidth, this->m_frameHeight));
	CheckHR(MFSetAttributeRatio(pOutputMediaType, MF_MT_FRAME_RATE, (UINT32)this->m_fps, 1));
	CheckHR(MFSetAttributeRatio(pOutputMediaType, MF_MT_PIXEL_ASPECT_RATIO, 1, 1));
	DWORD streamIndex;
	CheckHR(pSinkWriter->AddStream(pOutputMediaType, &streamIndex));

	// 设置输入的媒体类型.
    CheckHR(MFCreateMediaType(&pInMediaType));   
    CheckHR(pInMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));   
    CheckHR(pInMediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB32));     
    CheckHR(pInMediaType->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive)); 

	// 输入的步幅信息不为所有输出编码解码器需要.但某些编解码器需要它，如 H.264.
	// 如果步幅是去掉，或设置为负值，H.264 将从下到上处理图像.
	CheckHR(pInMediaType->SetUINT32(MF_MT_DEFAULT_STRIDE, this->m_frameStride));
    CheckHR(MFSetAttributeSize(pInMediaType, MF_MT_FRAME_SIZE, this->m_frameWidth, this->m_frameHeight));
    CheckHR(MFSetAttributeRatio(pInMediaType, MF_MT_FRAME_RATE, (UINT32)this->m_fps, 1));   
    CheckHR(MFSetAttributeRatio(pInMediaType, MF_MT_PIXEL_ASPECT_RATIO, 1, 1));
    CheckHR(pSinkWriter->SetInputMediaType(streamIndex, pInMediaType, nullptr));   

	// 开始编写.
	CheckHR(pSinkWriter->BeginWriting());

	*ppSinkWriter = pSinkWriter;
	(*ppSinkWriter)->AddRef();
	*pStreamIndex = streamIndex;

cleanup:
	if (!SUCCEEDED(hr))
	{
		DWORD error = GetLastError();
		this->m_logFileStream << "意外错误: " << error << endl;
	}
	SafeRelease(&pSinkWriter);
	SafeRelease(&pOutputMediaType);
	return hr;
}