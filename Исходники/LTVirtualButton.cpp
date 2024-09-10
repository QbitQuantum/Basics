//**************************************************************************************************
void LTThemeButton::OnPaintButtonState( CDC* pDC )
{
	if (!p_Owner->PaintBack(this, pDC, r_Area))
	{
		if (pi_BackColor)
			pDC->FillSolidRect(r_Area, *pi_BackColor);
	}

	DrawThemeBackground(*ph_Theme, pDC->m_hDC, i_Part, i_State + i_StateOffset, r_Area, *pr_Clip);
	//LTVirtualButton::OnPaintButtonState(pDC);
}