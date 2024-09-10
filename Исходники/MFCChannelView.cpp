void
MFCChannelView::ArrangeChildren()
{
	cout << "cv: arrange children()\n";
	long	atY = 12;
	for (short i=0; i<NInR(); i++) {
		MFCInputView	*iv = (MFCInputView *)InR(i);
		iv->SetWindowPos(&wndTop, 1, atY, 0, 0, SWP_NOSIZE);
		atY += iv->bounds.bottom+1;
	}
	atY += 3;
	for (short i=0; i<NOutR(); i++) {
		MFCOutputView	*ov = (MFCOutputView *)OutR(i);
		ov->SetWindowPos(&wndTop, 1, atY, 0, 0, SWP_NOSIZE);
		atY += ov->bounds.bottom+1;
	}
	bool	adjustMounty = false;
	if (atY != bounds.bottom) {
		adjustMounty = true;
	}
	SetWindowPos(&wndTop, 0, 0, bounds.right, atY, SWP_NOMOVE);
	if (adjustMounty) {
		CWnd *w = GetParent(), *ww=NULL;
		if (w && w->IsWindowVisible() && (ww=w->GetParent())) {
			long ret = ww->PostMessage(QM_ARRANGE_VIEW, 0, 0);
			CFrameWnd	*pfw = GetParentFrame();
			if (pfw) {
				QuaChildFrame	*qcfw = (QuaChildFrame *)pfw;
				qcfw->arranger->Invalidate();
			}
		}
	}
}