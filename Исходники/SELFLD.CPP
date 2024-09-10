void SelectionField::setToDefault()
{
	selection = defaultSelection;
	if( getWindow() )
		getWindow()->update();
}