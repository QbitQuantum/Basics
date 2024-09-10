void PanelObjectsList::mousePressed(MyGUI::WidgetPtr _widget) 
{	
	EditorFrameHandler *handler = EditorFrameListener::GetInstance()->GetCurrentHandler();
	
	size_t count = mItemsCheckBox.size();
	for (size_t pos=0; pos<count; ++pos) 
	{
		((MyGUI::ButtonPtr)mItemsCheckBox[pos])->setStateCheck(false);
	}
		
	if (handler->SelectObject(_widget->getCaption()))
		((MyGUI::ButtonPtr)_widget)->setStateCheck(true);
	else
		((MyGUI::ButtonPtr)_widget)->setStateCheck(false);
}