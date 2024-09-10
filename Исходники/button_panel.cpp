void Button_Panel::SetButtonText(const char* Text)
{
	ButtonText = GetGameUI2().ConvertToLocalizedString(Text);
	ButtonText = wcsupr(ButtonText);
}