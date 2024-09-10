void CMovPlayerFrm::OnPaint()
{


	if(NULL==lpPrimary)return;
	if(DD_OK == lpPrimary->IsLost()){
		
		if(forccNum<3){
			HDC hDC = ::GetDC(m_hWnd);
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 8));
		
			HBRUSH old_brush = (HBRUSH)SelectObject(hDC,brush);
			PatBlt(hDC,0,0, 800, 600, PATCOPY);
			SelectObject(hDC,old_brush);

			DrawSurface(GetDeviceCaps(hDC,BITSPIXEL));

			DeleteObject(brush);
			::ReleaseDC(m_hWnd,hDC);
		}
	}else{
		lpPrimary->Restore();
		if(lpSrcSurface)lpSrcSurface->Restore();
	}
} 