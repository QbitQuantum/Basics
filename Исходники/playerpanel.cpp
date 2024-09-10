LRESULT __stdcall PlayerPanel::PlayerButtonProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    case WM_LBUTTONDOWN:
    {
      SetCapture(hWnd);

      /* Show menu */
      if (GetWindowLong(hWnd, GWL_USERDATA) < 2)
      {
        RECT R;
        GetWindowRect(hWnd, &R);
        PostMessage(GetParent(hWnd), WM_CONTEXTMENU, (WPARAM)hWnd, MAKELPARAM(R.left,R.bottom));
      }

      /* Set button status to pressed */
      SetWindowLong(hWnd, GWL_USERDATA, 2);
      InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    }
    case WM_LBUTTONUP:
    {
      ReleaseCapture();

      /* Set button status to hover */
      SetWindowLong(hWnd, GWL_USERDATA, 1);
      InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    }
    case WM_MOUSEMOVE:
    {
      /* Track mouse leave */
      TRACKMOUSEEVENT* Event = new TRACKMOUSEEVENT;
      Event->cbSize = sizeof(TRACKMOUSEEVENT);
      Event->dwFlags = TME_LEAVE;
      Event->hwndTrack = hWnd;
      TrackMouseEvent(Event);

      /* Set button status to hover */
      SetWindowLong(hWnd, GWL_USERDATA, 1);
      InvalidateRect(hWnd, NULL, TRUE);
      return 0;
    }
    case WM_MOUSELEAVE:
    {
      if (GetWindowLong(hWnd, GWL_USERDATA) < 2)
      {
        /* Set button status to none */
        SetWindowLong(hWnd, GWL_USERDATA, 0);
        InvalidateRect(hWnd, NULL, TRUE);
      }
      return 0;
    }
    case WM_PAINT:
    {
      PlayerPanel* Panel = (PlayerPanel*)GetWindowLong(GetParent(hWnd), GWL_USERDATA);

      if (Panel != NULL)
      {
        PAINTSTRUCT PS;
        HDC DC = BeginPaint(hWnd, &PS);
        if (DC != NULL)
        {
          RECT R;
          GetClientRect(hWnd, &R);

          /* Paint the background */
          if (GetWindowLong(hWnd, GWL_USERDATA) == 0)
          {
            /* Plain background */
            HBRUSH OldBrush = (HBRUSH)SelectObject(DC,CreateSolidBrush(GetSysColor(Panel->Game != NULL && Panel->Game->GetActivePlayer() == Panel->Color && Panel->Game->GetState() != Undefined ? COLOR_HIGHLIGHT : COLOR_BTNFACE)));
            HPEN OldPen = (HPEN)SelectObject(DC,CreatePen(PS_SOLID,1,GetSysColor(Panel->Game != NULL && Panel->Game->GetActivePlayer() == Panel->Color && Panel->Game->GetState() != Undefined ? COLOR_HIGHLIGHT : COLOR_BTNFACE)));
            Rectangle(DC,R.top,R.left,R.right-R.left,R.bottom-R.top);
            DeleteObject(SelectObject(DC,OldPen));
            DeleteObject(SelectObject(DC,OldBrush));
          }
          else
          {
            /* Button frame background */
            DRAWITEMSTRUCT* Item = new DRAWITEMSTRUCT;
            Item->hDC = DC;
            Item->itemState = (GetWindowLong(hWnd, GWL_USERDATA) > 1 ? ODS_SELECTED : ODS_DEFAULT);
            Item->rcItem = R;
            DrawCustomButton(hWnd, Item);
            delete Item;
          }

          /* Draw the player's name */
          if (Panel->Game != NULL)
          {
            InflateRect(&R,-5,-1);
            const ChessPlayer* Player = Panel->Game->GetPlayer(Panel->Color);
            SetBkMode(DC,TRANSPARENT);
            SetTextColor(DC, GetSysColor(Panel->Game->GetActivePlayer() == Panel->Color && Panel->Game->GetState() != Undefined && GetWindowLong(hWnd, GWL_USERDATA) == 0 ? COLOR_HIGHLIGHTTEXT : COLOR_BTNTEXT));
            HFONT OldFont = (HFONT)SelectObject(DC,EasyCreateFont(DC,DefaultSystemFont,9,0));
            const char* Text = Player->Name.c_str();
            if (strlen(Text) == 0)
            {
              if (Panel->Color == White)
                Text = "White";
              else
                Text = "Black";
            }
            DrawText(DC,Text,strlen(Text),&R,DT_NOPREFIX|DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_END_ELLIPSIS);
            DeleteObject(SelectObject(DC,OldFont));
          }
        }
        EndPaint(hWnd, &PS);
      }
      return 0;
    }
  }
  return CallWindowProc(OldPlayerButtonProc, hWnd, Msg, wParam, lParam);
}