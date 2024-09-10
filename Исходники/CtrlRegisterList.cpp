//Yeah this truly turned into a mess with the latest additions.. but it sure looks nice ;)
void CtrlRegisterList::onPaint(WPARAM wParam, LPARAM lParam)
{
	if (!cpu) 
		return;

	GetClientRect(wnd, &rect);
	PAINTSTRUCT ps;
	HDC hdc;
	
	hdc = BeginPaint(wnd, &ps);
	// TODO: Add any drawing code here...
	int width = rect.right;
	//numRows=(numRows&(~1)) + 1;
	SetBkMode(hdc, TRANSPARENT);
	DWORD bgColor = 0xffffff;
	HPEN nullPen=CreatePen(0,0,bgColor);
	HPEN currentPen=CreatePen(0,0,0);
	HPEN selPen=CreatePen(0,0,0x808080);

	LOGBRUSH lbr;
	lbr.lbHatch=0; lbr.lbStyle=0; 
	lbr.lbColor=bgColor;
	HBRUSH nullBrush=CreateBrushIndirect(&lbr);
	lbr.lbColor=0xFFEfE8;
	HBRUSH currentBrush=CreateBrushIndirect(&lbr);
	lbr.lbColor=0x70FF70;
	HBRUSH pcBrush=CreateBrushIndirect(&lbr);

	HPEN oldPen=(HPEN)SelectObject(hdc,nullPen);
	HBRUSH oldBrush=(HBRUSH)SelectObject(hdc,nullBrush);

   
	HFONT oldFont = (HFONT)SelectObject(hdc,(HGDIOBJ)font);
//	HICON breakPoint = (HICON)LoadIcon(GetModuleHandle(0),(LPCSTR)IDI_STOP);
//	HICON breakPointDisable = (HICON)LoadIcon(GetModuleHandle(0),(LPCSTR)IDI_STOPDISABLE);

	int nc = cpu->GetNumCategories();
	for (int i=0; i<nc; i++)
	{
		SelectObject(hdc,i==category?currentPen:nullPen);
		SelectObject(hdc,i==category?pcBrush:nullBrush);
		Rectangle(hdc,width*i/nc,0,width*(i+1)/nc,rowHeight);
		const TCHAR *name = cpu->GetCategoryName(i);
		TextOut(hdc,width*i/nc,1,name,(int)strlen(name));
	}

	int numRows=rect.bottom/rowHeight;

	for (int i=0; i<numRows; i++)
	{
		int rowY1 = rowHeight*(i+1);
		int rowY2 = rowHeight*(i+2);


		lbr.lbColor = i==selection?0xffeee0:0xffffff;

		SelectObject(hdc,currentBrush);
		SelectObject(hdc,nullPen);
		Rectangle(hdc,0,rowY1,16,rowY2);

		if (selecting && i == selection)
			SelectObject(hdc,selPen);
		else
			SelectObject(hdc,nullPen);

		HBRUSH mojsBrush=CreateBrushIndirect(&lbr);
		SelectObject(hdc,mojsBrush);

		//else
		//	SelectObject(hdc,i==0 ? currentBrush : nullBrush);

		Rectangle(hdc,16,rowY1,width,rowY2);

		// Check for any changes in the registers.
		if (lastPC != cpu->GetPC())
		{
			for (int j = 0, n = cpu->GetNumRegsInCategory(0); j < n; ++j)
			{
				u32 v = cpu->GetRegValue(0, j);
				changedCat0Regs[j] = v != lastCat0Values[j];
				lastCat0Values[j] = v;
			}
			
			changedCat0Regs[REGISTER_PC] = cpu->GetPC() != lastCat0Values[REGISTER_PC];
			lastCat0Values[REGISTER_PC] = cpu->GetPC();
			changedCat0Regs[REGISTER_HI] = cpu->GetHi() != lastCat0Values[REGISTER_HI];
			lastCat0Values[REGISTER_HI] = cpu->GetHi();
			changedCat0Regs[REGISTER_LO] = cpu->GetLo() != lastCat0Values[REGISTER_LO];
			lastCat0Values[REGISTER_LO] = cpu->GetLo();

			lastPC = cpu->GetPC();
		}

		SelectObject(hdc,currentBrush);
		DeleteObject(mojsBrush);
		if (i<cpu->GetNumRegsInCategory(category))
		{
			char temp[256];
			int temp_len = sprintf(temp,"%s",cpu->GetRegName(category,i));
			SetTextColor(hdc,0x600000);
			TextOut(hdc,17,rowY1,temp,temp_len);
			SetTextColor(hdc,0x000000);

			cpu->PrintRegValue(category,i,temp);
			if (category == 0 && changedCat0Regs[i])
				SetTextColor(hdc, 0x0000FF);
			else
				SetTextColor(hdc,0x004000);
			TextOut(hdc,77,rowY1,temp,(int)strlen(temp));
		} else if (category == 0 && i < REGISTERS_END)
		{
			char temp[256];
			int len;
			u32 value;

			switch (i)
			{
			case REGISTER_PC:
				value = cpu->GetPC();
				len = sprintf(temp,"pc");
				break;
			case REGISTER_HI:
				value = cpu->GetHi();
				len = sprintf(temp,"hi");
				break;
			case REGISTER_LO:
				value = cpu->GetLo();
				len = sprintf(temp,"lo");
				break;
			}

			SetTextColor(hdc,0x600000);
			TextOut(hdc,17,rowY1,temp,len);
			len = sprintf(temp,"%08X",value);
			if (changedCat0Regs[i])
				SetTextColor(hdc, 0x0000FF);
			else
				SetTextColor(hdc,0x004000);
			TextOut(hdc,77,rowY1,temp,(int)strlen(temp));
		}

		/*
			}
			SetTextColor(hdc,0x007000);

			TextOut(hdc,70,rowY1,dis,strlen(dis));
			if (desc[0]==0)
				strcpy(desc,debugger->getDescription(address));
			SetTextColor(hdc,0x0000FF);
			//char temp[256];
			//UnDecorateSymbolName(desc,temp,255,UNDNAME_COMPLETE);
			if (strlen(desc))
				TextOut(hdc,280,rowY1,desc,strlen(desc));
			if (debugger->isBreakpoint(address))
			{
				DrawIconEx(hdc,2,rowY1,breakPoint,32,32,0,0,DI_NORMAL);
			}
		}*/
	}

	SelectObject(hdc,oldFont);
	SelectObject(hdc,oldPen);
	SelectObject(hdc,oldBrush);
	
	DeleteObject(nullPen);
	DeleteObject(currentPen);
	DeleteObject(selPen);

	DeleteObject(nullBrush);
	DeleteObject(pcBrush);
	DeleteObject(currentBrush);
	
//	DestroyIcon(breakPoint);
//	DestroyIcon(breakPointDisable);
	
	EndPaint(wnd, &ps);
}