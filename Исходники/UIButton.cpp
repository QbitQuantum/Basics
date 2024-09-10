bool CUIButton::OnKeyboard(int dik, EUIMessages keyboard_action)
{
	if (WINDOW_KEY_PRESSED == keyboard_action)
	{
		if(IsAccelerator(dik) )
		{
			OnClick		();
			return		true;
		}
	}
	return inherited::OnKeyboard(dik, keyboard_action);
}