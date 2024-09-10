BOOL vncDesktop:: CalculateSWrect(RECT &rect)
{

	if (!m_Single_hWnd)
	{
		m_server->SingleWindow(false);
		m_SWtoDesktop=TRUE;
		rect.top=0;
		rect.left=0;
		rect.right=m_scrinfo.framebufferWidth;
		rect.bottom=m_scrinfo.framebufferHeight;
		return FALSE;
	}

	if (IsIconic(m_Single_hWnd))
	{
		m_server->SingleWindow(false);
		m_Single_hWnd=NULL;
		m_SWtoDesktop=TRUE;
		rect.top=0;
		rect.left=0;
		rect.right=m_scrinfo.framebufferWidth;
		rect.bottom=m_scrinfo.framebufferHeight;
		return FALSE;
	}
	if ( IsWindowVisible(m_Single_hWnd) && GetWindowRect(m_Single_hWnd,&rect)) 
		{
			RECT taskbar;
			rect.top=Max(rect.top,0);
			rect.left=Max(rect.left,0);
			rect.right=Min(rect.right,m_scrinfo.framebufferWidth);
			rect.bottom=Min(rect.bottom,m_scrinfo.framebufferHeight);
			APPBARDATA pabd;
			pabd.cbSize=sizeof(APPBARDATA);
			SHAppBarMessage(ABM_GETTASKBARPOS, &pabd);
			taskbar.top=Max(pabd.rc.top,0);
			taskbar.left=Max(pabd.rc.left,0);
			taskbar.right=Min(pabd.rc.right,m_scrinfo.framebufferWidth);
			taskbar.bottom=Min(pabd.rc.bottom,m_scrinfo.framebufferHeight);
			///desktop
			if (rect.top==0 && rect.left== 0&& rect.right==m_scrinfo.framebufferWidth && rect.bottom==m_scrinfo.framebufferHeight)
				{
					m_server->SingleWindow(false);
					m_Single_hWnd=NULL;
					rect.top=0;
					rect.left=0;
					rect.right=m_scrinfo.framebufferWidth;
					rect.bottom=m_scrinfo.framebufferHeight;
					return TRUE;
				}
			//taskbar
			if (rect.top>=taskbar.top && rect.left== taskbar.left&& rect.right==taskbar.right && rect.bottom==taskbar.bottom)
			
				{
					rect.top=taskbar.top;
					rect.left=taskbar.left;
					rect.right=taskbar.right;
					rect.bottom=taskbar.bottom;
					if ((m_SWHeight!=(rect.bottom-rect.top)) || (m_SWWidth!=(rect.right-rect.left)))
					m_SWSizeChanged=TRUE;
					m_SWHeight=rect.bottom-rect.top;
					m_SWWidth=rect.right-rect.left;
					return TRUE;	
				}
			//eliminate other little windows
			if ((m_SWHeight!=(rect.bottom-rect.top)) || (m_SWWidth!=(rect.right-rect.left)))
				m_SWSizeChanged=TRUE;
			//vnclog.Print(LL_INTINFO, VNCLOG("screen format %d %d %d %d\n"),
			//		rect.top,
			//		rect.bottom,rect.right,rect.left);
			if ((rect.bottom-rect.top)<64||(rect.right-rect.left)<128 || rect.bottom<0 ||rect.top<0 || rect.right<0 ||
				rect.left<0 || rect.bottom>m_scrinfo.framebufferHeight||rect.top>m_scrinfo.framebufferHeight||
				rect.right>m_scrinfo.framebufferWidth||rect.left>m_scrinfo.framebufferWidth)
			{
				m_server->SingleWindow(false);
				m_Single_hWnd=NULL;
				m_SWtoDesktop=TRUE;
				rect.top=0;
				rect.left=0;
				rect.right=m_scrinfo.framebufferWidth;
				rect.bottom=m_scrinfo.framebufferHeight;
				m_SWSizeChanged=FALSE;
				return FALSE;
			}


			m_SWHeight=rect.bottom-rect.top;
			m_SWWidth=rect.right-rect.left;
			return TRUE;
		}		
	m_server->SingleWindow(false);
	m_Single_hWnd=NULL;
	m_SWtoDesktop=TRUE;
	rect.top=0;
	rect.left=0;
	rect.right=m_scrinfo.framebufferWidth;
	rect.bottom=m_scrinfo.framebufferHeight;
	return FALSE;
}