void LocalUpdateHandler::updateVideoRegion()
{
  ServerConfig *srvConf = Configurator::getInstance()->getServerConfig();
  unsigned int interval = srvConf->getVideoRecognitionInterval();

  DateTime curTime = DateTime::now();
  if ((curTime - m_lastVidUpdTime).getTime() > interval) {
    m_lastVidUpdTime = DateTime::now();
    m_vidRegion.clear();
    AutoLock al(srvConf);
    StringVector *classNames = srvConf->getVideoClassNames();
    std::vector<HWND> hwndVector;
    std::vector<HWND>::iterator hwndIter;

    WindowFinder::findWindowsByClass(classNames, &hwndVector);

    for (hwndIter = hwndVector.begin(); hwndIter != hwndVector.end(); hwndIter++) {
      HWND videoHWND = *hwndIter;
      if (videoHWND != 0) {
        WINDOWINFO wi;
        wi.cbSize = sizeof(WINDOWINFO);
        if (GetWindowInfo(videoHWND, &wi)) {
          Rect videoRect(wi.rcClient.left, wi.rcClient.top,
                         wi.rcClient.right, wi.rcClient.bottom);
          videoRect.move(-GetSystemMetrics(SM_XVIRTUALSCREEN),
                         -GetSystemMetrics(SM_YVIRTUALSCREEN));
          m_vidRegion.addRect(&videoRect);
        }
      }
    }
  }
}