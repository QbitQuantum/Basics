gboolean
gst_dshow_show_propertypage (IBaseFilter * base_filter)
{
  gboolean ret = FALSE;
  ISpecifyPropertyPages *pProp = NULL;
  HRESULT hres =
      base_filter->QueryInterface (IID_ISpecifyPropertyPages, (void **) &pProp);
  if (SUCCEEDED (hres)) {
    /* Get the filter's name and IUnknown pointer. */
    FILTER_INFO FilterInfo;
    CAUUID caGUID;
    IUnknown *pFilterUnk = NULL;
    hres = base_filter->QueryFilterInfo (&FilterInfo);
    base_filter->QueryInterface (IID_IUnknown, (void **) &pFilterUnk);

    /* Show the page. */
    pProp->GetPages (&caGUID);
    pProp->Release ();
    OleCreatePropertyFrame (GetDesktopWindow (), 0, 0, FilterInfo.achName,
        1, &pFilterUnk, caGUID.cElems, caGUID.pElems, 0, 0, NULL);

    pFilterUnk->Release ();
    FilterInfo.pGraph->Release ();
    CoTaskMemFree (caGUID.pElems);
  }
  return ret;
}