// Enable or disable the OK button
void PromptDialog::OnChange() 
{
	SetTimer(TIMER_ID_CHECK_OK, 10, NULL);
}