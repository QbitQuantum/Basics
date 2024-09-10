void MacPrinterCanvas::finish() {
	if (!hdc) {return;}
	endPaint();
	//if (!Escape(hdc, NEWFRAME, 0, NULL, NULL)) {
		//DebugMessage("NEWFRAME failed\n");
	//	abort();
	//}
	//if (!Escape(hdc, ENDDOC, 0, NULL, NULL)) {
		//DebugMessage("ENDDOC failed\n");
	//	abort();
	//}
	EndPage(hdc);
	EndDoc(hdc);
	DeleteDC(hdc);
	hdc = 0;
}