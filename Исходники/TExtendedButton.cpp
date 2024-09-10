void TExtendedButton::DrawControl(void)
{
    EDrawingMode iDrawingMode;
    TCanvas      *oCanvas;
    long         lStartColor;
    long         lEndColor;
    long         lBorderColor;
    short        iTextDeviation;
    RECT		 oArea;

    this->FDrawingBuffer->Width  = this->Width;
    this->FDrawingBuffer->Height = this->Height;
    oCanvas = this->FDrawingBuffer->Canvas;
    oCanvas->Font = this->Font;

    //---------------------------------------------------------------------------
    // Find the drawing mode
    iDrawingMode = DM_NORMAL;

    if (::GetAsyncKeyState(VK_LBUTTON) == 0)
    {
        if (PtInRect(this->Canvas->ClipRect, this->ScreenToClient(Mouse->CursorPos)) == true)
            iDrawingMode = DM_HOT;
    }
    else
    {
        if (PtInRect(this->Canvas->ClipRect, this->ScreenToClient(Mouse->CursorPos)) == false)
        {
            if (this->FFocused == true)
                iDrawingMode = DM_HOT;
        }
        else
            iDrawingMode = DM_DOWN;
    }
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Define which colors to use for painting
    switch (iDrawingMode)
    {
        case DM_NORMAL:
            lStartColor    = this->StartColor;
            lEndColor      = this->EndColor;
            lBorderColor   = this->BorderColor;
            iTextDeviation = 0;
            oCanvas->Font->Color = Graphics::clBlack;
            break;

        case DM_DOWN:
            lStartColor    = this->FBase->DarkenColor(this->EndColor, 20);
            lEndColor      = this->FBase->DarkenColor(this->StartColor, 20);
            lBorderColor   = this->FBase->DarkenColor(this->BorderColor, 50);
            iTextDeviation = 1;
            oCanvas->Font->Color = Graphics::clBlack;
            break;

        case DM_HOT:
            lStartColor    = this->FBase->LightenColor(this->StartColor, 100);
            lEndColor      = this->FBase->LightenColor(this->EndColor, 100);
            lBorderColor   = this->FBase->LightenColor(this->BorderColor, 100);
            iTextDeviation = 0;
            oCanvas->Font->Color = Graphics::clGray;
            break;

        default:
            lStartColor    = this->StartColor;
            lEndColor      = this->EndColor;
            lBorderColor   = this->BorderColor;
            iTextDeviation = 0;
            break;
    }
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Perform the actual drawing
    this->FBase->FillGradient(oCanvas->Handle, oCanvas->ClipRect, lStartColor, lEndColor, comn::OT_DIAGONAL);
    oCanvas->Pen->Color   = (TColor)lBorderColor;
    oCanvas->Brush->Style = Graphics::bsClear;
    oCanvas->RoundRect(oCanvas->ClipRect.Left, oCanvas->ClipRect.Top, oCanvas->ClipRect.Right, oCanvas->ClipRect.Bottom, 6, 6);
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Draw the image if required
    if (this->ImageID != comn::BI_NONE && this->DrawImage == true)
    {
        oArea.left   = 2;
        oArea.top    = 2;
        oArea.right  = this->Width - 2;
        oArea.bottom = this->Height - 2;

        if (iDrawingMode == DM_DOWN)
        {
            oArea.left++;
            oArea.top++;
            oArea.right++;
            oArea.bottom++;
        }

        this->FBase->DrawBitmap(oCanvas->Handle, oArea, this->ImageID, true);
    }
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Draw a closing cross if required
    if (this->DrawCross == true)
    {
        oCanvas->Brush->Style = Graphics::bsSolid;
        oCanvas->Pen->Color   = (TColor)lBorderColor;
        oCanvas->Pen->Width   = 1;

        oCanvas->MoveTo(oCanvas->ClipRect.Left + 1,  oCanvas->ClipRect.Top + 1);
        oCanvas->LineTo(oCanvas->ClipRect.Right - 1, oCanvas->ClipRect.Bottom - 1);
        oCanvas->MoveTo(oCanvas->ClipRect.Right - 2, oCanvas->ClipRect.Top + 1);
        oCanvas->LineTo(oCanvas->ClipRect.Left, oCanvas->ClipRect.Bottom - 1);
    }
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Draw the caption
	::DrawText(oCanvas->Handle, AnsiString(this->Caption).c_str(), this->Caption.Length(), &oArea, DT_CALCRECT);

    oArea.left   = 0 + iTextDeviation;
    oArea.top    = 0 + iTextDeviation;
    oArea.right  = oCanvas->ClipRect.Width() + iTextDeviation;
    oArea.bottom = oCanvas->ClipRect.Height() + iTextDeviation;

    ::SetBkMode(oCanvas->Handle, TRANSPARENT);
	::DrawText(oCanvas->Handle, AnsiString(this->Caption).c_str(), this->Caption.Length(), &oArea, DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
    //---------------------------------------------------------------------------

    //---------------------------------------------------------------------------
    // Output the drawing into screen
    this->FPaintBox->Canvas->Draw(0, 0, this->FDrawingBuffer);
    //---------------------------------------------------------------------------

    return;
}