void AP_UnixDialog_FormatTOC::setDetailsLevel(UT_sint32 iLevel)
{
	AP_Dialog_FormatTOC::setDetailsLevel(iLevel);
	UT_UTF8String sVal;

	sVal = getTOCPropVal("toc-label-after",getDetailsLevel());
	GtkWidget * pW = _getWidget("edTextAfter");
	gtk_entry_set_text(GTK_ENTRY(pW),sVal.utf8_str());

	sVal = getTOCPropVal("toc-label-before",getDetailsLevel());
	pW = _getWidget("edTextBefore");
	gtk_entry_set_text(GTK_ENTRY(pW),sVal.utf8_str());

	sVal = getTOCPropVal("toc-label-start",getDetailsLevel());
	pW = _getWidget("wStartEntry");
	gtk_entry_set_text(GTK_ENTRY(pW),sVal.utf8_str());


	sVal = getTOCPropVal("toc-indent",getDetailsLevel());
	pW = _getWidget("wIndentEntry");
	gtk_entry_set_text(GTK_ENTRY(pW),sVal.utf8_str());
	

	sVal = getTOCPropVal("toc-label-inherits",getDetailsLevel());
	pW = _getWidget("cbInherit");
	if(g_ascii_strcasecmp(sVal.utf8_str(),"1") == 0)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pW),TRUE);
	}
	else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pW),FALSE);
	}


	FV_View * pView = static_cast<FV_View *>(getActiveFrame()->getCurrentView());
	sVal = getTOCPropVal("toc-label-type",getDetailsLevel());
	pW = _getWidget("wLabelChoose"); 
	GtkComboBox *combo = GTK_COMBO_BOX(pW);
	UT_sint32 iHist = static_cast<UT_sint32>(pView->getLayout()->FootnoteTypeFromString(sVal.utf8_str()));
	gtk_combo_box_set_active(combo,iHist);

	sVal = getTOCPropVal("toc-page-type",getDetailsLevel());
	pW = _getWidget("wPageNumberingChoose"); 
	combo = GTK_COMBO_BOX(pW);
	iHist = static_cast<UT_sint32>(pView->getLayout()->FootnoteTypeFromString(sVal.utf8_str()));
	gtk_combo_box_set_active(combo,iHist);

	sVal = getTOCPropVal("toc-tab-leader",getDetailsLevel());
	pW = _getWidget("wTabLeaderChoose");
	combo = GTK_COMBO_BOX(pW);
	if(g_ascii_strcasecmp(sVal.utf8_str(),"none") == 0)
	{
		iHist = 0;
	}
	else if(g_ascii_strcasecmp(sVal.utf8_str(),"dot") == 0)
	{
		iHist = 1;
	}
	else if(g_ascii_strcasecmp(sVal.utf8_str(),"hyphen") == 0)
	{
		iHist = 2;
	}
	else if(g_ascii_strcasecmp(sVal.utf8_str(),"underline") == 0)
	{
		iHist = 3;
	}
	else
	{
		iHist = 1;
	}
	gtk_combo_box_set_active(combo,iHist);
}