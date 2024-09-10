void CChartCtrl::SaveAsImage(const TChartString& strFilename, 
							 const CRect& rect,
							 int nBPP,
							 REFGUID guidFileType)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

	CImage chartImage;
	CRect chartRect = rect;
	if (chartRect.IsRectEmpty())
	{
		GetClientRect(&chartRect);
	}
    
	chartImage.Create(chartRect.Width(), chartRect.Height(), nBPP);
	CDC newDC;
	newDC.Attach(chartImage.GetDC());

	DrawBackground(&newDC, chartRect);
	chartRect.DeflateRect(3,3);
	DrawChart(&newDC, chartRect);

	newDC.Detach();
	chartImage.Save(strFilename.c_str(), guidFileType);
	chartImage.ReleaseDC();
}