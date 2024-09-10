void TBTextFragmentContentWidget::UpdatePos(int x, int y)
{
	m_widget->SetRect(TBRect(x, y, GetWidth(nullptr, nullptr), GetHeight(nullptr, nullptr)));
}