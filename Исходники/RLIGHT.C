TANY PEXPORT KpiDrawRectLight(OBJECTID idSelf, LPSTR ap)
{
    WORD wType = OBJECT_TYPE(idSelf);
    ATOMID idWidget = va_far_arg(ap, ATOMID);
    short sXL, sHeight = 0;
    char *Context = "Context";
    ATOMID idOwner =
        Kpp_Get_SlotValue(wType, idSelf, lpSNs->idOwnerSN);
    ATOMID idOwnerSlot =
        Kpp_Get_SlotValue(wType, idSelf, lpSNs->idOwnerSlotSN);
    WORD wMaxWidth, wTextHeight, wTitleHgt;
    BOOL bOwnerValues = FALSE;
    short sBkMode;
    HDC hDC;
    HWND hWnd;
    ATOMID idDesc, idValue = NULLID, idItem;
    LISTID idPossValues;
    WORD wNumPossValues, wRectWidth;
    RECT rect;
    HBRUSH hRedBrush, hWhiteBrush, hOldBrush;
    HFONT hOldFont;
    DWORD dwTextColor;
    TANY res;
    
    res.type = T_CBOOL;
    res.data.cbool = FALSE;
    
    KppGetAtomInt(Kpp_Get_SlotValue(wType, idSelf, lpSNs->idWinIdSN),
		  (int *) &hWnd);
    if (!hWnd)
        return res;

    hDC = GetProp(hWnd, Context);
    if (!hDC)
        hDC = GetDC(hWnd);

    if (idOwner != lpIDs->idNull && idOwnerSlot != lpIDs->idNull)
    {
        idValue = KppGetSlotValue(idOwner, idOwnerSlot);
        idPossValues = KppGetOption(idOwner, idOwnerSlot, OPT_PV);
        wNumPossValues = KppListLen(idPossValues);

        if (wNumPossValues > 0)
            bOwnerValues = TRUE;
    }

    if (!bOwnerValues)
    {
        idPossValues = Kpp_Get_SlotListValue(wType, idSelf,
                                             lpSNs->idPossValuesSN);
        wNumPossValues = KppListLen(idPossValues);
    }

    if (!idValue || idValue == lpIDs->idNull)
        idValue = Kpp_Get_SlotValue(wType, idSelf, lpSNs->idValueSN);

    if (wNumPossValues <= 0)
    {
        if (!GetProp(hWnd, Context))
            ReleaseDC(hWnd, hDC);
        return res;
    }

    idDesc = Kpp_Get_SlotValue(wType, idSelf, lpSNs->idTitleSN);
    SetTextColor(hDC, BLACK);

    hOldFont = KpsSetWidgetFont(idWidget, hDC, FALSE, 1.0);
    wMaxWidth = DetRStringWidths(hDC, idPossValues, idDesc, 
                                 &wRectWidth, &wTextHeight);

    SetupRLightMapping(hWnd, hDC, wMaxWidth, wTextHeight, wNumPossValues);

    sXL = (short) ((double) wMaxWidth / 2.0);

    if (hOldFont)
        SelectObject(hDC, hOldFont);

    if (idDesc != lpIDs->idNull)
    {
        WORD wLen = KppGetAtomName(idDesc, pBuffer, 50);
        HBRUSH hBrBack = KpsSetWidgetTextColor(idWidget, hDC, NULL);
        DWORD dwExtent;
        
        hOldFont = KpsSetWidgetFont(idWidget, hDC, TRUE, 1.0);
        SetBkMode(hDC, TRANSPARENT);

        dwExtent = GetTextExtent(hDC, pBuffer, wLen);
        wMaxWidth = LOWORD(dwExtent);
        wTitleHgt = HIWORD(dwExtent);
        sXL = (short) ((double) wMaxWidth / 2.0);
        sHeight = HALF_VERT_PAD + wTitleHgt;
        FILLRECT(rect, -sXL, sHeight, sXL, sHeight - wTitleHgt);
        DrawText(hDC, pBuffer, wLen, &rect, DT_CENTER);

        if (hOldFont)
        {
            SelectObject(hDC, hOldFont);
            hOldFont = NULL;
        }
        DeleteObject(hBrBack);
        SetTextColor(hDC, BLACK);
    }

    hOldFont = KpsSetWidgetFont(idWidget, hDC, FALSE, 1.0);

    sXL = (short) ((double) wRectWidth / 2.0);
    sHeight += (VERT_PAD + HALF_VERT_PAD);

    /* Prepare fonts && brushes */
    sBkMode = GetBkMode(hDC);
    hRedBrush = CreateSolidBrush(RGB(255, 0, 0));

    hWhiteBrush = KpsSetWidgetText2Color(idWidget, hDC, NULL);
    dwTextColor = GetTextColor(hDC);

    hOldBrush = SelectObject(hDC, hWhiteBrush);

    /* Begin looping && draw possible values */
    if (idPossValues && idPossValues != lpIDs->idNull)
    {
        LIST_LOOP loop;
        
        kpc_init_loop(idPossValues, &loop);
        while (idItem = KppNextListElement(&loop)) {
            WORD wLen = KppGetAtomName(idItem, pBuffer, 32);

            sHeight += (VERT_PAD + wTextHeight);

            SelectObject(hDC, hWhiteBrush);
            ECHO_ROUNDRECT(hDC, sXL, sHeight, wTextHeight);

            if (idValue == idItem)
            {
                SelectObject(hDC, hRedBrush);
                SetTextColor(hDC, RGB(255, 255, 255));
            }
            else
            {
                SelectObject(hDC, hWhiteBrush);
                SetTextColor(hDC, dwTextColor);
            }
            DRAW_ROUNDRECT(hDC, sXL, sHeight, wTextHeight);

            FILLRECT(rect, -sXL, sHeight, sXL, sHeight - wTextHeight);

            SetBkMode(hDC, TRANSPARENT);
            DrawText(hDC, pBuffer, wLen, &rect, DT_CENTER);
            SetBkMode(hDC, OPAQUE);
            sHeight += VERT_PAD;
        }
    }

    Kpp_Set_SlotValue(wType, idSelf, lpSNs->idValueSN, idValue, EXPATOM);

    /* Restore the fonts && brushes */
    SetBkMode(hDC, sBkMode);
    SelectObject(hDC, hOldFont);
    SelectObject(hDC, hOldBrush);
    DeleteObject(hRedBrush);
    SetTextColor(hDC, dwTextColor);

    if (!GetProp(hWnd, Context))
        ReleaseDC(hWnd, hDC);
    
    res.data.cbool = TRUE;
    return res;
}