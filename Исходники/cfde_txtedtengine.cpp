int32_t CFDE_TxtEdtEngine::Insert(int32_t nStart,
                                  const FX_WCHAR* lpText,
                                  int32_t nLength) {
  if (IsLocked()) {
    return FDE_TXTEDT_MODIFY_RET_F_Locked;
  }
  CFX_WideString wsTemp;
  FX_WCHAR* lpBuffer = wsTemp.GetBuffer(nLength);
  FXSYS_memcpy(lpBuffer, lpText, nLength * sizeof(FX_WCHAR));
  ReplaceParagEnd(lpBuffer, nLength, FALSE);
  wsTemp.ReleaseBuffer(nLength);
  FX_BOOL bPart = FALSE;
  if (m_nLimit > 0) {
    int32_t nTotalLength = GetTextBufLength();
    int32_t nCount = m_SelRangePtrArr.GetSize();
    for (int32_t i = 0; i < nCount; i++) {
      FDE_TXTEDTSELRANGE* lpSelRange = m_SelRangePtrArr.GetAt(i);
      nTotalLength -= lpSelRange->nCount;
    }
    int32_t nExpectLength = nTotalLength + nLength;
    if (nTotalLength == m_nLimit) {
      return FDE_TXTEDT_MODIFY_RET_F_Full;
    }
    if (nExpectLength > m_nLimit) {
      nLength -= (nExpectLength - m_nLimit);
      bPart = TRUE;
    }
  }
  if ((m_Param.dwMode & FDE_TEXTEDITMODE_LimitArea_Vert) ||
      (m_Param.dwMode & FDE_TEXTEDITMODE_LimitArea_Horz)) {
    int32_t nTemp = nLength;
    if (m_Param.dwMode & FDE_TEXTEDITMODE_Password) {
      CFX_WideString wsText;
      while (nLength > 0) {
        GetPreInsertText(wsText, m_nCaret, lpBuffer, nLength);
        int32_t nTotal = wsText.GetLength();
        FX_WCHAR* lpBuf = wsText.GetBuffer(nTotal);
        for (int32_t i = 0; i < nTotal; i++) {
          lpBuf[i] = m_wcAliasChar;
        }
        wsText.ReleaseBuffer(nTotal);
        if (IsFitArea(wsText)) {
          break;
        }
        nLength--;
      }
    } else {
      CFX_WideString wsText;
      while (nLength > 0) {
        GetPreInsertText(wsText, m_nCaret, lpBuffer, nLength);
        if (IsFitArea(wsText)) {
          break;
        }
        nLength--;
      }
    }
    if (nLength == 0) {
      return FDE_TXTEDT_MODIFY_RET_F_Full;
    }
    if (nLength < nTemp) {
      bPart = TRUE;
    }
  }
  if (m_Param.dwMode & FDE_TEXTEDITMODE_Validate) {
    CFX_WideString wsText;
    GetPreInsertText(wsText, m_nCaret, lpBuffer, nLength);
    if (!m_Param.pEventSink->On_Validate(this, wsText)) {
      return FDE_TXTEDT_MODIFY_RET_F_Invalidate;
    }
  }
  if (IsSelect()) {
    DeleteSelect();
  }
  if (!(m_Param.dwMode & FDE_TEXTEDITMODE_NoRedoUndo))
    m_Param.pEventSink->On_AddDoRecord(
        this,
        new CFDE_TxtEdtDoRecord_Insert(this, m_nCaret, lpBuffer, nLength));

  GetText(m_ChangeInfo.wsPrevText, 0);
  Inner_Insert(m_nCaret, lpBuffer, nLength);
  m_ChangeInfo.nChangeType = FDE_TXTEDT_TEXTCHANGE_TYPE_Insert;
  m_ChangeInfo.wsInsert = CFX_WideString(lpBuffer, nLength);
  nStart = m_nCaret;
  nStart += nLength;
  FX_WCHAR wChar = m_pTxtBuf->GetCharByIndex(nStart - 1);
  FX_BOOL bBefore = TRUE;
  if (wChar != L'\n' && wChar != L'\r') {
    nStart--;
    bBefore = FALSE;
  }
  SetCaretPos(nStart, bBefore);
  m_Param.pEventSink->On_TextChanged(this, m_ChangeInfo);
  return bPart ? FDE_TXTEDT_MODIFY_RET_S_Part : FDE_TXTEDT_MODIFY_RET_S_Normal;
}