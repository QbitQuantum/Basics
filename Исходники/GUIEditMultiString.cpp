GUIEditMultiString::GUIEditMultiString(int32 bufSize/* = MAX_SIZE*/, eEditTextType eeType/* = EETT_ALL*/, GUIControlContainer * parent, const ControlRect &cr)
	:	GUIInputText		(eeType)
	,	GUIMultiString		((char16 *)NULL, parent, cr)
	,	isResizeable		(false)
{
	SetEditType(eeType);
	SetSelectable(true);


	SAFE_DELETE_ARRAY(GUIMultiString::textBuffer);
	GUIMultiString::bufferSize		=	bufSize;
	GUIMultiString::textBuffer		=	new char16[bufSize];

	GUIInputText::SetText(GUIMultiString::textBuffer, GUIMultiString::textSize, GUIMultiString::bufferSize);

	SetTextAlign(Font::EAP_LEFT | Font::EAP_VCENTER);
}