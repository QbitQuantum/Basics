void DFF::Draw(CDC* pDC){
	CRect rect(this->base_point.x, this->base_point.y, this->base_point.x + this->GetLength() * 10 - 20, this->base_point.y + this->GetLength() * 10 - 20);
	this->baseRect = rect;
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	switch (radius){
	case 0:
		bmp.LoadBitmapW(IDB_DFF_0);
		this->ins[0].SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 + 5, rect.left, (rect.bottom + rect.top) / 2 + 15);
		this->clk.SetRect(rect.left - 10, (rect.bottom + rect.top) / 2 - 15, rect.left, (rect.bottom + rect.top) / 2 - 5);
		this->outs[0] = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 - 15, rect.right + 5, (rect.bottom + rect.top) / 2 - 5);
		this->outs[1] = CRect(rect.right - 5, (rect.bottom + rect.top) / 2 + 5, rect.right + 5, (rect.bottom + rect.top) / 2 + 15);
		break;
	case 1:
		bmp.LoadBitmapW(IDB_DFF_90);
		this->ins[0] = CRect((rect.left + rect.right) / 2 - 25, rect.top - 10, (rect.left + rect.right) / 2 - 15, rect.top);
		this->clk = CRect((rect.left + rect.right) / 2 + 15, rect.top - 10, (rect.left + rect.right) / 2 + 25, rect.top);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 25, rect.bottom - 3, (rect.left + rect.right) / 2 - 15, rect.bottom + 7);
		this->outs[1] = CRect((rect.left + rect.right) / 2 + 15, rect.bottom - 3, (rect.left + rect.right) / 2 + 25, rect.bottom + 7);
		break;
	case 2:
		bmp.LoadBitmapW(IDB_DFF_180);
		this->ins[0] = CRect(rect.right + 5, (rect.bottom + rect.top) / 2 - 25, rect.right + 15, (rect.bottom + rect.top) / 2 - 15);
		this->clk = CRect(rect.right + 5, (rect.bottom + rect.top) / 2 + 15, rect.right + 15, (rect.bottom + rect.top) / 2 + 25);
		this->outs[0] = CRect(rect.left - 5, rect.top + 5, rect.left + 5, rect.top + 15);
		this->outs[1] = CRect(rect.left - 5, rect.top + 45, rect.left + 5, rect.top + 55);
		break;
	case 3:
		bmp.LoadBitmapW(IDB_DFF_270);
		this->clk = CRect((rect.left + rect.right) / 2 - 25, rect.bottom + 4, (rect.left + rect.right) / 2 - 15, rect.bottom + 14);
		this->ins[0] = CRect((rect.left + rect.right) / 2 + 15, rect.bottom + 4, (rect.left + rect.right) / 2 + 25, rect.bottom + 14);
		this->outs[0] = CRect((rect.left + rect.right) / 2 - 25, rect.top - 5, (rect.left + rect.right) / 2 - 15, rect.top + 5);
		this->outs[1] = CRect((rect.left + rect.right) / 2 + 15, rect.top - 5, (rect.left + rect.right) / 2 + 25, rect.top + 5);
		break;
	}
	static_assert(sizeof(int) == sizeof(LONG), "이 플랫폼은 지원하지않습니다.");
	BITMAP bmpinfo;
	bmp.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bmp);
	pDC->TransparentBlt(this->base_point.x, this->base_point.y, 60, 60, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, RGB(0, 0, 0));
	//글자를 그립니다
}