void OpTabGroupButton::RefreshIndicatorState()
{
	short indicator_state = 0;
	if (!m_group)
	{
		return;
	}
	for (INT32 i = m_group->GetChildIndex(); i <= m_group->GetLastChildIndex(); i++)
	{
		DesktopWindowCollectionItem* item = m_group->GetModel()->GetItemByIndex(i);
		DesktopWindow* window = item->GetDesktopWindow();
		PagebarButton* button = window->GetPagebarButton();
		/* It can happen that DesktopWindow still exists but PagebarButton related
		 * to it is already destroyed when Opera is closing so we have to check if
		 *  button is not NULL.
		 */
		if (button)
		{
			OpIndicatorButton* indicator = button->GetIndicatorButton();
			if (indicator->IsVisible() == TRUE && window != m_group->GetActiveDesktopWindow())
			{
				indicator_state |= indicator->GetIndicatorType();
			}
		}
	}
	m_indicator_button->SetIndicatorType(indicator_state);
	if (!m_group->IsCollapsed())
	{
		m_indicator_button->SetVisibility(FALSE);
	}
	CalculateAndSetMinWidth();
}