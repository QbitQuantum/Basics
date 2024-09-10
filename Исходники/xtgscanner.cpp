void XtgScanner::definePStyles()
{
	QString s1,s2,s3;
	enterState(stringMode);
	define = 2;
	if (token == "[S\"")
		s1 = getToken();
	else
	{
		while (lookAhead() != '\"')
			top++;					//skip the inch
		top++;
		s1 = getToken();			//will contain the string 1
	}
//	top = top + 2;				//we have to skip comma and next inch character
	while (lookAhead() != '\"')
		top++;
	top++;
	s2 = getToken();
	if (lookAhead() != ']' )
	{
		while (lookAhead() != '\"')
			top++;
		top++;
	//	top = top + 2;
		s3 = getToken();
	}
	top++; // to ensure that ] is avoided
	QString pStyle = CommonStrings::DefaultParagraphStyle;
	ParagraphStyle newStyle;
	if (s1 != "")
	{
		if (doc->paragraphStyles().contains(m_item->itemName() + "_" + s1))
			newStyle.setParent(m_item->itemName() + "_" + s1);
		else if  (doc->paragraphStyles().contains(s1))
			newStyle.setParent(s1);
		else
			newStyle.setParent(pStyle);
	}
	else
		newStyle.setParent(pStyle);
	if (m_prefixName)
		newStyle.setName(m_item->itemName() + "_" + sfcName);
	else
		newStyle.setName((sfcName));
	newStyle.setLineSpacingMode(ParagraphStyle::AutomaticLineSpacing);
	if (s3 != "")
	{
		if (doc->charStyles().contains(m_item->itemName() + "_" + s3))
			newStyle.charStyle().setParent(m_item->itemName() + "_" + s3);
		else if  (doc->charStyles().contains(s3))
			newStyle.charStyle().setParent(s3);
		else
			newStyle.charStyle().setParent(CommonStrings::DefaultCharacterStyle);
	}
	else
	{
		newStyle.charStyle().setParent(CommonStrings::DefaultCharacterStyle);
		newStyle.charStyle().setFontSize(120.0);
		styleEffects = ScStyle_None;
		newStyle.charStyle().setFeatures(styleEffects.featureList());
	}
	currentParagraphStyle = newStyle;
	currentCharStyle = newStyle.charStyle();
	enterState(textMode);
}