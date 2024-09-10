   void 
   ScriptServer::FireEvent(Event e,  const String &sEventCaller, shared_ptr<ScriptObjectContainer> pObjects)
   {
      if (!Configuration::Instance()->GetUseScriptServer())
         return;

	  // JDR: stores the name of the method that is fired in the script. http://www.hmailserver.com/forum/viewtopic.php?f=2&t=25497
	  String m_sEventName = _T("Unknown");

      switch (e)
      {
      case EventOnClientConnect:
		 m_sEventName = _T("OnClientConnect");
         if (!m_bHasOnClientConnect)
            return;
         break;
      case EventOnAcceptMessage:
		 m_sEventName = _T("OnAcceptMessage");
         if (!m_bHasOnAcceptMessage)
            return;
         break;
      case EventOnMessageDeliver:
	     m_sEventName = _T("OnMessageDeliver");
         if (!m_bHasOnDeliverMessage)
            return;
         break;
      case EventOnBackupCompleted:
		  m_sEventName = _T("OnBackupCompleted");
         if (!m_bHasOnBackupCompleted)
            return;
         break;
      case EventOnBackupFailed:
		  m_sEventName = _T("OnBackupFailed");
         if (!m_bHasOnBackupFailed)
            return;
         break;
      case EventOnError:
		  m_sEventName = _T("OnError");
         if (!m_bHasOnError)
            return;
         break;
      case EventOnDeliveryStart:
		  m_sEventName = _T("OnDeliveryStart");
         if (!m_bHasOnDeliveryStart)
            return;
         break;
      case EventOnDeliveryFailed:
		  m_sEventName = _T("OnDeliveryFailed");
         if (!m_bHasOnDeliveryFailed)
            return;
         break;
      case EventOnExternalAccountDownload:
		  m_sEventName = _T("OnExternalAccountDownload");
         if (!m_bHasOnExternalAccountDownload)
            return;
         break;
      case EventOnSMTPData:
		  m_sEventName = _T("OnSMTPData");
         if (!m_bHasOnSMTPData)
            return;
         break;

      case EventCustom:
         break;
      default:
         {
            return;
         }
         
      }

	  // JDR: Added event name to the debug log. http://www.hmailserver.com/forum/viewtopic.php?f=2&t=25497
	  LOG_DEBUG("ScriptServer::FireEvent-" + m_sEventName);

      String sScript;

      // Build the script.
      if (m_sScriptLanguage == _T("VBScript"))
         sScript = m_sScriptContents + "\r\n\r\n" + "Call " + sEventCaller + "\r\n";
      else if (m_sScriptLanguage == _T("JScript"))
         sScript = m_sScriptContents + "\r\n\r\n" + sEventCaller + ";\r\n";

      CComObject<CScriptSiteBasic>* pBasic;
      CComObject<CScriptSiteBasic>::CreateInstance(&pBasic);
      CComQIPtr<IActiveScriptSite> spUnk;
      
      if (!pBasic)
      {
         ErrorManager::Instance()->ReportError(ErrorManager::High, 5018, "ScriptServer::FireEvent", "Failed to create instance of script site.");
         return;
      }
      
      spUnk = pBasic; // let CComQIPtr tidy up for us
      pBasic->Initiate(m_sScriptLanguage, NULL);
      pBasic->SetObjectContainer(pObjects);
      pBasic->AddScript(sScript);
      pBasic->Run();
      pBasic->Terminate();

      LOG_DEBUG("ScriptServer:~FireEvent");
   }