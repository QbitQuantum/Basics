void CMovieView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rc;
	CStatic* pFrame = (CStatic*)GetDlgItem(IDC_FORM_IMAGE);
	pFrame->GetWindowRect(rc);
	ScreenToClient(rc);

	if(rc.PtInRect(point))
	{
		// 리소스를 이용하는 경우 
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), AfxGetInstanceHandle(), 
			SND_ASYNC | SND_RESOURCE); 
        
		// 파일을 이용하는 경우 
		//PlaySound("c:\\Ricochet.wav", NULL, SND_ASYNC | SND_FILENAME); 
	}	
	CFormView::OnMouseMove(nFlags, point);
}