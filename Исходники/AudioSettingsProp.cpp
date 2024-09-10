HRESULT CLAVAudioStatusProp::OnActivate()
{
  HRESULT hr = S_OK;
  INITCOMMONCONTROLSEX icc;
  icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icc.dwICC = ICC_STANDARD_CLASSES | ICC_BAR_CLASSES;
  if (InitCommonControlsEx(&icc) == FALSE)
  {
    return E_FAIL;
  }
  ASSERT(m_pAudioStatus != nullptr);

  m_nChannels = 0;

  const char *codec = nullptr;
  const char *decodeFormat = nullptr;
  int nDecodeChannels = 0;
  int nDecodeSampleRate = 0;
  DWORD dwDecodeChannelMask;
  hr = m_pAudioStatus->GetDecodeDetails(&codec, &decodeFormat, &nDecodeChannels, &nDecodeSampleRate, &dwDecodeChannelMask);
  if (SUCCEEDED(hr)) {
    WCHAR buffer[100];
    _snwprintf_s(buffer, _TRUNCATE, L"%d / 0x%x", nDecodeChannels, dwDecodeChannelMask);
    SendDlgItemMessage(m_Dlg, IDC_INPUT_CHANNEL, WM_SETTEXT, 0, (LPARAM)buffer);

    _snwprintf_s(buffer, _TRUNCATE, L"%d", nDecodeSampleRate);
    SendDlgItemMessage(m_Dlg, IDC_INPUT_SAMPLERATE, WM_SETTEXT, 0, (LPARAM)buffer);

    _snwprintf_s(buffer, _TRUNCATE, L"%S", codec);
    SendDlgItemMessage(m_Dlg, IDC_INPUT_CODEC, WM_SETTEXT, 0, (LPARAM)buffer);

    _snwprintf_s(buffer, _TRUNCATE, L"%S", decodeFormat);
    SendDlgItemMessage(m_Dlg, IDC_INPUT_FORMAT, WM_SETTEXT, 0, (LPARAM)buffer);
  }

  const char *outputFormat = nullptr;
  int nOutputChannels = 0;
  int nOutputSampleRate = 0;
  DWORD dwOutputChannelMask = 0;
  hr = m_pAudioStatus->GetOutputDetails(&outputFormat, &nOutputChannels, &nOutputSampleRate, &dwOutputChannelMask);
  if (SUCCEEDED(hr)) {
    WCHAR buffer[100];

    if (hr == S_OK) {
      _snwprintf_s(buffer, _TRUNCATE, L"%d / 0x%x", nOutputChannels, dwOutputChannelMask);
      SendDlgItemMessage(m_Dlg, IDC_OUTPUT_CHANNEL, WM_SETTEXT, 0, (LPARAM)buffer);

      _snwprintf_s(buffer, _TRUNCATE, L"%d", nOutputSampleRate);
      SendDlgItemMessage(m_Dlg, IDC_OUTPUT_SAMPLERATE, WM_SETTEXT, 0, (LPARAM)buffer);

      _snwprintf_s(buffer, _TRUNCATE, L"PCM");
      SendDlgItemMessage(m_Dlg, IDC_OUTPUT_CODEC, WM_SETTEXT, 0, (LPARAM)buffer);

      _snwprintf_s(buffer, _TRUNCATE, L"%S", outputFormat);
      SendDlgItemMessage(m_Dlg, IDC_OUTPUT_FORMAT, WM_SETTEXT, 0, (LPARAM)buffer);

      m_nChannels = nOutputChannels;
    } else {
      _snwprintf_s(buffer, _TRUNCATE, L"Bitstreaming");
      SendDlgItemMessage(m_Dlg, IDC_OUTPUT_CODEC, WM_SETTEXT, 0, (LPARAM)buffer);
    }
  }

  SetTimer(m_Dlg, 1, 250, nullptr);
  m_pAudioStatus->EnableVolumeStats();

  WCHAR chBuffer[5];
  if (dwOutputChannelMask == 0 && nOutputChannels != 0) {
    // 0x4 is only front center, 0x3 is front left+right
    dwOutputChannelMask = nOutputChannels == 1 ? 0x4 : 0x3;
  }
  for(int i = 0; i < MAX_CHANNELS; ++i) {
    SendDlgItemMessage(m_Dlg, iddVolumeControls[i], PBM_SETRANGE, 0, MAKELPARAM(0, 50));
    _snwprintf_s(chBuffer, _TRUNCATE, L"%S", get_channel_desc(get_flag_from_channel(dwOutputChannelMask, i)));
    SendDlgItemMessage(m_Dlg, iddVolumeDescs[i], WM_SETTEXT, 0, (LPARAM)chBuffer);
  }

  return hr;
}