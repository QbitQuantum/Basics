int CCrashInfoReader::Init(CString sCrashInfoFileName)
{ 
  strconv_t strconv;
  ErrorReportInfo eri;
  
  TiXmlDocument doc;
  bool bOpen = doc.LoadFile(strconv.t2a(sCrashInfoFileName));
  if(!bOpen)
    return 1;

  TiXmlHandle hRoot = doc.FirstChild("CrashRptInternal");
  if(hRoot.ToElement()==NULL)
    return 1;

  {    
    TiXmlHandle hUnsentCrashReportsFolder = hRoot.FirstChild("UnsentCrashReportsFolder");
    if(hUnsentCrashReportsFolder.FirstChild().ToText()!=NULL)
    {      
      const char* szUnsentCrashReportsFolder = hUnsentCrashReportsFolder.FirstChild().ToText()->Value();
      if(szUnsentCrashReportsFolder!=NULL)
      {
        m_sUnsentCrashReportsFolder = strconv.utf82t(szUnsentCrashReportsFolder);
        Utility::CreateFolder(m_sUnsentCrashReportsFolder);
        
        m_sINIFile = m_sUnsentCrashReportsFolder + _T("\\~CrashRpt.ini");        
      }
    }
  }  
  
  {
    TiXmlHandle hReportFolder = hRoot.FirstChild("ReportFolder");
    if(hReportFolder.FirstChild().ToText()!=NULL)
    {
      const char* szReportFolder = hReportFolder.FirstChild().ToText()->Value();
      if(szReportFolder!=NULL)
        eri.m_sErrorReportDirName = strconv.utf82t(szReportFolder);
    }
  }

  {
    m_bQueueEnabled = FALSE;
    TiXmlHandle hQueueEnabled = hRoot.FirstChild("QueueEnabled");
    if(hQueueEnabled.FirstChild().ToText()!=NULL)
    {      
      const char* szQueueEnabled = hQueueEnabled.FirstChild().ToText()->Value();
      if(szQueueEnabled!=NULL)
      {
        m_bQueueEnabled = atoi(szQueueEnabled);        
      }
    }
  }  

  {
    m_bSendRecentReports = FALSE;
    TiXmlHandle hSendRecentReports = hRoot.FirstChild("SendRecentReports");
    if(hSendRecentReports.FirstChild().ToText()!=NULL)
    {      
      const char* szSendRecentReports = hSendRecentReports.FirstChild().ToText()->Value();
      if(szSendRecentReports!=NULL)
      {
        m_bSendRecentReports = atoi(szSendRecentReports);        
      }
    }
  }  


  {
    TiXmlHandle hCrashGUID = hRoot.FirstChild("CrashGUID");
    if(hCrashGUID.FirstChild().ToText()!=NULL)
    {
      const char* szCrashGUID = hCrashGUID.FirstChild().ToText()->Value();
      if(szCrashGUID!=NULL)
        eri.m_sCrashGUID = strconv.utf82t(szCrashGUID);
    }
  }

  {
    TiXmlHandle hAppName = hRoot.FirstChild("AppName");
    if(hAppName.FirstChild().ToText()!=NULL)
    {
      const char* szAppName = hAppName.FirstChild().ToText()->Value();
      if(szAppName!=NULL)
        m_sAppName = strconv.utf82t(szAppName);
    }
  }

  {
    TiXmlHandle hLangFileName = hRoot.FirstChild("LangFileName");
    if(hLangFileName.FirstChild().ToText()!=NULL)
    {
      const char* szLangFileName = hLangFileName.FirstChild().ToText()->Value();
      if(szLangFileName!=NULL)
        m_sLangFileName = strconv.utf82t(szLangFileName);
    }
  }

  {
    TiXmlHandle hDbgHelpPath = hRoot.FirstChild("DbgHelpPath");
    if(hDbgHelpPath.FirstChild().ToText()!=NULL)
    {
      const char* szDbgHelpPath = hDbgHelpPath.FirstChild().ToText()->Value();
      if(szDbgHelpPath!=NULL)
        m_sDbgHelpPath = strconv.utf82t(szDbgHelpPath);
    }
  }

  {
    m_bGenerateMinidump = TRUE;
    TiXmlHandle hGenerateMinidump = hRoot.FirstChild("GenerateMinidump");
    if(hGenerateMinidump.FirstChild().ToText()!=NULL)
    {
      const char* szGenerateMinidump = hGenerateMinidump.FirstChild().ToText()->Value();
      if(szGenerateMinidump!=NULL)
        m_bGenerateMinidump = (MINIDUMP_TYPE)atol(szGenerateMinidump);      
    }    
  }

  {
    TiXmlHandle hMinidumpType = hRoot.FirstChild("MinidumpType");
    if(hMinidumpType.FirstChild().ToText()!=NULL)
    {
      const char* szMinidumpType = hMinidumpType.FirstChild().ToText()->Value();
      if(szMinidumpType!=NULL)
        m_MinidumpType = (MINIDUMP_TYPE)atol(szMinidumpType);
      else
        m_MinidumpType = MiniDumpNormal;
    }
    else
      m_MinidumpType = MiniDumpNormal;
  }

  {
    TiXmlHandle hUrl = hRoot.FirstChild("Url");
    if(hUrl.FirstChild().ToText()!=NULL)
    {
      const char* szUrl = hUrl.FirstChild().ToText()->Value();
      if(szUrl!=NULL)
        m_sUrl = strconv.utf82t(szUrl);
    }
  }

  {
    TiXmlHandle hEmailTo = hRoot.FirstChild("EmailTo");
    if(hEmailTo.FirstChild().ToText()!=NULL)
    {
      const char* szEmailTo = hEmailTo.FirstChild().ToText()->Value();
      if(szEmailTo!=NULL)
        m_sEmailTo = strconv.utf82t(szEmailTo);
    }
  }

  {
    m_nSmtpPort = 25;
    TiXmlHandle hSmtpPort = hRoot.FirstChild("SmtpPort");
    if(hSmtpPort.FirstChild().ToText()!=NULL)
    {
      const char* szSmtpPort = hSmtpPort.FirstChild().ToText()->Value();
      if(szSmtpPort!=NULL)
        m_nSmtpPort = atoi(szSmtpPort);
    }
  }

  {
    TiXmlHandle hEmailSubject = hRoot.FirstChild("EmailSubject");
    if(hEmailSubject.FirstChild().ToText()!=NULL)
    {
      const char* szEmailSubject = hEmailSubject.FirstChild().ToText()->Value();
      if(szEmailSubject!=NULL)
        m_sEmailSubject = strconv.utf82t(szEmailSubject);
    }
  }

  {
    TiXmlHandle hEmailText = hRoot.FirstChild("EmailText");
    if(hEmailText.FirstChild().ToText()!=NULL)
    {
      const char* szEmailText = hEmailText.FirstChild().ToText()->Value();
      if(szEmailText!=NULL)
        m_sEmailText = strconv.utf82t(szEmailText);
    }
  }

  {
    TiXmlHandle hPrivacyPolicyUrl = hRoot.FirstChild("PrivacyPolicyUrl");    
    if(hPrivacyPolicyUrl.FirstChild().ToText()!=NULL)
    {
      const char* szPrivacyPolicyUrl = hPrivacyPolicyUrl.FirstChild().ToText()->Value();
      if(szPrivacyPolicyUrl!=NULL)
        m_sPrivacyPolicyURL = strconv.utf82t(szPrivacyPolicyUrl);
    }
  }

  {
    TiXmlHandle hHttpPriority = hRoot.FirstChild("HttpPriority");
    if(hHttpPriority.FirstChild().ToText()!=NULL)
    {
      const char* szHttpPriority = hHttpPriority.FirstChild().ToText()->Value();
      if(szHttpPriority!=NULL)
        m_uPriorities[CR_HTTP] = atoi(szHttpPriority);
      else
        m_uPriorities[CR_HTTP] = 0;
    }
  }

  {
    TiXmlHandle hSmtpPriority = hRoot.FirstChild("SmtpPriority");
    if(hSmtpPriority.FirstChild().ToText()!=NULL)
    {
      const char* szSmtpPriority = hSmtpPriority.FirstChild().ToText()->Value();
      if(szSmtpPriority!=NULL)
        m_uPriorities[CR_SMTP] = atoi(szSmtpPriority);
      else
        m_uPriorities[CR_SMTP] = 0;
    }
  }

  {
    TiXmlHandle hMapiPriority = hRoot.FirstChild("MapiPriority");
    if(hMapiPriority.FirstChild().ToText()!=NULL)
    {
      const char* szMapiPriority = hMapiPriority.FirstChild().ToText()->Value();
      if(szMapiPriority!=NULL)
        m_uPriorities[CR_SMAPI] = atoi(szMapiPriority);
      else
        m_uPriorities[CR_SMAPI] = 0;
    }
  }

  {
    TiXmlHandle hProcessId = hRoot.FirstChild("ProcessId");
    if(hProcessId.FirstChild().ToText()!=NULL)
    {
      const char* szProcessId = hProcessId.FirstChild().ToText()->Value();
      if(szProcessId!=NULL)
        m_dwProcessId = strtoul(szProcessId, NULL, 10);
      else
        m_dwProcessId = 0;
    }
  }

  {
    TiXmlHandle hThreadId = hRoot.FirstChild("ThreadId");
    if(hThreadId.FirstChild().ToText()!=NULL)
    {
      const char* szThreadId = hThreadId.FirstChild().ToText()->Value();
      if(szThreadId!=NULL)
        m_dwThreadId = strtoul(szThreadId, NULL, 10);
      else 
        m_dwThreadId = 0;
    }
  }

  {
    m_pExInfo = NULL;
    TiXmlHandle hExceptionPointersAddress = hRoot.FirstChild("ExceptionPointersAddress");
    if(hExceptionPointersAddress.FirstChild().ToText()!=NULL)
    {
      const char* szExceptionPointersAddress = hExceptionPointersAddress.FirstChild().ToText()->Value();
      if(szExceptionPointersAddress!=NULL)
        m_pExInfo = (PEXCEPTION_POINTERS)_strtoui64(szExceptionPointersAddress, NULL, 16);     
    }    
  }

  {
    TiXmlHandle hAddScreenshot = hRoot.FirstChild("AddScreenshot");
    if(hAddScreenshot.FirstChild().ToText()!=NULL)
    {
      const char* szAddScreenshot = hAddScreenshot.FirstChild().ToText()->Value();
      if(szAddScreenshot!=NULL)
        m_bAddScreenshot = strtol(szAddScreenshot, NULL, 10);
      else
        m_bAddScreenshot = FALSE;
    }
  }

  {
    m_dwScreenshotFlags = 0;
    TiXmlHandle hScreenshotFlags = hRoot.FirstChild("ScreenshotFlags");
    if(hScreenshotFlags.FirstChild().ToText()!=NULL)
    {
      const char* szScreenshotFlags = hScreenshotFlags.FirstChild().ToText()->Value();
      if(szScreenshotFlags!=NULL)
        m_dwScreenshotFlags = strtoul(szScreenshotFlags, NULL, 10);        
    }
  }

  {
    m_ptCursorPos.SetPoint(0, 0);
    TiXmlHandle hCursorPos = hRoot.FirstChild("CursorPos");
    if(hCursorPos.ToElement()!=NULL)
    {
      const char* szX = hCursorPos.ToElement()->Attribute("x");
      const char* szY = hCursorPos.ToElement()->Attribute("y");
      if(szX && szY)
      {
        m_ptCursorPos.x = atoi(szX);
        m_ptCursorPos.y = atoi(szY);
      }
    }
  }

  {
    m_rcAppWnd.SetRectEmpty();
    TiXmlHandle hAppWndRect = hRoot.FirstChild("AppWindowRect");
    if(hAppWndRect.ToElement()!=NULL)
    {
      const char* szLeft = hAppWndRect.ToElement()->Attribute("left");
      const char* szTop = hAppWndRect.ToElement()->Attribute("top");
      const char* szRight = hAppWndRect.ToElement()->Attribute("right");
      const char* szBottom = hAppWndRect.ToElement()->Attribute("bottom");

      if(szLeft && szTop && szRight && szBottom)
      {
        m_rcAppWnd.left = atoi(szLeft);
        m_rcAppWnd.top = atoi(szTop);
        m_rcAppWnd.right = atoi(szRight);
        m_rcAppWnd.bottom = atoi(szBottom);
      }
    }
  }

  {
    m_bHttpBinaryEncoding = FALSE;    
    TiXmlHandle hHttpBinaryEncoding = hRoot.FirstChild("HttpBinaryEncoding");
    if(hHttpBinaryEncoding.FirstChild().ToText()!=NULL)
    {
      const char* szHttpBinaryEncoding = hHttpBinaryEncoding.FirstChild().ToText()->Value();
      if(szHttpBinaryEncoding!=NULL)
        m_bHttpBinaryEncoding = atoi(szHttpBinaryEncoding);
    }      
  }

  {
    m_bSilentMode = FALSE;    
    TiXmlHandle hSilentMode = hRoot.FirstChild("SilentMode");
    if(hSilentMode.FirstChild().ToText()!=NULL)
    {
      const char* szSilentMode = hSilentMode.FirstChild().ToText()->Value();
      if(szSilentMode!=NULL)
        m_bSilentMode = atoi(szSilentMode);
    }      
  }

  {
    m_bSendErrorReport = FALSE;    
    TiXmlHandle hSendErrorReport = hRoot.FirstChild("SendErrorReport");
    if(hSendErrorReport.FirstChild().ToText()!=NULL)
    {
      const char* szSendErrorReport = hSendErrorReport.FirstChild().ToText()->Value();
      if(szSendErrorReport!=NULL)
        m_bSendErrorReport = atoi(szSendErrorReport);     
    }      
  }

  {
    m_bAppRestart = FALSE;    
    TiXmlHandle hAppRestart = hRoot.FirstChild("AppRestart");
    if(hAppRestart.FirstChild().ToText()!=NULL)
    {
      const char* szAppRestart = hAppRestart.FirstChild().ToText()->Value();
      if(szAppRestart!=NULL)
        m_bAppRestart = atoi(szAppRestart);     
    }      
  }

  {    
    TiXmlHandle hRestartCmdLine = hRoot.FirstChild("RestartCmdLine");
    if(hRestartCmdLine.FirstChild().ToText()!=NULL)
    {
      const char* szRestartCmdLine = hRestartCmdLine.FirstChild().ToText()->Value();
      if(szRestartCmdLine!=NULL)
        m_sRestartCmdLine = strconv.utf82t(szRestartCmdLine);     
    }      
  }

  {    
    TiXmlHandle hSmtpProxyServer = hRoot.FirstChild("SmtpProxyServer");
    if(hSmtpProxyServer.FirstChild().ToText()!=NULL)
    {
      const char* szSmtpProxyServer = hSmtpProxyServer.FirstChild().ToText()->Value();
      if(szSmtpProxyServer!=NULL)
        m_sSmtpProxyServer = strconv.utf82t(szSmtpProxyServer);     
    }      
  }

  {    
    m_nSmtpProxyPort = 25;
    TiXmlHandle hSmtpProxyPort = hRoot.FirstChild("SmtpProxyPort");
    if(hSmtpProxyPort.FirstChild().ToText()!=NULL)
    {
      const char* szSmtpProxyPort = hSmtpProxyPort.FirstChild().ToText()->Value();
      if(szSmtpProxyPort!=NULL)
        m_nSmtpProxyPort = atoi(szSmtpProxyPort);     
    }      
  }

  if(!m_bSendRecentReports)
  {    
    // Get the list of files that should be included to report
    ParseFileList(hRoot, eri);

    // Get some info from crashrpt.xml
    CString sXmlName = eri.m_sErrorReportDirName + _T("\\crashrpt.xml");
    ParseCrashDescription(sXmlName, FALSE, eri);    
    
    m_Reports.push_back(eri);
  }  
  else
  {
    // Look for unsent error reports
    CString sSearchPattern = m_sUnsentCrashReportsFolder + _T("\\*");
    CFindFile find;
    BOOL bFound = find.FindFile(sSearchPattern);
    while(bFound)
    {
      if(find.IsDirectory() && !find.IsDots())
      {
        CString sErrorReportDirName = m_sUnsentCrashReportsFolder + _T("\\") + 
          find.GetFileName();
        CString sFileName = sErrorReportDirName + _T("\\crashrpt.xml");
        ErrorReportInfo eri;
        eri.m_sErrorReportDirName = sErrorReportDirName;
        if(0==ParseCrashDescription(sFileName, TRUE, eri))
        {          
          eri.m_uTotalSize = GetUncompressedReportSize(eri);
          m_Reports.push_back(eri);
        }
      }

      bFound = find.FindNextFile();
    }
  }
  
  return 0;
}