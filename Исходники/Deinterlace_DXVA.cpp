CDeinterlacer::FrameStatus CDeinterlacer_DXVA::GetFrame(
	CFrameBuffer *pDstBuffer, const CFrameBuffer *pSrcBuffer,
	bool fTopField, int Field)
{
	const int Width = pDstBuffer->m_Width, Height = pDstBuffer->m_Height;

	if (!m_pVideoProcessor || m_Width != Width || m_Height != Height) {
		if (m_fOpenFailed)
			return FRAME_SKIP;
		if (!Open(Width, Height))
			return FRAME_SKIP;
	}

	const size_t TotalSamples = m_BackwardRefSamples + m_ForwardRefSamples + 1;

	if (m_RefSamples.size() == TotalSamples)
		m_RefSamples.pop_front();

	IDirect3DSurface9 *pSurface = GetFreeSurface();
	if (!pSurface) {
		TRACE(TEXT("Unable to find unused surface\n"));
		return FRAME_SKIP;
	}

	HRESULT hr;

	D3DSURFACE_DESC desc;

	hr = pSurface->GetDesc(&desc);
	if (FAILED(hr)) {
		TRACE(TEXT("Failed to get surface desc (%x)\n"), hr);
		return FRAME_SKIP;
	}

	D3DLOCKED_RECT rect;

	hr = pSurface->LockRect(&rect, nullptr, D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK);
	if (FAILED(hr)) {
		TRACE(TEXT("Failed to lock surface (%x)\n"), hr);
		return FRAME_SKIP;
	}

	PixelCopyI420ToNV12(
		Width, Height,
		(uint8_t*)rect.pBits, (uint8_t*)rect.pBits + desc.Height * rect.Pitch, rect.Pitch,
		pSrcBuffer->m_Buffer[0], pSrcBuffer->m_Buffer[1], pSrcBuffer->m_Buffer[2],
		pSrcBuffer->m_PitchY, pSrcBuffer->m_PitchC);

	pSurface->UnlockRect();

	SampleInfo Sample;
	Sample.pSurface = pSurface;
	Sample.StartTime = pDstBuffer->m_rtStart;
	Sample.EndTime = pDstBuffer->m_rtStop;
	Sample.fTopFieldFirst = fTopField;
	m_RefSamples.push_back(Sample);

	if (m_RefSamples.size() <= m_ForwardRefSamples)
		return FRAME_SKIP;

	m_FrameNumber++;

	DXVA2_VideoSample Samples[MAX_DEINTERLACE_SURFACES];
	RECT rc = {0, 0, Width, Height};

	ZeroMemory(Samples, sizeof(Samples));

	size_t BackwardSamples = 0;
	if (m_RefSamples.size() > m_ForwardRefSamples + 1)
		BackwardSamples = m_RefSamples.size() - (m_ForwardRefSamples + 1);

	for (size_t i = 0; i < m_RefSamples.size(); i++) {
		DXVA2_VideoSample &vs = Samples[i];

		vs.Start = m_FrameNumber + i - BackwardSamples;
		vs.End = vs.Start + 1;
		vs.SampleFormat = m_VideoDesc.SampleFormat;
		vs.SampleFormat.SampleFormat =
			m_RefSamples[i].fTopFieldFirst ?
				DXVA2_SampleFieldInterleavedEvenFirst :
				DXVA2_SampleFieldInterleavedOddFirst;
		vs.SrcSurface = m_RefSamples[i].pSurface;
		vs.SrcRect = rc;
		vs.DstRect = rc;
		vs.PlanarAlpha = DXVA2_Fixed32OpaqueAlpha();
	}

	DXVA2_VideoProcessBltParams blt = {};

	blt.TargetFrame = m_FrameNumber;
	blt.TargetRect = rc;
	blt.BackgroundColor.Y     = 0x1000;
	blt.BackgroundColor.Cb    = 0x8000;
	blt.BackgroundColor.Cr    = 0x8000;
	blt.BackgroundColor.Alpha = 0xffff;
	blt.DestFormat.SampleFormat = DXVA2_SampleProgressiveFrame;
	blt.DestFormat.NominalRange = m_VideoDesc.SampleFormat.NominalRange;
	blt.DestFormat.VideoTransferFunction = DXVA2_VideoTransFunc_sRGB;
	blt.ProcAmpValues.Brightness = m_ProcAmpBrightness.DefaultValue;
	blt.ProcAmpValues.Contrast = m_ProcAmpContrast.DefaultValue;
	blt.ProcAmpValues.Hue = m_ProcAmpHue.DefaultValue;
	blt.ProcAmpValues.Saturation = m_ProcAmpSaturation.DefaultValue;
	blt.Alpha = DXVA2_Fixed32OpaqueAlpha();
	blt.NoiseFilterLuma = m_NoiseFilterLuma;
	blt.NoiseFilterChroma = m_NoiseFilterChroma;
	blt.DetailFilterLuma = m_DetailFilterLuma;
	blt.DetailFilterChroma = m_DetailFilterChroma;

	pSurface = m_Surfaces.front();

	hr = m_pVideoProcessor->VideoProcessBlt(pSurface, &blt, Samples, (UINT)m_RefSamples.size(), nullptr);
	if (FAILED(hr)) {
		TRACE(TEXT("VideoProcessBlt() failed (%x)\n"), hr);
		return FRAME_SKIP;
	}

	if (pDstBuffer->m_pSurface) {
		D3DSURFACE_DESC descSrc, descDst;
		D3DLOCKED_RECT rectSrc, rectDst;

		hr = pSurface->GetDesc(&descSrc);
		if (FAILED(hr)) {
			TRACE(TEXT("Failed to get surface desc (%x)\n"), hr);
			return FRAME_SKIP;
		}

		hr = pDstBuffer->m_pSurface->GetDesc(&descDst);
		if (FAILED(hr)) {
			TRACE(TEXT("Failed to get surface desc (%x)\n"), hr);
			return FRAME_SKIP;
		}

		hr = pSurface->LockRect(&rectSrc, nullptr, D3DLOCK_READONLY | D3DLOCK_NOSYSLOCK);
		if (FAILED(hr)) {
			TRACE(TEXT("Failed to lock surface (%x)\n"), hr);
			return FRAME_SKIP;
		}

		hr = pDstBuffer->m_pSurface->LockRect(&rectDst, nullptr, D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK);
		if (FAILED(hr)) {
			TRACE(TEXT("Failed to lock surface (%x)\n"), hr);
			pSurface->UnlockRect();
			return FRAME_SKIP;
		}

		PixelCopyNV12ToNV12(
			Width, Height,
			(uint8_t*)rectDst.pBits, (uint8_t*)rectDst.pBits + descDst.Height * rectDst.Pitch, rectDst.Pitch,
			(const uint8_t*)rectSrc.pBits, (const uint8_t*)rectSrc.pBits + descSrc.Height * rectSrc.Pitch, rectSrc.Pitch);

		pDstBuffer->m_pSurface->UnlockRect();
		pSurface->UnlockRect();
	} else {
		hr = pSurface->GetDesc(&desc);
		if (FAILED(hr)) {
			TRACE(TEXT("Failed to get surface desc (%x)\n"), hr);
			return FRAME_SKIP;
		}

		hr = pSurface->LockRect(&rect, nullptr, D3DLOCK_READONLY | D3DLOCK_NOSYSLOCK);
		if (FAILED(hr)) {
			TRACE(TEXT("Failed to lock surface (%x)\n"), hr);
			return FRAME_SKIP;
		}

#if 0
		PixelCopyNV12ToI420(
			Width, Height,
			pDstBuffer->m_Buffer[0], pDstBuffer->m_Buffer[1], pDstBuffer->m_Buffer[2],
			pDstBuffer->m_PitchY, pDstBuffer->m_PitchC,
			(const uint8_t*)rect.pBits, (const uint8_t*)rect.pBits + desc.Height * rect.Pitch, rect.Pitch);
#else
		PixelCopyNV12ToNV12(
			Width, Height,
			pDstBuffer->m_Buffer[0], pDstBuffer->m_Buffer[1], pDstBuffer->m_PitchY,
			(const uint8_t*)rect.pBits, (const uint8_t*)rect.pBits + desc.Height * rect.Pitch, rect.Pitch);
		pDstBuffer->m_Subtype = MEDIASUBTYPE_NV12;
#endif

		pSurface->UnlockRect();
	}

	const SampleInfo *pSample = &m_RefSamples[m_RefSamples.size() - 1 - m_ForwardRefSamples];
	pDstBuffer->m_rtStart = pSample->StartTime;
	pDstBuffer->m_rtStop = pSample->EndTime;

	return FRAME_OK;
}