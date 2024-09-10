void gtAction::write(const QString& text, gtStyle *style)
{
	if (isFirstWrite)
	{
		if (!doAppend)
		{
			if (it->nextInChain() != 0)
			{
				PageItem *nextItem = it->nextInChain();
				while (nextItem != 0)
				{
					nextItem->itemText.clear();
					nextItem = nextItem->nextInChain();
				}
			}
			it->itemText.clear();
		}
	}
	int paragraphStyle = -1;
	if (style->target() == "paragraph")
	{
		gtParagraphStyle* pstyle = dynamic_cast<gtParagraphStyle*>(style);
		assert(pstyle != NULL);
		paragraphStyle = applyParagraphStyle(pstyle);
		if (isFirstWrite)
			inPara = true;
	}
	else if (style->target() == "frame")
	{
		gtFrameStyle* fstyle = dynamic_cast<gtFrameStyle*>(style);
		assert(fstyle != NULL);
		applyFrameStyle(fstyle);
	}

	if ((inPara) && (!lastCharWasLineChange) && (text.left(1) != "\n") && (lastParagraphStyle != -1))
		paragraphStyle = lastParagraphStyle;

	if (paragraphStyle == -1)
		paragraphStyle = 0; //::findParagraphStyle(textFrame->doc(), textFrame->doc()->currentStyle);

	const ParagraphStyle& paraStyle = textFrame->doc()->paragraphStyles()[paragraphStyle];

	gtFont* font = style->getFont();
	QString fontName = validateFont(font).scName();
	CharStyle lastStyle, newStyle;
	int lastStyleStart = 0;
	
	if ((inPara) && (!overridePStyleFont))
	{
		if (paraStyle.charStyle().font().isNone())
		{
			gtFont font2(*font);
			font2.setName(paraStyle.charStyle().font().scName());
			QString fontName2 = validateFont(&font2).scName();
			newStyle.setFont((*textFrame->doc()->AllFonts)[fontName2]);
		}
	}
	else
	{
		setCharStyleAttributes(font, newStyle);
	}
	/*newStyle.eraseCharStyle(paraStyle.charStyle());*/

	lastStyle = newStyle;
	lastStyleStart = it->itemText.length();

	QChar ch0(0), ch5(5), ch10(10), ch13(13);
	for (int a = 0; a < text.length(); ++a)
	{
		if ((text.at(a) == ch0) || (text.at(a) == ch13))
			continue;
		QChar ch = text.at(a);
		if ((ch == ch10) || (ch == ch5))
			ch = ch13;
		else if (ch.unicode() == 0x2028)
			ch = SpecialChars::LINEBREAK;
		else if (ch.unicode() == 0x2029)
			ch = SpecialChars::PARSEP;
		
		int pos = it->itemText.length();
		it->itemText.insertChars(pos, QString(ch));
		if (ch == SpecialChars::PARSEP) 
		{
			if (paraStyle.hasName())
			{
				ParagraphStyle pstyle;
				pstyle.setParent(paraStyle.name());
				it->itemText.applyStyle(pos, pstyle);
			}
			else
				it->itemText.applyStyle(pos, paraStyle);
		}
	}
	it->itemText.applyCharStyle(lastStyleStart, it->itemText.length()-lastStyleStart, lastStyle);
	if (paraStyle.hasName())
	{
		ParagraphStyle pStyle;
		pStyle.setParent(paraStyle.name());
		it->itemText.applyStyle(qMax(0,it->itemText.length()-1), pStyle);
	}
	else
		it->itemText.applyStyle(qMax(0,it->itemText.length()-1), paraStyle);
	
	lastCharWasLineChange = text.right(1) == "\n";
	inPara = style->target() == "paragraph";
	lastParagraphStyle = paragraphStyle;
	if (isFirstWrite)
		isFirstWrite = false;
}