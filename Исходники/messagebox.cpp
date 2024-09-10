string MessageBox::getXml() {
/*
<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<MessageBox xmlns="http://www.garmin.com/xmlschemas/PluginAPI/v1" DefaultButtonValue="2">
  <Icon>Question</Icon>
  <Text>The file F:/Garmin/gpx/GC22K31.gpx already exists on your GPS Device. OK to overwrite the file?</Text>
  <Button Caption="OK" Value="1"/>
  <Button Caption="Cancel" Value="2"/>
</MessageBox>
*/

    TiXmlDocument doc;
    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "UTF-8", "no" );
    doc.LinkEndChild( decl );

	TiXmlElement * msgBox = new TiXmlElement( "MessageBox" );
    msgBox->SetAttribute("xmlns", "http://www.garmin.com/xmlschemas/PluginAPI/v1");
    msgBox->SetAttribute("DefaultButtonValue", this->defaultButton);
    doc.LinkEndChild( msgBox );

	TiXmlElement * icon = new TiXmlElement( "Icon" );
	if (this->type == Question) {
        icon->LinkEndChild(new TiXmlText("Question"));
	} else {
	    Log::err("MessageBox::getXml Message type not yet implemented!");
        icon->LinkEndChild(new TiXmlText("Unknown"));
	}
    msgBox->LinkEndChild( icon );

	TiXmlElement * textelem = new TiXmlElement( "Text" );
    textelem->LinkEndChild(new TiXmlText(this->text));
    msgBox->LinkEndChild( textelem );

    if ((this->buttons & BUTTON_OK) > 0) {
        TiXmlElement * btn = new TiXmlElement( "Button" );
        btn->SetAttribute("Caption", "OK");
        btn->SetAttribute("Value", BUTTON_OK);
        msgBox->LinkEndChild( btn );
    }

    if ((this->buttons & BUTTON_CANCEL) > 0) {
        TiXmlElement * btn = new TiXmlElement( "Button" );
        btn->SetAttribute("Caption", "Cancel");
        btn->SetAttribute("Value", BUTTON_CANCEL);
        msgBox->LinkEndChild( btn );
    }

    if ((this->buttons & BUTTON_YES) > 0) {
        TiXmlElement * btn = new TiXmlElement( "Button" );
        btn->SetAttribute("Caption", "Yes");
        btn->SetAttribute("Value", BUTTON_YES);
        msgBox->LinkEndChild( btn );
    }

    if ((this->buttons & BUTTON_NO) > 0) {
        TiXmlElement * btn = new TiXmlElement( "Button" );
        btn->SetAttribute("Caption", "No");
        btn->SetAttribute("Value", BUTTON_NO);
        msgBox->LinkEndChild( btn );
    }

    TiXmlPrinter printer;
	//printer.SetIndent( "\t" );
	doc.Accept( &printer );
    string str = printer.Str();

    return str;
}