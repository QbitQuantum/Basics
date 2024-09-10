// Sends a file download event to the Vista Event Log 
void
nsParentalControlsServiceWin::LogFileDownload(bool blocked, nsIURI *aSource, nsIFile *aTarget)
{
  nsAutoCString curi;

  if (!gEventWrite)
    return;

  // Note, EventDataDescCreate is a macro defined in the headers, not a function

  aSource->GetSpec(curi);
  nsAutoString uri = NS_ConvertUTF8toUTF16(curi);

  // Get the name of the currently running process
  nsCOMPtr<nsIXULAppInfo> appInfo = do_GetService("@mozilla.org/xre/app-info;1");
  nsAutoCString asciiAppName;
  if (appInfo)
    appInfo->GetName(asciiAppName);
  nsAutoString appName = NS_ConvertUTF8toUTF16(asciiAppName);

  static const WCHAR fill[] = L"";
  
  // See wpcevent.h and msdn for event formats
  EVENT_DATA_DESCRIPTOR eventData[WPC_ARGS_FILEDOWNLOADEVENT_CARGS];
  DWORD dwBlocked = blocked;

  EventDataDescCreate(&eventData[WPC_ARGS_FILEDOWNLOADEVENT_URL], (const void*)uri.get(),
                      ((ULONG)uri.Length()+1)*sizeof(WCHAR));
  EventDataDescCreate(&eventData[WPC_ARGS_FILEDOWNLOADEVENT_APPNAME], (const void*)appName.get(),
                      ((ULONG)appName.Length()+1)*sizeof(WCHAR));
  EventDataDescCreate(&eventData[WPC_ARGS_FILEDOWNLOADEVENT_VERSION], (const void*)fill, sizeof(fill));
  EventDataDescCreate(&eventData[WPC_ARGS_FILEDOWNLOADEVENT_BLOCKED], (const void*)&dwBlocked,
                      sizeof(dwBlocked));

  nsCOMPtr<nsILocalFileWin> local(do_QueryInterface(aTarget)); // May be null
  if (local) {
    nsAutoString path;
    local->GetCanonicalPath(path);
    EventDataDescCreate(&eventData[WPC_ARGS_FILEDOWNLOADEVENT_PATH], (const void*)path.get(),
                        ((ULONG)path.Length()+1)*sizeof(WCHAR));
  }
  else {
    EventDataDescCreate(&eventData[WPC_ARGS_FILEDOWNLOADEVENT_PATH], (const void*)fill, sizeof(fill));
  }

  gEventWrite(mProvider, &WPCEVENT_WEB_FILEDOWNLOAD, ARRAYSIZE(eventData), eventData);
}