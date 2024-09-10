void PersonEditorPane::setNameObject (const Person &nameObject)
{
	if (!isBlank (nameObject.lastName))
	{
		ui.lastNameInput->setText (nameObject.lastName);
		ui.lastNameInput->setEnabled (false);
	}

	if (!isBlank (nameObject.firstName))
	{
		ui.firstNameInput->setText (nameObject.firstName);
		ui.firstNameInput->setEnabled (false);
	}
}