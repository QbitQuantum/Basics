void TBRadioCheckBox::SetValue(int value)
{
	if (m_value == value)
		return;
	m_value = value;

	SetState(WIDGET_STATE_SELECTED, value ? true : false);

	Invalidate();
	TBWidgetEvent ev(EVENT_TYPE_CHANGED);
	InvokeEvent(ev);

	if (!value || !GetGroupID())
		return;
	// Toggle all other widgets in the same group. First get a root widget
	// for the search.
	TBWidget *group = this;
	while (group && !group->GetIsGroupRoot())
		group = group->GetParent();
	if (group)
	{
		ToggleGroup(group, this);
	}
}