int AutoLayoutPanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  Add your specialized creation code here
    CRect rectDummy;
    rectDummy.SetRectEmpty();
    this->slider.Create(WS_CHILD | WS_VISIBLE, rectDummy, this, ID_SLIDER);
    this->slider.SetRange(0, 80, 1);	// hard code!!!

    return 0;
}