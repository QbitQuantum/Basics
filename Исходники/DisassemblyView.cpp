void DisassemblyView::paintSelection(QPainter& p)
{
  if (m_SelectionBegin == m_SelectionEnd)
    return;

  medusa::UserConfiguration UserCfg;
  QColor slctColor = QColor(QString::fromStdString(UserCfg.GetOption("color.selection")));

  medusa::u32 xSelectBeg, ySelectBeg, xSelectEnd, ySelectEnd;

  if (!_ConvertAddressOffsetToViewOffset(m_SelectionBegin, xSelectBeg, ySelectBeg))
  {
    xSelectBeg = _addrLen;
    ySelectBeg = 0;
  }

  if (static_cast<int>(xSelectBeg) < _addrLen)
    xSelectBeg = _addrLen;

  if (!_ConvertAddressOffsetToViewOffset(m_SelectionEnd, xSelectEnd, ySelectEnd))
    GetDimension(xSelectEnd, ySelectEnd);

  if (static_cast<int>(xSelectEnd) < _addrLen)
    xSelectEnd = _addrLen;

  int begSelect    = ySelectBeg;
  int endSelect    = ySelectEnd;
  int begSelectOff = xSelectBeg;
  int endSelectOff = xSelectEnd;
  int deltaSelect  = endSelect    - begSelect;
  int deltaOffset  = endSelectOff - begSelectOff;

  if (deltaSelect == 0 && deltaOffset == 0)
    return;

  // If the user select from the bottom to the top, we have to swap up and down
  if (deltaSelect < 0)
  {
    deltaSelect  = -deltaSelect;
    std::swap(begSelect, endSelect);
    std::swap(begSelectOff, endSelectOff);
  }

  if (deltaSelect)
    deltaSelect++;

  if (deltaSelect == 0)
  {
    if (deltaOffset < 0)
    {
      deltaOffset = -deltaOffset;
      std::swap(begSelectOff, endSelectOff);
    }
    int x = (begSelectOff - horizontalScrollBar()->value()) * _wChar;
    int y = (begSelect - verticalScrollBar()->value()) * _hChar;
    int w = deltaOffset * _wChar;
    int h = _hChar;
    QRect slctRect(x, y, w, h);
    p.fillRect(slctRect, slctColor);
  }

  // Draw selection background
  // This part is pretty tricky:
  // To draw the selection we use the lazy method by three passes.
  /*
     +-----------------+
     |     ############+ Part¹
     |#################+ Part²
     |#################+ Part²
     |####             | Part³
     +-----------------+
  */
  else if (deltaSelect > 0)
  {
    // Part¹
    int x = (begSelectOff - horizontalScrollBar()->value()) * _wChar;
    int y = (begSelect - verticalScrollBar()->value()) * _hChar;
    int w = (viewport()->width() - _addrLen) * _wChar;
    int h = _hChar;
    QRect slctRect(x, y, w, h);
    p.fillRect(slctRect, slctColor);

    // Part²
    if (deltaSelect > 2)
    {
      x = (_addrLen - horizontalScrollBar()->value()) * _wChar;
      y = slctRect.bottom();
      w = (viewport()->width() - _addrLen) * _wChar;
      h = (deltaSelect - 2) * _hChar;
      slctRect.setRect(x, y, w, h);
      p.fillRect(slctRect, slctColor);
    }

    // Part³
    x = (_addrLen - horizontalScrollBar()->value()) * _wChar;
    y = slctRect.bottom();
    w = (endSelectOff - _addrLen) * _wChar;
    h = _hChar;
    slctRect.setRect(x, y, w, h);
    p.fillRect(slctRect, slctColor);
  }
}