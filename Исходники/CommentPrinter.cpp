 void DrawShita(const Chat &chat) {
     RECT rc;
     rc.top = rcWnd_.bottom - yPitch_ - static_cast<LONG>(chat.line * (int)((float)yPitch_ * CNJIni::GetSettings()->commentLineMargin));
     rc.bottom = rc.top + yPitch_;
     rc.left = 0;
     rc.right = rcWnd_.right;
     int shadow = (yPitch_ / 16);
     if ( yPitch_ > 24 && shadow == 1 ) {
         shadow = 2;
     }
     if ( shadow < 1 ) {
         shadow = 1;
     }
     const std::wstring &text = chat.text;
     SetTextColor(memDC_, RGB(0, 0, 0));
     DrawTextW(memDC_, text.c_str(), text.length(), &rc, DT_CENTER | DT_NOPREFIX);
     OffsetRect(&rc, -shadow, -shadow);
     SetTextColor(memDC_, chat.color);
     DrawTextW(memDC_, text.c_str(), text.length(), &rc, DT_CENTER | DT_NOPREFIX);
 }