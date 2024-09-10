//////////
//
// Called to render the Debo1 window.
// Note:  Renders into the bmpDebo1->hdc bitmap for later copying with BitBlt().
// Note:  The file debo-1.png was used as a template for this construction.
//
//////
	void iiDebo1_render(void)
	{
		RECT lrc;


		//////////
		// Render the sub-components
		//////
			iiDebo1_renderStage1();
			iiDebo1_renderStage2();
			iiDebo1_renderStage3();
			iiDebo1_renderStage4();
			iiDebo1_renderStage5();
			iiDebo1_renderRegisters();
			iiDebo1_renderDisassembly();
			iiDebo1_renderMemory();


		//////////
		// The main window has a white background, and then each component is rendered atop
		//////
			FillRect(bmpDebo1->hdc, &bmpDebo1->rc, (HBRUSH)GetStockObject(WHITE_BRUSH));


		//////////
		// Title
		//////
			CopyRect(&lrc, &bmpDebo1->rc);
			--lrc.top;
			lrc.left += 8;
			SelectObject(bmpDebo1->hdc, fontUbuntu14->hfont);
			SetBkMode(bmpDebo1->hdc, TRANSPARENT);
			SetTextColor(bmpDebo1->hdc, RGB(titleColor.red, titleColor.grn, titleColor.blu));
			DrawText(bmpDebo1->hdc, cgcAppTitle, strlen(cgcAppTitle), &lrc, DT_LEFT);


		//////////
		//  Pipeline stages
		//////
			BitBlt(bmpDebo1->hdc, 5, 28,	bmpStage1->bi.biWidth, bmpStage1->bi.biHeight, bmpStage1->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpDebo1->hdc, 78, 28,	bmpStage2->bi.biWidth, bmpStage2->bi.biHeight, bmpStage2->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpDebo1->hdc, 178, 28,	bmpStage3->bi.biWidth, bmpStage3->bi.biHeight, bmpStage3->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpDebo1->hdc, 278, 9,	bmpStage4->bi.biWidth, bmpStage4->bi.biHeight, bmpStage4->hdc, 0, 0, SRCCOPY);
			BitBlt(bmpDebo1->hdc, 528, 28,	bmpStage5->bi.biWidth, bmpStage5->bi.biHeight, bmpStage5->hdc, 0, 0, SRCCOPY);


		//////////
		// Registers
		//////
			BitBlt(bmpDebo1->hdc, 618, 2,	bmpRegisters->bi.biWidth, bmpRegisters->bi.biHeight, bmpRegisters->hdc, 0, 0, SRCCOPY);


		//////////
		// Disassembly
		//////
			BitBlt(bmpDebo1->hdc, 618, 173,	bmpDisassembly->bi.biWidth, bmpDisassembly->bi.biHeight, bmpDisassembly->hdc, 0, 0, SRCCOPY);


		//////////
		// Memory
		//////
			BitBlt(bmpDebo1->hdc, 0, 154,	bmpMemory->bi.biWidth, bmpMemory->bi.biHeight, bmpMemory->hdc, 0, 0, SRCCOPY);
	}