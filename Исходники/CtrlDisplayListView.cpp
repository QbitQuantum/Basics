void CtrlDisplayListView::onPaint(WPARAM wParam, LPARAM lParam)
{
	if (!validDisplayList || !gpuDebug)
		return;

	PAINTSTRUCT ps;
	HDC actualHdc = BeginPaint(wnd, &ps);
	HDC hdc = CreateCompatibleDC(actualHdc);
	HBITMAP hBM = CreateCompatibleBitmap(actualHdc, rect.right-rect.left, rect.bottom-rect.top);
	SelectObject(hdc, hBM);

	SetBkMode(hdc, TRANSPARENT);

	HPEN nullPen=CreatePen(0,0,0xffffff);
	HPEN condPen=CreatePen(0,0,0xFF3020);
	HBRUSH nullBrush=CreateSolidBrush(0xffffff);
	HBRUSH currentBrush=CreateSolidBrush(0xFFEfE8);

	HPEN oldPen=(HPEN)SelectObject(hdc,nullPen);
	HBRUSH oldBrush=(HBRUSH)SelectObject(hdc,nullBrush);
	HFONT oldFont = (HFONT)SelectObject(hdc,(HGDIOBJ)font);
	
	HICON breakPoint = (HICON)LoadIcon(GetModuleHandle(0),(LPCWSTR)IDI_STOP);

	auto disasm = gpuDebug->DissassembleOpRange(windowStart, windowStart + (visibleRows + 2) * instructionSize);

	for (int i = 0; i < visibleRows+2; i++)
	{
		unsigned int address=windowStart + i*instructionSize;
		bool stall = address == list.stall;

		int rowY1 = rowHeight*i;
		int rowY2 = rowHeight*(i+1);

		// draw background
		COLORREF backgroundColor = stall ? 0xCCCCFF : 0xFFFFFF;
		COLORREF textColor = 0x000000;
		
		if (address >= selectRangeStart && address < selectRangeEnd)
		{
			if (hasFocus)
			{
				backgroundColor = address == curAddress ? 0xFF8822 : 0xFF9933;
				textColor = 0xFFFFFF;
			} else {
				backgroundColor = 0xC0C0C0;
			}
		}

		HBRUSH backgroundBrush = CreateSolidBrush(backgroundColor);
		HPEN backgroundPen = CreatePen(0,0,backgroundColor);
		SelectObject(hdc,backgroundBrush);
		SelectObject(hdc,backgroundPen);
		Rectangle(hdc,0,rowY1,rect.right,rowY1+rowHeight);
		
		SelectObject(hdc,currentBrush);
		SelectObject(hdc,nullPen);

		DeleteObject(backgroundBrush);
		DeleteObject(backgroundPen);

		// display address/symbol
		if (GPUBreakpoints::IsAddressBreakpoint(address))
		{
			textColor = 0x0000FF;
			int yOffset = std::max(-1,(rowHeight-14+1)/2);
			DrawIconEx(hdc,2,rowY1+1+yOffset,breakPoint,32,32,0,0,DI_NORMAL);
		}
		SetTextColor(hdc,textColor);

		GPUDebugOp op = i < (int)disasm.size() ? disasm[i] : GPUDebugOp();

		char addressText[64];
		sprintf(addressText,"%08X %08X",op.pc,op.op);
		TextOutA(hdc,pixelPositions.addressStart,rowY1+2,addressText,(int)strlen(addressText));

		if (address == list.pc)
		{
			TextOut(hdc,pixelPositions.opcodeStart-8,rowY1,L"■",1);
		}

		const char* opcode = op.desc.c_str();
		SelectObject(hdc,stall ? boldfont : font);
		TextOutA(hdc,pixelPositions.opcodeStart,rowY1+2,opcode,(int)strlen(opcode));
		SelectObject(hdc,font);
	}

	SelectObject(hdc,oldFont);
	SelectObject(hdc,oldPen);
	SelectObject(hdc,oldBrush);

	// copy bitmap to the actual hdc
	BitBlt(actualHdc, 0, 0, rect.right, rect.bottom, hdc, 0, 0, SRCCOPY);
	DeleteObject(hBM);
	DeleteDC(hdc);

	DeleteObject(nullPen);
	DeleteObject(condPen);

	DeleteObject(nullBrush);
	DeleteObject(currentBrush);
	
	DestroyIcon(breakPoint);

	EndPaint(wnd, &ps);
}