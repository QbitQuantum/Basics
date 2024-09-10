// WaveformViewDialog message handlers
void WaveformViewDialog::OnPaint() {
  BufferredPaintDC dc(this);
  
  CRect rectTitle;
  GetDlgItem(IDC_PLACE_CAPTION)->GetWindowRect(&rectTitle);
  ScreenToClient(&rectTitle);
  dc.FillSolidRect(rectTitle, RGB(54, 133, 214));

  CRect waveformRect;
  GetDlgItem(IDC_PLACE_WAVEFORM)->GetWindowRect(&waveformRect);
  ScreenToClient(&waveformRect);
  dc.FillSolidRect(waveformRect, RGB(0, 0, 0));

  CFont *oldFont = dc.SelectObject(GuiResources::GetInstance()->GetFont(GuiResources::FONT_NORMAL));
  dc.SetTextColor(RGB(255, 255, 255));
  dc.SetBkMode(TRANSPARENT);
  CSize textSize = dc.GetTextExtent(_T("88888"));
  waveformRect.left += textSize.cx + 8;

  if (monitor_ != NULL && cashIndex_ != -1) {
    int cashCount = monitor_->Freeze();
    if (cashIndex_ < cashCount) {
      Cash *cash = monitor_->GetCash(cashIndex_);
      CPen penYellow(PS_SOLID, 1, RGB(255, 255, 0));
      CPen penGreen(PS_SOLID, 1, RGB(0, 255, 0));
      int count = cash->GetADCSampleCount(g_ADCChannels[channel_].id);      
      if (count > 0) {
        CString title;
        title.Format(_T("%s - %s"), (LPCTSTR)CA2T(cash->GetSN()), g_ADCChannels[channel_].name);
        labelTitle_.SetWindowText(title);

        const short *codes = cash->GetADCSampleCodes(g_ADCChannels[channel_].id);
        const short *values = cash->GetADCSampleValues(g_ADCChannels[channel_].id);
        
        // draw scaler
        __int64 sum = 0;
        short minValue = SHORT_MAX, maxValue = SHORT_MIN;
        for (int i = 0; i < count; i++) {
          if (values[i] < minValue) {
            minValue = values[i];
          }
          if (values[i] > maxValue) {
            maxValue = values[i];
          }
          sum += values[i];
        }
        CPen whitePen(PS_SOLID, 1, RGB(255, 255, 255));
        CPen *oldPen = dc.SelectObject(&whitePen);
        dc.MoveTo(waveformRect.left, waveformRect.top);
        dc.LineTo(waveformRect.left, waveformRect.bottom);
        
        int height = waveformRect.Height();
        int range = g_ADCChannels[channel_].maxValue - g_ADCChannels[channel_].minValue;
        // min
        CString label;
        int x = waveformRect.left - textSize.cx - 8;
        int y = waveformRect.bottom - (minValue - g_ADCChannels[channel_].minValue) * height / range;
        dc.MoveTo(waveformRect.left - 4, y);
        dc.LineTo(waveformRect.right, y);
        label.Format(_T("%d"), minValue);
        dc.TextOut(x, y - textSize.cy / 2, label);
        // center
        short median = (short)(sum / count);
        y = waveformRect.bottom - (median - g_ADCChannels[channel_].minValue) * height / range;
        dc.MoveTo(waveformRect.left - 4, y);
        dc.LineTo(waveformRect.right, y);
        label.Format(_T("%d"), median);
        dc.TextOut(x, y - textSize.cy / 2, label);
        // max
        y = waveformRect.bottom - (maxValue - g_ADCChannels[channel_].minValue) * height / range;
        dc.MoveTo(waveformRect.left - 4, y);
        dc.LineTo(waveformRect.right, y);
        label.Format(_T("%d"), maxValue);
        dc.TextOut(x, y - textSize.cy / 2, label);

        dc.SelectObject(oldPen);

        ::DrawWaveform(&dc, waveformRect, codes, codes[0], codes[count - 1], count, &penYellow);
        ::DrawWaveform(&dc, waveformRect, values, 
            g_ADCChannels[channel_].minValue, 
            g_ADCChannels[channel_].maxValue, count, &penGreen);
      }
    }
    monitor_->Unfreeze();
  }

  dc.SelectObject(oldFont);
}