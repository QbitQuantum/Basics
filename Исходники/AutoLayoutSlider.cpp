int AutoLayoutSlider::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	this->_sliderCtrl.Create(WS_CHILD | WS_VISIBLE, rectDummy, this, 1);
	this->_sliderCtrl.SetRange(0, 80, 1);	// hard code!!!

	return 0;
}