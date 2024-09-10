HRESULT CAudioDecFilter::Transform(IMediaSample *pIn, IMediaSample *pOut)
{
	// 入力データポインタを取得する
	const DWORD InSize = pIn->GetActualDataLength();
	BYTE *pInData = NULL;
	HRESULT hr = pIn->GetPointer(&pInData);
	if (FAILED(hr))
		return hr;

	{
		CAutoLock Lock(&m_cPropLock);

		/*
			複数の音声フォーマットに対応する場合、この辺りでフォーマットの判定をする
		*/
		if (!m_pDecoder) {
			m_pDecoder = new CAacDecoder();
			m_pDecoder->Open();
		}

		REFERENCE_TIME rtStart, rtEnd;
		hr = pIn->GetTime(&rtStart, &rtEnd);
		if (FAILED(hr))
			rtStart = -1;
		if (pIn->IsDiscontinuity() == S_OK) {
			m_bDiscontinuity = true;
			m_bInputDiscontinuity = true;
		} else if (hr == S_OK || hr == VFW_S_NO_STOP_TIME) {
			if (!m_bJitterCorrection) {
				m_StartTime = rtStart;
			} else if (m_StartTime >= 0
					&& _abs64(rtStart - m_StartTime) > MAX_JITTER) {
				TRACE(TEXT("Resync audio stream time (%lld -> %lld [%f])\n"),
					  m_StartTime, rtStart,
					  (double)(rtStart - m_StartTime) / (double)REFERENCE_TIME_SECOND);
				m_StartTime = rtStart;
			}
		}
		if (m_StartTime < 0 || m_bDiscontinuity) {
			TRACE(TEXT("Initialize audio stream time (%lld)\n"), rtStart);
			m_StartTime = rtStart;
		}

		m_BitRateCalculator.Update(InSize);
	}

	DWORD InDataPos = 0;
	FrameSampleInfo SampleInfo;
	SampleInfo.pData = &m_OutData;

	hr = S_OK;

	while (InDataPos < InSize) {
		{
			CAutoLock Lock(&m_cPropLock);

			CAudioDecoder::DecodeFrameInfo FrameInfo;
			const DWORD DataSize = InSize - InDataPos;
			DWORD DecodeSize = DataSize;
			if (!m_pDecoder->Decode(&pInData[InDataPos], &DecodeSize, &FrameInfo)) {
				if (DecodeSize < DataSize) {
					InDataPos += DecodeSize;
					continue;
				}
				break;
			}
			InDataPos += DecodeSize;

			if (FrameInfo.bDiscontinuity)
				m_bDiscontinuity = true;

			SampleInfo.bMediaTypeChanged = false;

			hr = OnFrame(FrameInfo.pData, FrameInfo.Samples, FrameInfo.Info,
						 &SampleInfo);
		}

		if (SUCCEEDED(hr)) {
			if (SampleInfo.bMediaTypeChanged) {
				hr = ReconnectOutput(SampleInfo.MediaBufferSize, SampleInfo.MediaType);
				if (FAILED(hr))
					break;
				OutputLog(TEXT("出力メディアタイプを更新します。\r\n"));
				hr = m_pOutput->SetMediaType(&SampleInfo.MediaType);
				if (FAILED(hr)) {
					OutputLog(TEXT("出力メディアタイプを設定できません。(%08x)\r\n"), hr);
					break;
				}
				m_MediaType = SampleInfo.MediaType;
				m_bDiscontinuity = true;
				m_bInputDiscontinuity = true;
			}

			IMediaSample *pOutSample = NULL;
			hr = m_pOutput->GetDeliveryBuffer(&pOutSample, NULL, NULL, 0);
			if (FAILED(hr)) {
				OutputLog(TEXT("出力メディアサンプルを取得できません。(%08x)\r\n"), hr);
				break;
			}

			if (SampleInfo.bMediaTypeChanged)
				pOutSample->SetMediaType(&m_MediaType);

			// 出力ポインタ取得
			BYTE *pOutBuff = NULL;
			hr = pOutSample->GetPointer(&pOutBuff);
			if (FAILED(hr)) {
				OutputLog(TEXT("出力サンプルのバッファを取得できません。(%08x)\r\n"), hr);
				pOutSample->Release();
				break;
			}

			::CopyMemory(pOutBuff, m_OutData.GetData(), m_OutData.GetSize());
			pOutSample->SetActualDataLength(m_OutData.GetSize());

			if (m_StartTime >= 0) {
				REFERENCE_TIME rtDuration, rtStart, rtEnd;
				rtDuration = REFERENCE_TIME_SECOND * (LONGLONG)SampleInfo.Samples / FREQUENCY;
				rtStart = m_StartTime;
				m_StartTime += rtDuration;
				// 音ずれ補正用時間シフト
				if (m_DelayAdjustment > 0) {
					// 最大2倍まで時間を遅らせる
					if (rtDuration >= m_DelayAdjustment) {
						rtDuration += m_DelayAdjustment;
						m_DelayAdjustment = 0;
					} else {
						m_DelayAdjustment -= rtDuration;
						rtDuration *= 2;
					}
				} else if (m_DelayAdjustment < 0) {
					// 最短1/2まで時間を早める
					if (rtDuration >= -m_DelayAdjustment * 2) {
						rtDuration += m_DelayAdjustment;
						m_DelayAdjustment = 0;
					} else {
						m_DelayAdjustment += rtDuration;
						rtDuration /= 2;
					}
				} else {
					rtStart += m_Delay;
				}
				rtEnd = rtStart + rtDuration;
				pOutSample->SetTime(&rtStart, &rtEnd);
			}
			pOutSample->SetMediaTime(NULL, NULL);
			pOutSample->SetPreroll(FALSE);
#if 0
			// Discontinuityを設定すると倍速再生がおかしくなる模様
			pOutSample->SetDiscontinuity(m_bDiscontinuity);
#else
			pOutSample->SetDiscontinuity(m_bInputDiscontinuity);
#endif
			m_bDiscontinuity = false;
			m_bInputDiscontinuity = false;
			pOutSample->SetSyncPoint(TRUE);

			hr = m_pOutput->Deliver(pOutSample);
#ifdef _DEBUG
			if (FAILED(hr)) {
				OutputLog(TEXT("サンプルを送信できません。(%08x)\r\n"), hr);
				if (m_bPassthrough && !m_bPassthroughError) {
					m_bPassthroughError = true;
					if (m_pEventHandler)
						m_pEventHandler->OnSpdifPassthroughError(hr);
				}
			}
#endif
			pOutSample->Release();
			if (FAILED(hr))
				break;
		}
	}

	return hr;
}