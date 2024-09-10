void GEllipse::draw(CDC* dc)
{
	CPen pen(this->getPattern(), this->getThick(), this->getLineColor());
	dc->SelectObject(&pen);
	CBrush brush;
	brush.CreateHatchBrush(this->getFillPattern(), this->getFillColor());	
	
	dc->SelectObject(&brush);
	// 처음에 색이 NULL 이면 투명으로
	if (this->getFillColor() == NULL)
		dc->SelectStockObject(NULL_BRUSH);
			
	// 원 그리기는 여기서부터
	dc->MoveTo(getStartX(), getStartY());
	dc->Ellipse(this->getStartX(), this->getStartY(), GetEnd().x, GetEnd().y);
	if (this->getSelected() == TRUE){
		CPen pen2(PS_SOLID, 0, RGB(0, 0, 0));
		dc->SelectObject(&pen2);
		CBrush brush2(RGB(255, 255, 255));
		dc->SelectObject(&brush2);
		m_selectedRect[0] = new CRect(this->getStartX() - 5, this->getStartY() - 5, this->getStartX() + 5, this->getStartY() + 5);
		m_selectedRect[1] = new CRect(this->getEndX() - 5, this->getStartY() - 5, this->getEndX() + 5, this->getStartY() + 5);
		m_selectedRect[2] = new CRect(this->getStartX() - 5, this->getEndY() - 5, this->getStartX() + 5, this->getEndY() + 5);
		m_selectedRect[3] = new CRect(this->getEndX() - 5, this->getEndY() - 5, this->getEndX() + 5, this->getEndY() + 5); // 메모리 누수의 위험 있음. 수정바람!
		dc->Rectangle(m_selectedRect[0]);
		dc->Rectangle(m_selectedRect[1]);
		dc->Rectangle(m_selectedRect[2]);
		dc->Rectangle(m_selectedRect[3]);
	}
}