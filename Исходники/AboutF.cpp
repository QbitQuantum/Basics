void __fastcall TfrmAbout::WMPaletteChanged(TMessage& Msg)
{

	if (hPalette != NULL && (HWND) Msg.WParam != Handle) {
	    UnrealizeObject(hPalette);
	    SelectPalette(hDC, hPalette, FALSE);
	    RealizePalette(hDC);
	    redraw();
  }

}