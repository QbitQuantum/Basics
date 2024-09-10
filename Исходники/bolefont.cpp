// rayk - need to ensure that this object supports IPersistStream
BOleFont::BOleFont (BOleClassManager *pCF, IBUnknownMain * pO) :
        BOleComponent (pCF, pO),
        weight (FW_NORMAL),            modified (FALSE),
        charSet (DEFAULT_CHARSET),     style (fsBold),
        pTI (NULLP),                   pTL (NULLP),
        pF (NULLP),                    pEventList (NULLP),
        cyLogical (1),                 cyHimetric (1),
        bstrName (SysAllocString (OLESTR ("Arial")))
//        bstrName (SysAllocString (OLESTR ("MS Sans Serif")))
{
  SETFONTSIZE(height, 12);
  HRESULT err = LoadTypeLib (OLESTR ("bole.tlb"), &pTL);
  if (!err) {
    ITypeInfo *pTI;
    err = pTL->GetTypeInfoOfGuid (IID_BOleFont, &pTI);
  }
  // EventHandler deal with ConnecctionPoints
  pEventList = new BEventList (1);
  if (pEventList) {
    pEventList->AddRef();
    pEventList->AddEventsSet (IID_IPropertyNotifySink, AsPIUnknown(this), 5);
  }
}