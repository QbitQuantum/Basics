EditBox* CreateEditBoxFromXML(ticpp::Element* elem, Dialog* /*dlg*/){
	int tmpInt;
	EditBox* box = new EditBox();

	box->SetName(elem->GetAttribute("NAME").c_str());
	if(elem->GetAttribute("ID", &tmpInt))			box->SetID(tmpInt);
	if(elem->GetAttribute("X", &tmpInt))			box->SetPositionX(tmpInt);
	if(elem->GetAttribute("Y", &tmpInt))			box->SetPositionY(tmpInt);
	if(elem->GetAttribute("WIDTH", &tmpInt))		box->SetSizeX(tmpInt);
	if(elem->GetAttribute("HEIGHT", &tmpInt))		box->SetSizeY(tmpInt);
	if(elem->GetAttribute("CHARWIDTH", &tmpInt))	box->SetCharWidth(tmpInt);
	if(elem->GetAttribute("CHARHEIGHT", &tmpInt))	box->SetCharHeight(tmpInt);
	if(elem->GetAttribute("NUMBER", &tmpInt))		box->SetNumber(tmpInt);
	if(elem->GetAttribute("LIMITTEXT", &tmpInt))	box->SetLimitText(tmpInt);
	if(elem->GetAttribute("PASSWORD", &tmpInt))		box->SetPassword(tmpInt);
	if(elem->GetAttribute("HIDECURSOR", &tmpInt))	box->SetHideCursor(tmpInt);
	if(elem->GetAttribute("TEXTALIGN", &tmpInt))	box->SetTextAlign(tmpInt);
	if(elem->GetAttribute("MULTILINE", &tmpInt))	box->SetMultiline(tmpInt);
	if(elem->GetAttribute("TEXTCOLOR", &tmpInt))	box->SetTextColour(tmpInt);
	if(elem->GetAttribute("FONT", &tmpInt))			box->SetFont(tmpInt);
	
	box->SetTextElement(gUiRender->CreateTextWithFont(box->Font()));

	return box;
}