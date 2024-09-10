bool CMyList::OnTheEvent (void* pParam)
{
	TEventUI* pEvent = (TEventUI*)pParam;
	CContainerUI* pContainer = NULL;

	if (pEvent->pSender == NULL) {
		return true;
	}


	if (_tcsicmp (pEvent->pSender->GetClass(), _T ("ContainerUI")) != 0) {
		pContainer = static_cast <CContainerUI*> (pEvent->pSender->GetParent());
	}
	else {
		pContainer = static_cast <CContainerUI*> (pEvent->pSender);
	}

	if (pContainer == NULL) {
		return true;
	}

	if (pEvent->Type == UIEVENT_MOUSEENTER) {
		if (pContainer->GetBkColor() != 0x1100FF00)
			pContainer->SetBkColor(0x1100FF00);
	}
	else if (pEvent->Type == UIEVENT_MOUSELEAVE) {
		if (pContainer->GetBkColor() != 0xFFFFFFFF)
			pContainer->SetBkColor(0xFFFFFFFF);
	}

	return true;
}