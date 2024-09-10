void CScreenViewWnd::updateStatus(int camera)
{
	if (GetSafeHwnd() == NULL) {
		return;
	}

	_sync_drawing.Lock();

	if (_fuse1x1Mode == true &&
		_selectCamera != camera) {
		_sync_drawing.Unlock();
		return;
	}

	if (!_cameraView[camera].is_visible()) {
		_sync_drawing.Unlock();
		return;
	}

	int camstatus = getCameraState(camera);

	CClientDC dc(this);
	CMemDC MemDC;
	MemDC.CreateDC(&dc, &_bmpCanvas);

	const CRect& rctcamera = _cameraView[camera].rect();
	if (camstatus != CameraView::ENABLED) {
		MemDC->FillSolidRect(rctcamera, (camstatus == CameraView::NO_VIDEO) ? RGB(0, 0, 255) : RGB(0, 0, 0));
	}

	CString strStatus = _T("");
	switch (camstatus)	{
		case CameraView::NO_VIDEO :
			strStatus = _T("No Video");
			break;
		case CameraView::NOT_CONNECTED:
			strStatus = _T("Not Connected");
			break;
		case CameraView::COVERT_LEVEL1 :
			strStatus = _T("Covert");
			break;
		case CameraView::COVERT_LEVEL2 :
			strStatus = _T("");
			break;
	}

	CRect rctosd = rctcamera;
	rctosd.DeflateRect(5, 2, 5, 3);

	CFont* lpFontPrev = MemDC->SelectObject(&_fontText);
	drawText(&MemDC, strStatus, rctosd, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawText(&MemDC, getCameraTitle(camera), rctosd, DT_LEFT | DT_TOP | DT_SINGLELINE);
	MemDC->SelectObject(lpFontPrev);

	MemDC->Draw3dRect(rctcamera, RGB(255, 255, 255), RGB(255, 255, 255));

	dc.BitBlt(rctcamera.left, rctcamera.top,
			  rctcamera.Width(), rctcamera.Height(),
			  &MemDC,
			  rctcamera.left, rctcamera.top,
			  SRCCOPY);

	_sync_drawing.Unlock();
}