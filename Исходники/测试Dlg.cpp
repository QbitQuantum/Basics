void CMyDlg::OnPaint() 
{
	CPaintDC dc(this);
	CRect rcClient;
	GetClientRect(&rcClient);
	Graphics  graphics(dc); 
	if (version&&bIsAero) graphics.Clear(Color.Black);
	else graphics.Clear(Color.White);
	
	Bitmap CacheImage(rcClient.Width(),rcClient.Height());
	Graphics buffer(&CacheImage);
	buffer.SetSmoothingMode(SmoothingModeAntiAlias);
	buffer.SetInterpolationMode(InterpolationModeHighQualityBicubic);
	
	Image  *logo;
	Image  *button;
	ImageFromIDResource(2,"png",logo);
	ImageFromIDResource(1,"png",button);
	buffer.DrawImage(logo, -5,20);
	buffer.DrawImage(button, 165,122);
	buffer.DrawImage(button, 350,122);
	
	FontFamily fontFamily(version?L"微软雅黑":L"宋体");
	StringFormat strformat;
	wchar_t pszbuf[512];
	wsprintfW(pszbuf,L"本程序适用于 迅雷5.9 系列\n如果本软件有错，我概不负责，但我会尽力解决。\n只有极少数时候需要您指定安装目录(比如非官方版)。\n如果会员补丁失效，重新破解即可。\n\n\n请选择：　　　　一键增强　　　　　　　%s取消增强\n\n2010年4月7日更新　　www.shuax.com",version?L"　":L" ");
	GraphicsPath path;
	path.AddString(pszbuf, wcslen(pszbuf), &fontFamily, FontStyleRegular, version?15:16, Gdiplus::Point(version?90:80,version?9:20), &strformat );
	
	Pen pen(Color(18, 255, 255, 255), 3.0);
	//pen.SetLineJoin(LineJoinRound);
	buffer.DrawPath(&pen, &path);
	
	SolidBrush brush(Color(0,0,0));
	buffer.FillPath(&brush, &path);
	graphics.DrawImage(&CacheImage, 0, 0);
	graphics.ReleaseHDC(dc);
}