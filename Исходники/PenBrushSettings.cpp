//WM_DRAWITEM
void PBSettings_OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT * lpDrawItem)
{
	//Get the PBSDP
	PenBrushSettingsDlgParam * pbsdp=(PenBrushSettingsDlgParam *)(LONG_PTR)GetWindowLongPtr(hwnd,GWLP_USERDATA);
	switch(lpDrawItem->CtlID) //Controls switch
	{
	case IDC_PB_PREVIEW: //Preview pane
		{
			RECT fillRct=lpDrawItem->rcItem;
			HRGN fillRgn=CreateRectRgnIndirect(&fillRct);
			ArrowSettings tas=UITC->GetTool<UIArrowline>(IDC_TB_ARROWLINE)->GetArrowSettings();
			//Paint the background with a white brush
			FillRgn(lpDrawItem->hDC,fillRgn,(HBRUSH)GetStockObject(WHITE_BRUSH));
			//Select the pen and the brush and set the appropriate settigns
			BEGIN_SELOBJ(lpDrawItem->hDC,pbsdp->GetPreviewPaneFGCU().GetPen(),hDC_pen);
			BEGIN_SELOBJ(lpDrawItem->hDC,pbsdp->GetPreviewPaneBGCU().GetBrush(),hDC_brush);
			pbsdp->GetPreviewPaneFGCU().ApplyACUPs(lpDrawItem->hDC);
			//Draw a filled rectangle in the left part of the rectangle
			Rectangle(lpDrawItem->hDC,fillRct.left+5,fillRct.top+5,(fillRct.right-fillRct.left)/2-5,fillRct.bottom-5);
			//Draw a filled arrow in the top right part of the rectangle
			MoveToEx(lpDrawItem->hDC,(fillRct.right-fillRct.left)/2+5,fillRct.top+5,NULL);
			tas.drawSecondArrow=true;
			ArrowTo(lpDrawItem->hDC,fillRct.right-5,fillRct.bottom-25,&tas);
			//Draw a line in the bottom right part of the rectangle
			MoveToEx(lpDrawItem->hDC,(fillRct.right-fillRct.left)/2+5,fillRct.bottom-15,NULL);
			LineTo(lpDrawItem->hDC,fillRct.right-5,fillRct.bottom-5);
			//Deselect the pen and the brush
			END_SELOBJ(lpDrawItem->hDC,hDC_brush);
			END_SELOBJ(lpDrawItem->hDC,hDC_pen);
			DeleteRgn(fillRgn);
			break;
		} //End IDC_PB_PREVIEW
	case IDC_PB_B_COLOR: //Color panes
	case IDC_PB_H_COLORP:
		{
			HBRUSH hbr=CreateSolidBrush((lpDrawItem->CtlID==IDC_PB_B_COLOR?pbsdp->GetCurrentCU().GetColor():pbsdp->GetCurrentCU().GetACUPs().bgColor));
			FillRect(lpDrawItem->hDC,&lpDrawItem->rcItem,hbr);
			DeleteBrush(hbr);
			break;
		} //End IDC_PB_B_COLOR
	}
}