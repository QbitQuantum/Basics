/// @brief Issues an event without attached data to the widget of choice
/// @param type Type of event to issue
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void UserInterface::IssueBasicEvent (WidgetEventType type, void * pContext)
{
	void (*processEvent)(Uint32, WidgetEventType, void *) = Widget::Get(mChoice).mProcessEvent;

	if (processEvent != 0) processEvent(mChoice, type, pContext);
}