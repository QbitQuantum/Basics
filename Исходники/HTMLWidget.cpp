//*****************************************************************************
void CHTMLWidget::StartElement(
//Expat callback function: Process XML start tag, and attributes.
//
//Params:
	const XML_Char *name, const XML_Char **atts)
{
	//Get tag type (assume no special chars).
	const HTMLTagType eTagType = ParseTag(name);

	if (wstrBuffer.length()) Flush();

	++aeTagLevel[eTagType];

	//Get id/name attribute
	{
		static const WCHAR wszID[] = {We('i'),We('d'),We(0)};
		static const WCHAR wszNAME[] = {We('n'),We('a'),We('m'),We('e'),We(0)};
		WSTRING tmp = GetAttr(wszID, atts);
		if (tmp.empty())
			tmp = GetAttr(wszNAME, atts);
		if (!tmp.empty())
			mIdmap.insert(std::make_pair(tmp, this->wY));
	}

	switch (eTagType)
	{
		case BODY_Tag:
		{
			static const WCHAR wszBgcolor[] = {We('b'),We('g'),We('c'),We('o'),We('l'),We('o'),We('r'),We(0)};
			WSTRING bgcolor = GetAttr(wszBgcolor, atts);
			if (bgcolor.size())
				this->wstrBGColor = bgcolor;
			break;
		}
		case UL_Tag:
		case OL_Tag:
			this->swOLstack.push(this->wOLcounter);
			this->wOLcounter = (eTagType == OL_Tag ? 1 : 0);
			this->wMargin += LISTINDENT;
			NewLine(this->swOLstack.size() == 1);
			break;
		case H1_Tag:
		case H2_Tag:
		case H3_Tag:
			NewLine();
			break;
		case TITLE_Tag:
			wstrTitle = wszEmpty;
			break;
		case A_Tag:
			swstrLink.push(GetAttr(wszHREF, atts));
			break;
		case B_Tag:
			break;
		case HR_Tag:
		case BR_Tag:
			NewLine(true);
			break;
		case IMG_Tag:
		{
			static const WCHAR wszSrc[] = {We('s'),We('r'),We('c'),We(0)};
			WSTRING imageURL = this->wstrBasePath;
			imageURL += wszSlash;
			imageURL += GetAttr(wszSrc, atts);
			CImageWidget *pImage = new CImageWidget(0, this->wX + this->wMargin, this->wY, imageURL.c_str());
			ASSERT(pImage);
			AddWidget(pImage);
			this->wY += pImage->GetH();
			this->wX = 0;  //next thing goes on new line
			break;
		}
		case P_Tag:
			this->wY += static_cast<UINT>(g_pTheFM->GetFontLineHeight(FONTLIB::F_Text) * 2/3);
			break;
		case LI_Tag:
		{
			//Use image as bullet in stead ?
			static const WCHAR wszItem[] = {We('*'),We(' '),We(0)};
			NewLine();
			if (this->wOLcounter)
			{
				WCHAR wszBuf[33];
				wstrBuffer = (WSTRING)_itow(this->wOLcounter, wszBuf, 10)
					+ wszPeriod + wszSpace;
				++this->wOLcounter;
			}
			else wstrBuffer = wszItem;
			Flush(true);
			this->bSkipSpace = true;
			break;
		}
		case TABLE_Tag:
			NewLine();
			vwColumns.clear();
			//Fall through
		case TR_Tag:
			this->wCurrentColumn = 0;
			break;
		case TD_Tag:
		{
			if (this->wCurrentColumn >= vwColumns.size())
			{
				static const WCHAR wszWidth[] = {We('w'),We('i'),We('d'),We('t'),We('h'),We(0)};
				WSTRING wstrWidthAttr = GetAttr(wszWidth, atts);
				this->wTDWidth = wstrWidthAttr.length() > 0 ?
					_Wtoi(wstrWidthAttr.c_str()) : 0;
				vwColumns.push_back(this->wX += 32);
			}
			else
			{
				this->wX = vwColumns[this->wCurrentColumn];
				this->wTDWidth = 0;
			}
			++this->wCurrentColumn;
			this->bSkipSpace = true;
			break;
		}
		default:
			break;
	}
}