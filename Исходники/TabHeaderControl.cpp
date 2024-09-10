void TabHeaderControl::adjustLabels()
{
	for (pp_int32 i = 0; i < tabButtons.size(); i++)
	{
		PPButton* button = tabButtons.get(i);
		PPFont* font = button->getFont();	
		pp_int32 shrinkWidth = 	button->getSize().width - 4;
		if (shrinkWidth < 1)
			shrinkWidth = 1;

		PPString text = tabHeaders.get(i + startIndex)->text;
		if (text.charAt(text.length()-1) == '*')
		{
			text = font->shrinkString(text, shrinkWidth - font->getCharWidth(), PPFont::ShrinkTypeEnd);
			if (text.charAt(text.length()-1) != '*')
				text.append("*");
		}
		else
			text = font->shrinkString(text, shrinkWidth, PPFont::ShrinkTypeEnd);

		button->setText(text);
		if ((i + startIndex) & 1)
			button->setTextColor(GlobalColorConfig::getInstance()->getColor(GlobalColorConfig::ColorTextHighlited));
		else
			button->setTextColor(GlobalColorConfig::getInstance()->getColor(GlobalColorConfig::ColorForegroundText));
	}
}