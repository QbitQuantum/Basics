OpWidget* WidgetCreator::CreateWidget()
{
	OpWidget* widget = ConstructWidgetForType();

	if (!widget)
		return 0;

	const BOOL add_as_first = OpTypedObject::WIDGET_TYPE_HELP_TOOLTIP == m_widget_type;
	
	m_parent->AddChild(widget, FALSE, add_as_first);

	if (m_action)
	{
		widget->SetAction(m_action);
		m_action = 0;
	}

	// Set resize effect first.  Subsequent widget configuration calls might
	// cause the widget to be updated for RTL.
	widget->SetXResizeEffect(GetXResizeEffect(m_resize_flags));
	widget->SetYResizeEffect(GetYResizeEffect(m_resize_flags));

	widget->SetStringID(m_string_id);
	widget->SetText(m_text.CStr());
	widget->SetName(m_name.CStr());
	widget->SetRect(m_rect);
	widget->SetOriginalRect(m_rect);

	if (OpStatus::IsError(widget->init_status))
	{
		widget->Delete();
		return 0;
	}

	return widget;
}