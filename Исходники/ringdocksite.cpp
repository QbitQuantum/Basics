LRESULT RingDockSite::RingdowProc(HWND hWnd,RINGPARAMS param)
{
	switch(param.uMsg)
   {
		case WM_CREATE:
			SetPos(m_rcPos.left,m_rcPos.top);
			SetCursor(m_windowInfo.hCursor);			
			break;
		case WM_COMMAND:			
			if(param.lParam != 0)
				return SendMessage(m_parent->Handle(),param.uMsg,param.wParam,param.lParam);
			else
				return OnDockBarHide(param.wParam);
		case RB_SETBKCOLOR:
			switch(param.wParam)
			{
				case RBIMG_HBITMAP:
					SetBgBmp((HBITMAP)param.lParam);
					return TRUE;
				case RBIMG_IDBMP:
					SetBgBmp((LPCTSTR)param.lParam);
					return TRUE;
				case RBIMG_BKCOLOR:
					SetBgColor(param.lParam);
					return TRUE;
				default:
					return 0;
			}
		case WM_MOVE:
		case WM_SIZE:
			InvalidateRect(m_hWnd,NULL,TRUE);
			return DefaultProc(param);
		case WM_LBUTTONDBLCLK:
			return OnLButtonDbClk(param);
		case WM_LBUTTONDOWN:
			return OnLButtonDown(param);
		case WM_LBUTTONUP:
			return OnLButtonUp(param);
		case WM_MOUSEMOVE:
			return OnMouseMove(param);
		case WM_RBUTTONDOWN:
			return OnRButtonDown(param);
		case WM_NCPAINT:
			return 0;		
		case WM_ERASEBKGND:
			return TRUE;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			DrawSite(BeginPaint(m_hWnd,&ps),param);
			EndPaint(m_hWnd,&ps);
			return 0;
      }
		case WM_NOTIFY:
			switch(param.lpnmhdr->code)
			{
				case TTN_NEEDTEXT:
				{
					((LPTOOLTIPTEXT)param.lParam)->hinst = GetInstance();
					return SendMessage(m_parent->Handle(),WM_RINGTOOLTIP,((LPTOOLTIPTEXT)param.lParam)->hdr.idFrom,param.lParam);
				}
				
				//case TBN_DROPDOWN:
				//工具栏DropDown按钮
				//	return SendMessage(param.lpnmhdr->hwndFrom,param);
			}
			if(IsWindowPtr(m_parent))
				return SendMessage(m_parent->Handle(),param);
			return DefaultProc(param);
	   case WM_CLOSE:
      	Show(SW_HIDE);
         break;
		//case WM_WINDOWPOSCHANGED:
		//	InvalidateRect(m_hWnd,NULL,FALSE);
		//	return 0;
		case WM_MEASUREITEM:
		{
			RingCoolMenu* rm = GetDockMenu();
			if(rm)
				rm->MeasureItem(param.lpmeasureitem);				
			return SendMessage(m_parent->Handle(),param.uMsg,param.wParam,param.lParam);
		}
      case WM_DRAWITEM:
		{
			RingCoolMenu* rm = GetDockMenu();
			if(rm)
				rm->Draw(param.lpdrawitem);			
			return SendMessage(m_parent->Handle(),param.uMsg,param.wParam,param.lParam);
		}
		//case WM_EXITSIZEMOVE:
		//	InvalidateRect(m_hWnd,NULL,TRUE);
		//	break;
		default:
		{	
			LRESULT res = CtlColorProc(hWnd,param);
			if(res != RM_NOTPROCESS)
				return res;
			else
				return RingWnd::DefaultProc(param);
		}
   }
   return 0;
}