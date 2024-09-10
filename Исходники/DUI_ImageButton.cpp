VOID DUI_ImageButton::Draw(DUI_Status s)
{
	m_MemDC->Clear();
	if (m_bVisialbe)
	{
		if (s == S_Invalid)
		{
			s = m_CurState;
		}
		Image* pImg;
		if (m_StatusImage[0] == nullptr)
		{
			pImg = m_StatusImage[s];
			//ASSERT(pImg != nullptr);
			m_MemDC->graphics->DrawImage(pImg, 0, 0);
		}
		else
		{
			pImg = m_StatusImage[0];
			if (s == S_Focus || s == S_Disabled)
			{
				s = S_Normal;
			}
			m_MemDC->graphics->DrawImage(pImg, RectF(0.0, 0.0, m_Rect->Width, m_Rect->Height), m_Start + (s - 1)*m_Rect->Width, 0.0, m_Rect->Width, m_Rect->Height, UnitPixel);
		}
		if (m_Text != nullptr)
		{
			SolidBrush TextBrush(*m_Text->color);
			INT offset = (m_bMouseDown) ? 1 : 0;
			m_MemDC->graphics->DrawString(m_Text->string->GetString(), m_Text->string->GetLength(), m_Text->font, RectF(m_Text->rect->X + offset, m_Text->rect->Y + offset, m_Text->rect->Width, m_Text->rect->Height), m_Text->format, &TextBrush);
		}
		DUI_ControlBase::Draw();
	}
	return VOID();
}