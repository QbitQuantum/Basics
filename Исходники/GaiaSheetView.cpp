void GaiaSheetView::OnPaint()
{
	this->creatTree();
	CPaintDC dc(this); // device context for painting
	// TODO: ¿©±â¿¡ ¸Þ½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	// ±×¸®±â ¸Þ½ÃÁö¿¡ ´ëÇØ¼­´Â GaiaGaiaCView::OnPaint()À»(¸¦) È£ÃâÇÏÁö ¸¶½Ê½Ã¿À.
	CRect _rect;
	this->GetClientRect(&_rect);
	DblBufMaker dm(&dc, _rect);
	CDC& bDC = dm.GetDC();
	CBrush brush(SingleTon<GaiaLayoutRepo>::use()->Getleftside());
	CRect rect;
	this->GetClientRect(&rect);
	bDC.FillRect(&rect, &brush);
	/////////////////////////
	CFont hfont;
	CFont cfont;
	hfont.CreateFont(20,                     // ±ÛÀÚ³ôÀÌ
		8,                     // ±ÛÀÚ³Êºñ
		0,                      // Ãâ·Â°¢µµ
		0,                      // ±âÁØ ¼±¿¡¼­ÀÇ°¢µµ
		FW_HEAVY,              // ±ÛÀÚ±½±â
		FALSE,                  // Italic Àû¿ë¿©ºÎ
		FALSE,                  // ¹ØÁÙÀû¿ë¿©ºÎ
		FALSE,                  // Ãë¼Ò¼±Àû¿ë¿©ºÎ
		DEFAULT_CHARSET,       // ¹®ÀÚ¼ÂÁ¾·ù
		OUT_DEFAULT_PRECIS,    // Ãâ·ÂÁ¤¹Ðµµ
		CLIP_DEFAULT_PRECIS,   // Å¬¸®ÇÎÁ¤¹Ðµµ
		DEFAULT_QUALITY,       // Ãâ·Â¹®ÀÚÇ°Áú
		DEFAULT_PITCH,         // ±Û²ÃPitch
		_T("Time New Romans")           // ±Û²Ã
		);
	cfont.CreateFont(17,                     // ±ÛÀÚ³ôÀÌ
		7,                     // ±ÛÀÚ³Êºñ
		0,                      // Ãâ·Â°¢µµ
		0,                      // ±âÁØ ¼±¿¡¼­ÀÇ°¢µµ
		FW_HEAVY,              // ±ÛÀÚ±½±â
		FALSE,                  // Italic Àû¿ë¿©ºÎ
		FALSE,                  // ¹ØÁÙÀû¿ë¿©ºÎ
		FALSE,                  // Ãë¼Ò¼±Àû¿ë¿©ºÎ
		DEFAULT_CHARSET,       // ¹®ÀÚ¼ÂÁ¾·ù
		OUT_DEFAULT_PRECIS,    // Ãâ·ÂÁ¤¹Ðµµ
		CLIP_DEFAULT_PRECIS,   // Å¬¸®ÇÎÁ¤¹Ðµµ
		DEFAULT_QUALITY,       // Ãâ·Â¹®ÀÚÇ°Áú
		DEFAULT_PITCH,         // ±Û²ÃPitch
		_T("Time New Romans")           // ±Û²Ã
		);
	bDC.SetTextColor(RGB(222, 200, 200));
	bDC.SetBkMode(TRANSPARENT);
	bDC.SelectStockObject(NULL_PEN);
	/////////////////////////
	CRect title(15, 15, 160, 50);
	CPen pen;
	bDC.SetTextColor(RGB(0, 122, 204));
	bDC.SelectObject(&hfont);
	//bDC.SetBkMode(TRANSPARENT);
	pen.CreatePen(PS_DOT, 2, RGB(0, 122, 204));
	CPen* op = bDC.SelectObject(&pen);

	bDC.MoveTo(title.left, title.bottom);
	bDC.LineTo(title.right, title.bottom);
	bDC.DrawText(_T("LIST"), &title, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	bDC.SelectObject(op);
	bDC.SetTextColor(RGB(222, 200, 200));
	/////////////////////////
	this->btnRect.clear();
	this->velem.clear();
	vector<const SheetElement*>& cvme = this->velem;
	int currID = this->currentID;
	if (currID == 0){
		for (vector<SheetElement>::iterator iter = elems.begin(); iter != elems.end(); ++iter){
			if (iter->parentID == 0)
				cvme.push_back(&(*iter));
		}
	}
	else{
		for (vector<SheetElement>::iterator iter = elems.begin(); iter != elems.end(); ++iter){
			if (iter->parentID == 0 || iter->parentID == currID)
				cvme.push_back(&(*iter));
		}
	}
	CRect myRect(CPoint(5, 85), CPoint(25, 105));
	CRect a(CPoint(55, 85), CPoint(135, 105));
	CRect b(CPoint(35, 85), CPoint(115, 105));
	int m = 20;
	for (int i = 0; i < velem.size(); i++){
		CBrush _brush(velem[i]->color);
		bDC.SelectObject(&_brush);
		CRect temp = velem[i]->topID != 1 ? a : b;
		temp.top = temp.top + m - 20;
		temp.bottom = temp.top + 20;
		btnRect.push_back(temp);
		m = temp.Height() + m + 20;
		bDC.SelectObject(&hfont);
		if (flag != -1 && seln == i){// Ä¿¼­°¡ ¿µ¿ª¾È¿¡ µé¾î¿À¸é
			bDC.SetTextColor(velem[i]->color);
			flag = -1;
		}
		if (velem[i]->topID != 1){	// ÀÚ½ÄÀÌ¸é
			if (selNum == i){		// ¼±ÅÃµÇ¾úÀ»‹š Ã¼Å©±×¸²À» Âï´Â´Ù
				CDC memDC;
				memDC.CreateCompatibleDC(&bDC);
				CBitmap bmp;
				bmp.LoadBitmapW(IDB_CHECK);
				BITMAP bmpinfo;
				bmp.GetBitmap(&bmpinfo);
				memDC.SelectObject(&bmp);
				bDC.TransparentBlt(btnRect[selNum].right + 25, btnRect[selNum].top - 10, 25, 25, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
				bDC.SetTextColor(velem[i]->color);
			}
			bDC.SelectObject(&cfont);
			bDC.RoundRect(btnRect[i].left - 25, btnRect[i].top, btnRect[i].left - 10, btnRect[i].bottom - 5, 5, 5);
		}
		else{
			bDC.RoundRect(btnRect[i].left - 30, btnRect[i].top, btnRect[i].left - 10, btnRect[i].bottom, 5, 5);
		}
		bDC.TextOutW(btnRect[i].left, btnRect[i].top, velem[i]->name);
		bDC.SetTextColor(RGB(222, 200, 200));
		_brush.DeleteObject();
	}
	this->elems.clear();
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &bDC, 0, 0, SRCCOPY);
	brush.DeleteObject();
}