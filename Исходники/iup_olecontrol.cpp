static int iOleControlCreateMethod(Ihandle* ih, void **params)
{
  CLSID clsid;

  if (!params || !(params[0]))
    return IUP_ERROR;

  char *progID = (char*)params[0];

  /* free the data alocated by IupCanvas */
  if (ih->data) free(ih->data);
  ih->data = iupALLOCCTRLDATA();

  /* change the IupCanvas default values */
  iupAttribSetStr(ih, "BORDER", "NO");

  /* IupCanvas callbacks */
  IupSetCallback(ih,"RESIZE_CB",(Icallback)iOleControlResize_CB);

  size_t len = strlen(progID)+1;
  wchar_t* wcProgId = (wchar_t*) malloc(len * sizeof(wchar_t));
  mbstowcs(wcProgId, progID, len);
  HRESULT hr = CLSIDFromProgID(wcProgId, &clsid);
  free(wcProgId);
  if(FAILED(hr))
    return IUP_ERROR;

  ih->data->olehandler = new tOleHandler();
  if (ih->data->olehandler->Create(&clsid) == CREATE_FAILED)
    return IUP_ERROR;

  return IUP_NOERROR;
}