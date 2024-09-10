void CHexViewView::draw(CDC *dc) {
  CHexViewDoc *doc = GetDocument();
  ASSERT_VALID(doc);

  const CRect cr = updateSettings(dc);

  if(m_docSize > 0) {

    const bool    showAddr          = m_settings->getShowAddr();
    const bool    showAscii         = m_settings->getShowAscii();
    const __int64 indexByte0TopLine = m_topLine * m_lineSize;

    ByteArray content;
    doc->getBytes(indexByte0TopLine, m_lineSize * m_pageSize.cy, content);

    const BYTE      *buffer         = content.getData();
    const AddrRange  selection    = getSelection();

    if(showAddr) { // paint headline with offset from leftmost byte address
      dc->FillSolidRect(0, 0, cr.Width(), m_addrTextSize.cy, m_settings->getAddrBackColor());
      setAddrColor(dc, true);
      for(int col = 0, xPos = m_contentRect.left; col < m_lineSize; col++, xPos += m_byteSize.cx) {
        if(xPos > m_contentRect.right) {
          break;
        }
        dc->TextOut(xPos, 0, m_addrFormat.offsetToString(col).cstr());
      }
      setAddrColor(dc, false);
    }

#define OFFSET_LEFTMOSTBYTE(row) ((row)*m_lineSize + m_lineOffset)

    const BYTE *lastByte = &content[content.size()-1];
    setReverseVideo(dc, false);
    for(int row = 0, yPos = m_contentRect.top; yPos <= m_contentRect.bottom; row++, yPos += m_byteSize.cy) {
      const BYTE *bp = buffer + OFFSET_LEFTMOSTBYTE(row);
      if(bp > lastByte) {
        break;
      }
      if(showAddr) {
        setAddrColor(dc, true);
        dc->TextOut(0,yPos, getAddrAsString(indexByte0TopLine + OFFSET_LEFTMOSTBYTE(row)).cstr());
        setAddrColor(dc, false);
      }
      __int64 addr = indexByte0TopLine + OFFSET_LEFTMOSTBYTE(row);
      for(int col = 0, xPos = m_contentRect.left; (col < m_lineSize) && (xPos <= m_contentRect.right) && (bp <= lastByte); col++, xPos += m_byteSize.cx, bp++, addr++) {
        if(!selection.isEmpty()) {
          if(selection.contains(addr)) {
            if(!m_reverseVideo) {
              setReverseVideo(dc, true);
            }
          } else if(m_reverseVideo) {
            setReverseVideo(dc, false);
          }
        }

        TCHAR tmp[40];
        if(showAscii && isprint(*bp)) {
          if(!m_asciiColor) {
            setAsciiColor(dc, true);
          }
          _stprintf(tmp, m_asciiFormat, *bp);
        } else {
          if(m_asciiColor) {
            setAsciiColor(dc, false);
          }
          _stprintf(tmp, m_radixFormat, *bp);
        }
        dc->TextOut(xPos, yPos, tmp);
      }
    }
  }

  showCaret();

  if(m_maxTopLine == 0) { // all bytes shown. hide scrollbar
    ShowScrollBar(SB_VERT, FALSE);
  } else {
    // dont use SetScrollPos as it is only 16-bit int
    ShowScrollBar(SB_VERT, TRUE );

    updateVerticalScrollBar();
  }

  if(m_docSize == 0 || m_maxLineOffset == 0) {
    ShowScrollBar(SB_HORZ, FALSE);
  } else {
    ShowScrollBar(SB_HORZ, TRUE );
    SCROLLINFO scrollInfo;
    GetScrollInfo(SB_HORZ, &scrollInfo);
    scrollInfo.nMin  = 0;
    scrollInfo.nMax  = m_lineSize - 1;
    scrollInfo.nPos  = m_lineOffset;
    scrollInfo.nPage = m_pageSize.cx;
    SetScrollInfo(SB_HORZ, &scrollInfo);
  }
}