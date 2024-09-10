INT_PTR CLAVSplitterSettingsProp::OnReceiveMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    // Mark the page dirty if the text changed
    if(HIWORD(wParam) == EN_CHANGE
      && (LOWORD(wParam) == IDC_PREF_LANG || LOWORD(wParam) == IDC_PREF_LANG_SUBS)) {

        WCHAR buffer[LANG_BUFFER_SIZE];
        SendDlgItemMessage(m_Dlg, LOWORD(wParam), WM_GETTEXT, LANG_BUFFER_SIZE, (LPARAM)&buffer);

        int dirty = 0;
        WCHAR *source = nullptr;
        if(LOWORD(wParam) == IDC_PREF_LANG) {
          source = m_pszPrefLang;
        } else {
          source = (m_selectedSubMode == LAVSubtitleMode_Advanced) ? m_pszAdvSubConfig : m_pszPrefSubLang;
        }

        if (source) {
          dirty = _wcsicmp(buffer, source);
        } else {
          dirty = (int)wcslen(buffer);
        }

        if(dirty != 0) {
          SetDirty();
        }
    } else if (HIWORD(wParam) == CBN_SELCHANGE && LOWORD(wParam) == IDC_SUBTITLE_MODE) {
      DWORD dwVal = (DWORD)SendDlgItemMessage(m_Dlg, IDC_SUBTITLE_MODE, CB_GETCURSEL, 0, 0);
      UpdateSubtitleMode((LAVSubtitleMode)dwVal);
      if (dwVal != m_subtitleMode) {
        SetDirty();
      }
    } else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_BD_SEPARATE_FORCED_SUBS) {
      BOOL bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_BD_SEPARATE_FORCED_SUBS, BM_GETCHECK, 0, 0);
      if (bFlag != m_PGSForcedStream) {
        SetDirty();
      }
    } else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_BD_ONLY_FORCED_SUBS) {
      BOOL bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_BD_ONLY_FORCED_SUBS, BM_GETCHECK, 0, 0);
      if (bFlag != m_PGSOnlyForced) {
        SetDirty();
      }
    } else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_VC1TIMESTAMP) {
      int iFlag = (int)SendDlgItemMessage(m_Dlg, IDC_VC1TIMESTAMP, BM_GETCHECK, 0, 0);
      if (iFlag != m_VC1Mode) {
        SetDirty();
      }
    }  else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_MKV_EXTERNAL) {
      BOOL bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_MKV_EXTERNAL, BM_GETCHECK, 0, 0);
      if (bFlag != m_MKVExternal) {
        SetDirty();
      }
    } else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_SUBSTREAMS) {
      BOOL bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_SUBSTREAMS, BM_GETCHECK, 0, 0);
      if (bFlag != m_substreams) {
        SetDirty();
      }
    } else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_STREAM_SWITCH_REMOVE_AUDIO) {
      BOOL bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_STREAM_SWITCH_REMOVE_AUDIO, BM_GETCHECK, 0, 0);
      if (bFlag != m_StreamSwitchRemoveAudio) {
        SetDirty();
      }
    }  else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_SELECT_AUDIO_QUALITY) {
      BOOL bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_SELECT_AUDIO_QUALITY, BM_GETCHECK, 0, 0);
      if (bFlag != m_PreferHighQualityAudio) {
        SetDirty();
      }
    }  else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_IMPAIRED_AUDIO) {
      BOOL bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_IMPAIRED_AUDIO, BM_GETCHECK, 0, 0);
      if (bFlag != m_ImpairedAudio) {
        SetDirty();
      }
    } else if (HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == IDC_TRAYICON) {
      BOOL bFlag = (BOOL)SendDlgItemMessage(m_Dlg, IDC_TRAYICON, BM_GETCHECK, 0, 0);
      if (bFlag != m_TrayIcon) {
        SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_QUEUE_MEM && HIWORD(wParam) == EN_CHANGE) {
      WCHAR buffer[100];
      SendDlgItemMessage(m_Dlg, LOWORD(wParam), WM_GETTEXT, 100, (LPARAM)&buffer);
      int maxMem = _wtoi(buffer);
      size_t len = wcslen(buffer);
      if (maxMem == 0 && (buffer[0] != L'0' || len > 1)) {
        SendDlgItemMessage(m_Dlg, LOWORD(wParam), EM_UNDO, 0, 0);
      } else {
        swprintf_s(buffer, L"%d", maxMem);
        if (wcslen(buffer) != len)
          SendDlgItemMessage(m_Dlg, IDC_QUEUE_MEM, WM_SETTEXT, 0, (LPARAM)buffer);
        if (maxMem != m_QueueMaxMem)
          SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_QUEUE_PACKETS && HIWORD(wParam) == EN_CHANGE) {
      WCHAR buffer[100];
      SendDlgItemMessage(m_Dlg, LOWORD(wParam), WM_GETTEXT, 100, (LPARAM)&buffer);
      int maxMem = _wtoi(buffer);
      size_t len = wcslen(buffer);
      if (maxMem == 0 && (buffer[0] != L'0' || len > 1)) {
        SendDlgItemMessage(m_Dlg, LOWORD(wParam), EM_UNDO, 0, 0);
      } else {
        swprintf_s(buffer, L"%d", maxMem);
        if (wcslen(buffer) != len)
          SendDlgItemMessage(m_Dlg, IDC_QUEUE_PACKETS, WM_SETTEXT, 0, (LPARAM)buffer);
        if (maxMem != m_QueueMaxPackets)
          SetDirty();
      }
    } else if (LOWORD(wParam) == IDC_STREAM_ANADUR && HIWORD(wParam) == EN_CHANGE) {
      WCHAR buffer[100];
      SendDlgItemMessage(m_Dlg, LOWORD(wParam), WM_GETTEXT, 100, (LPARAM)&buffer);
      int duration = _wtoi(buffer);
      size_t len = wcslen(buffer);
      if (duration == 0 && (buffer[0] != L'0' || len > 1)) {
        SendDlgItemMessage(m_Dlg, LOWORD(wParam), EM_UNDO, 0, 0);
      } else {
        swprintf_s(buffer, L"%d", duration);
        if (wcslen(buffer) != len)
          SendDlgItemMessage(m_Dlg, IDC_STREAM_ANADUR, WM_SETTEXT, 0, (LPARAM)buffer);
        if (duration != m_NetworkAnalysisDuration)
          SetDirty();
      }
    }
    break;
  }
  // Let the parent class handle the message.
  return __super::OnReceiveMessage(hwnd, uMsg, wParam, lParam);
}