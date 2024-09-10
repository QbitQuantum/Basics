void RTMPMP4Stream::onTextFrame(TextFrame &text)
{
	AMFObject *obj = new AMFObject();
	//Add text
	obj->AddProperty(L"text",text.GetWChar(),text.GetWLength());
	//Send packet
	SendCommand(L"onTextData",obj);
}