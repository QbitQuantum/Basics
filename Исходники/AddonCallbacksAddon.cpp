const char* CAddonCallbacksAddon::GetLocalizedTime(const void* addonData,time_t time, bool bWithSeconds)
{
  CAddonCallbacks* helper = (CAddonCallbacks*) addonData;
  if (!helper)
    return NULL;

  CDateTime date(time);

  CStdString string = date.GetAsLocalizedTime("",bWithSeconds);

  char *buffer = (char*) malloc (string.length()+1);
  strcpy(buffer, string.c_str());
  return buffer;
}