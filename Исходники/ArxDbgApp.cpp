AcRx::AppRetCode
ArxDbgApp::entryPoint(AcRx::AppMsgCode msg, void* pkt)
{
    if (msg == AcRx::kInitAppMsg) {
		m_acadAppPtr = pkt;	// keep track of this for later use
        acutPrintf("\nAPPMSG: %s, kInitAppMsg", m_appName);
        return initApp();
    }
    else if (msg == AcRx::kUnloadAppMsg) {
        acutPrintf("\nAPPMSG: %s, kUnloadAppMsg", m_appName);
        return exitApp();
    }
    else if (msg == AcRx::kLoadDwgMsg) {
        acutPrintf("\nAPPMSG: %s, kLoadDwgMsg", m_appName);
        return initDwg();
    }
    else if (msg == AcRx::kUnloadDwgMsg) {
        acutPrintf("\nAPPMSG: %s, kUnloadDwgMsg", m_appName);
        return exitDwg();
    }
    else if (msg == AcRx::kInvkSubrMsg) {
        acutPrintf("\nAPPMSG: %s, kInvkSubrMsg", m_appName);
        return invokeSubr();
    }
    else if (msg == AcRx::kCfgMsg) {
        acutPrintf("\nAPPMSG: %s, kCfgMsg", m_appName);
        return config();
    }
    else if (msg == AcRx::kEndMsg) {
        acutPrintf("\nAPPMSG: %s, kEndMsg", m_appName);
        return endDwg();
    }
    else if (msg == AcRx::kQuitMsg) {
        acutPrintf("\nAPPMSG: %s, kQuitMsg", m_appName);
        return quitDwg();
    }
    else if (msg == AcRx::kSaveMsg) {
        acutPrintf("\nAPPMSG: %s, kSaveMsg", m_appName);
        return saveDwg();
    }
    else if (msg == AcRx::kDependencyMsg) {
        acutPrintf("\nAPPMSG: %s, kDependencyMsg", m_appName);

        if (m_appServicePtr == pkt) {
            acutPrintf("\nLocking app: %s", m_appName);
            acrxDynamicLinker->lockApplication(m_acadAppPtr);
        }

        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kNoDependencyMsg) {
        acutPrintf("\nAPPMSG: %s, kNoDependencyMsg", m_appName);

        if (m_appServicePtr == pkt) {
            acutPrintf("\nUnlocking app: %s", m_appName);
            acrxDynamicLinker->unlockApplication(m_acadAppPtr);
        }

        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kOleUnloadAppMsg) {
        acutPrintf("\nAPPMSG: %s, kOleUnloadAppMsg", m_appName);
        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kPreQuitMsg) {
        acutPrintf("\nAPPMSG: %s, kPreQuitMsg", m_appName);
        return AcRx::kRetOK;
    }
    else if (msg == AcRx::kInitDialogMsg) {
        acutPrintf("\nAPPMSG: %s, kInitDialogMsg", m_appName);
        return initDialog(pkt);
    }
    else if (msg == AcRx::kEndDialogMsg) {
        acutPrintf("\nAPPMSG: %s, kEndDialogMsg", m_appName);
        return endDialog(pkt);
    }
    else {
        ASSERT(0);        // just see if it ever happens
        return AcRx::kRetOK;
    }
}