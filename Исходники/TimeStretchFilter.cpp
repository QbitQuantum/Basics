// Format negotiation
HRESULT CTimeStretchFilter::NegotiateFormat(const WAVEFORMATEXTENSIBLE* pwfx, int nApplyChangesDepth, ChannelOrder* pChOrder)
{
  if (!pwfx)
    return VFW_E_TYPE_NOT_ACCEPTED;

#ifdef INTEGER_SAMPLES
  // only accept 16bit int
  if (pwfx->Format.wBitsPerSample != 16 || pwfx->SubFormat != KSDATAFORMAT_SUBTYPE_PCM)
    return VFW_E_TYPE_NOT_ACCEPTED;
#else 
  // only accept 32bit float
  if (pwfx->Format.wBitsPerSample != 32 || pwfx->SubFormat != KSDATAFORMAT_SUBTYPE_IEEE_FLOAT)
    return VFW_E_TYPE_NOT_ACCEPTED;
#endif

  if (FormatsEqual(pwfx, m_pInputFormat))
  {
    *pChOrder = m_chOrder;
    return S_OK;
  }

  bool bApplyChanges = (nApplyChangesDepth != 0);
  if (nApplyChangesDepth != INFINITE && nApplyChangesDepth > 0)
    nApplyChangesDepth--;

  HRESULT hr = m_pNextSink->NegotiateFormat(pwfx, nApplyChangesDepth, pChOrder);
  if (FAILED(hr))
    return hr;

  hr = VFW_E_CANNOT_CONNECT;
  
  if (!pwfx)
    return SetFormat(NULL);

  if (bApplyChanges)
  {
    LogWaveFormat(pwfx, "TS   - applying ");

    m_pNextSink->NegotiateBuffer(pwfx, &m_nOutBufferSize, &m_nOutBufferCount, true);

    AM_MEDIA_TYPE tmp;
    HRESULT result = CreateAudioMediaType((WAVEFORMATEX*)pwfx, &tmp, true);
    if (SUCCEEDED(result))
    {
      if (m_pMediaType)
        DeleteMediaType(m_pMediaType);
      m_pMediaType = CreateMediaType(&tmp);
    }

    SetInputFormat(pwfx);
    SetOutputFormat(pwfx);
    SetFormat(pwfx);
  }
  else
    LogWaveFormat(pwfx, "TS   -          ");

  m_bNextFormatPassthru = !m_pSettings->m_bUseTimeStretching;
  m_chOrder = *pChOrder;

  return S_OK;
}