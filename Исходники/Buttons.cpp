void Buttons::render(ComPtr<ID2D1RenderTarget> d2dTarget)
{
	ComPtr<ID2D1SolidColorBrush> bgBrush;
	d2dTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White), bgBrush.Receive());
	ComPtr<ID2D1SolidColorBrush> borderBrush;
	d2dTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black), borderBrush.Receive());

	int cur = 0;
	for (ChoiceList::const_iterator it = m_choices.begin(); it != m_choices.end(); ++it)
	{
		d2dTarget->FillRectangle(it->rect, bgBrush);
		d2dTarget->DrawTextW(it->text.c_str(), it->text.size(), m_textFormat,
			it->rect, borderBrush);
		d2dTarget->DrawRectangle(it->rect, borderBrush,
			cur == m_selection ? 3.0f : 1.0f);

		++cur;
	}
}