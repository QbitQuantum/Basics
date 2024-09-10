BOOL C1394CameraDemoApp::OnIdle(LONG lCount)
{
	CMainFrame* pWnd = (CMainFrame *) theApp.GetMainWnd();
  HANDLE hFrameEvent;
  DWORD dwRet;
  BOOL GotFrame = FALSE;
  ULONG Timeout = 1000;
  ULONG Dropped = 0;
  unsigned long t;
  float fps;
  float belief;
  char buf[256];
  if(this->m_showCamera)
  {
    do {
      hFrameEvent = theCamera.GetFrameEvent();
      
      if(hFrameEvent == NULL)
      {
        // no frame is attached, push it on
        OutputDebugString("Pushing\n");
        if(theCamera.AcquireImageEx(FALSE,NULL) != CAM_ERROR_FRAME_TIMEOUT)
        {
          AfxMessageBox("WTF?");
        }
        hFrameEvent = theCamera.GetFrameEvent();
      }
      dwRet = MsgWaitForMultipleObjects(1,&hFrameEvent,FALSE,Timeout,QS_ALLINPUT);
      switch(dwRet)
      {
      case WAIT_OBJECT_0:
        // got a frame
        if(Timeout == 0)
        {
          m_dropped++;
          OutputDebugString(" -> Drop\n");
        } else {
          t = clock();
          if(m_frames >= 32)
            m_timesum -= m_times[m_frames & 31];
          m_times[m_frames & 31] = t - m_lastclock;
          m_lastclock = t;
          m_timesum += m_times[m_frames & 31];
          m_frames++;
          if(m_timesum > 0)
          {
            fps = (float)(m_frames > 32 ? 32 : m_frames);
            fps /= m_timesum;
            fps *= 1000.0;
          } else {
            fps = 0.0;
          }
          // simple kalman on fps to provide some visual stability
          belief = ((float)(m_frames > 32 ? 32 : m_frames)) / 40.0f;
          m_fps = belief * m_fps + (1.0f - belief) * fps;
          sprintf(buf,"Displaying: %.1f fps, %.1f%% dropped\n",
            m_fps,100.0f * (float)(m_dropped)/(float)(m_frames));
          ((CMainFrame*)m_pMainWnd)->SetStatus(buf);
          GotFrame = TRUE;
          Timeout = 0;
        }
        if(theCamera.AcquireImageEx(FALSE,NULL) != CAM_SUCCESS)
        {
          sprintf(buf,"Error \"%s\" while Acquiring Images, Terminate Acguitision?",StrLastError());
          if(AfxMessageBox(buf,MB_YESNO,0) == IDYES)
            this->On1394StopCamera();
        }
        break;
      case WAIT_OBJECT_0 + 1:
        // got a message
        break;
      case WAIT_TIMEOUT:
        // timeout
        if(Timeout == 1000)
        {
          m_timeouts++;
          m_timeouts &= 0x3;
          sprintf(buf,"Timeout.%c%c%c",
            m_timeouts > 0 ? '.' : ' ',
            m_timeouts > 1 ? '.' : ' ',
            m_timeouts > 2 ? '.' : ' ');
          ((CMainFrame*)m_pMainWnd)->SetStatus(buf);
        }
        break;
      default:
        // error
        sprintf(buf,"Error \"%s\" while Acquiring Images, Terminate Acquitision?",StrLastError());
        if(AfxMessageBox(buf,MB_YESNO,0) == IDYES)
          this->On1394StopCamera();
        break;
      }
    } while(dwRet == WAIT_OBJECT_0);
    if(GotFrame)
    {
    	BITMAPINFO bmi;
      unsigned long wd,ht;
      theCamera.GetVideoFrameDimensions(&wd,&ht);
	    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bmi.bmiHeader.biWidth = (long) wd;
      bmi.bmiHeader.biHeight = (long) ht;
	    bmi.bmiHeader.biPlanes = 1;
	    bmi.bmiHeader.biBitCount = 24;
	    bmi.bmiHeader.biCompression = BI_RGB;
	    bmi.bmiHeader.biSizeImage = 0;
	    bmi.bmiHeader.biXPelsPerMeter = 1000;
	    bmi.bmiHeader.biYPelsPerMeter = 1000;
	    bmi.bmiHeader.biClrUsed = 0;
	    bmi.bmiHeader.biClrImportant = 0;
	    RECT rect;
	    int x,y,w,h,i=0, timeouts = 0;
	    unsigned long sum = 0, t=clock(),totaldropped = 0;
      int drop = 0;
      CDC *pDC = pWnd->GetViewDC();
      HDC hDC = pDC->m_hDC;
      BOOL DropStuff = TRUE;
		  pWnd->GetWindowRect(&rect);
		  h = rect.bottom - rect.top - theApp.m_borderHeight;
		  w = rect.right - rect.left - theApp.m_borderWidth;

		  x = w - wd;
		  x >>= 1;
		  if(x < 0) x = 0;

		  y = h - ht;
		  y >>= 1;
		  if(y < 0) y = 0;

      theCamera.getDIB(this->m_pBitmap,this->m_pBitmapLength);
		  SetDIBitsToDevice(hDC, x, y, wd, ht, 0, 0, 0, ht, theApp.m_pBitmap, &bmi, DIB_RGB_COLORS);
      pWnd->ReleaseViewDC(pDC);
    } 
    return TRUE;
  }
  return FALSE;
}