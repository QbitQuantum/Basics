//设置最前
void CCommonWidget::Foreground(bool abShowFirst/* = true*/)
{
	if(abShowFirst)
	{
		show();
	}
	SwitchToThisWindow(winId(), TRUE);
}