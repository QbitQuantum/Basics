//レイヤーウィンドウプロシージャ
LRESULT __stdcall LayerWndProc(HWND WindowHandle,UINT Message,WPARAM WParam,LPARAM LParam)
{
	switch (Message){
	case WM_PAINT:
		{
			PAINTSTRUCT PaintStruct;
			BeginPaint(WindowHandle,&PaintStruct);
			std::unique_ptr<Gdiplus::Font> DrawFont(new Gdiplus::Font(L"Tahoma",8));
			std::unique_ptr<Gdiplus::SolidBrush> WhiteBrush(new Gdiplus::SolidBrush(Gdiplus::Color::White)),BlackBrush(new Gdiplus::SolidBrush(Gdiplus::Color::Black));
			std::unique_ptr<Gdiplus::Graphics> LayerWindowGraphics(new Gdiplus::Graphics(WindowHandle));
			std::unique_ptr<Gdiplus::StringFormat> Layout(new Gdiplus::StringFormat(Gdiplus::StringFormatFlagsNoWrap));
			Layout->SetAlignment(Gdiplus::StringAlignment::StringAlignmentFar);
			Layout->SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentFar);
			Layout->SetTrimming(Gdiplus::StringTrimmingNone);
			RECT ClientRect;
			GetClientRect(WindowHandle,&ClientRect);
			Gdiplus::RectF LayoutRect(ClientRect.left,ClientRect.top,ClientRect.right-5,ClientRect.bottom-5);
			std::vector<wchar_t> WindowSize(64,0);
			_itow(ClientRect.right,WindowSize.data(),10);
			auto Null=std::find(WindowSize.begin(),WindowSize.end(),0);
			*Null++=L'\n';
			_itow(ClientRect.bottom,Null._Ptr,10);
			int Count=std::wcslen(WindowSize.data());
			LayerWindowGraphics->DrawString(WindowSize.data(),Count,&*DrawFont,LayoutRect,&*Layout,&*BlackBrush);
			LayoutRect.Inflate(-1,-1);
			LayerWindowGraphics->DrawString(WindowSize.data(),Count,&*DrawFont,LayoutRect,&*Layout,&*WhiteBrush);
			EndPaint(WindowHandle,&PaintStruct);
			break;
		}
	default:
		return DefWindowProc(WindowHandle,Message,WParam,LParam);
	}
	return 0;

}