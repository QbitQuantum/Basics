void log_debug(wchar_t *mess){
  wchar_t *buff=malloc((wcslen(mess)+100)*sizeof(wchar_t));
  swprintf(buff,wcslen(mess)+100,L"DEBUG! %s",mess);
  log_info(buff);
  free(buff);
}