void CNetscapeSrvrItem::OnDoVerb(LONG iVerb)
{
	switch (iVerb)
	{
	// open - maps to OnOpen
	case OLEIVERB_OPEN:
	case -OLEIVERB_OPEN-1:  // allows positive OLEIVERB_OPEN-1 in registry
		OnOpen();
		break;

	// primary, show, and unknown map to OnShow
	case OLEIVERB_PRIMARY:  // OLEIVERB_PRIMARY is 0 and "Edit" in registry
	case OLEIVERB_SHOW:
	case OLEIVERB_UIACTIVATE: {
		COleServerDoc* pDoc = GetDocument();
		m_ShowUI = TRUE;
		OnShow();
		break;
	}					  

	case OLEIVERB_INPLACEACTIVATE: {
		COleServerDoc* pDoc = GetDocument();
		m_ShowUI = FALSE;
		OnShow();
		break;
   }

	// hide maps to OnHide
	case OLEIVERB_HIDE:
	case -OLEIVERB_HIDE-1:  // allows positive OLEIVERB_HIDE-1 in registry
		OnHide();
		break;


	case NO_UI_EMBEDDING:	{
		//Get InPlaceFrame ptr.
		CGenericDoc *pDoc = GetDocument();
		ASSERT(pDoc);

		POSITION pos = pDoc->GetFirstViewPosition();
		CView *pView = pDoc->GetNextView(pos);
		ASSERT(pView);

		m_ShowUI = FALSE;

		OnShow();

		CInPlaceFrame *pFrm = (CInPlaceFrame *)pView->GetParent();
		ASSERT(pFrm);

		pFrm->DestroyResizeBar();

		break;
		}
	default:
		// negative verbs not understood should return E_NOTIMPL
		if (iVerb < 0)
			AfxThrowOleException(E_NOTIMPL);

		// positive verb not processed --
		//  according to OLE spec, primary verb should be executed
		//  instead.
		OnDoVerb(OLEIVERB_PRIMARY);

		// also, OLEOBJ_S_INVALIDVERB should be returned.
		AfxThrowOleException(OLEOBJ_S_INVALIDVERB);
	}
}