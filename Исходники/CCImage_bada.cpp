    bool drawText(const char * pszText, Dimension& dimensions, CCImage::ETextAlign alignment, const char * fontName = NULL, int fontSize = 0)
    {
        bool nRet = false;
        do
        {
            CC_BREAK_IF(pszText == NULL || strlen(pszText) <= 0);
            // text
            Osp::Base::String strText(pszText);
            // Set a font to the TextElement
            Font font;
            bool bUseDefaultFont = true;
            if (fontName != NULL && strlen(fontName) > 0)
            {
                String strFonName(fontName);
                if (strFonName.EndsWith(".ttf") || strFonName.EndsWith(".TTF"))
                {
                    bUseDefaultFont = false;
                    const char* pFullFontPath = CCFileUtils::fullPathFromRelativePath(fontName);
                    font.Construct(pFullFontPath, FONT_STYLE_PLAIN, fontSize);
                }
                else
                {
                    IList* pSystemFontList = Font::GetSystemFontListN();
                    if (pSystemFontList != NULL)
                    {
                        IEnumerator* pEnum = pSystemFontList->GetEnumeratorN();
                        Object* pObj = null;
                        while (pEnum->MoveNext() == E_SUCCESS)
                        {
                            pObj = pEnum->GetCurrent();
                            String* pStrName = static_cast<String*>(pObj);
                            if (pStrName->Equals(strFonName, false))
                            {
                                bUseDefaultFont = false;
                                font.Construct(*pStrName, FONT_STYLE_PLAIN, fontSize);
                                break;
                            }
                        }

                        delete pEnum;

                        pSystemFontList->RemoveAll(true);
                        delete pSystemFontList;
                    }
                }
            }

            if (bUseDefaultFont)
            {
                font.Construct(FONT_STYLE_PLAIN, fontSize);
            }

            // calculate text size
            if (dimensions.width <= 0)
            {
                Dimension dim;
                font.GetTextExtent(strText, strText.GetLength(), dim);
                dimensions.width = dim.width;
                dimensions.height = dim.height;
            }

            CC_BREAK_IF(dimensions.width <= 0);

            // Create an EnrichedText
            m_pEnrichedText = new EnrichedText();
            m_pEnrichedText->Construct(Dimension(dimensions.width, 10));

            switch (alignment)
            {
            case CCImage::kAlignCenter:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
                break;
            case CCImage::kAlignTop:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
                break;
            case CCImage::kAlignTopRight:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
                break;
            case CCImage::kAlignRight:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
                break;
            case CCImage::kAlignBottomRight:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_RIGHT);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
                break;
            case CCImage::kAlignBottom:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
                break;
            case CCImage::kAlignBottomLeft:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_BOTTOM);
                break;
            case CCImage::kAlignLeft:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
                break;
            case CCImage::kAlignTopLeft:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
                break;
            default:
                m_pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
                m_pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
                break;
            }
            // Set attributes of the EnrichedText
            m_pEnrichedText->SetTextWrapStyle(TEXT_WRAP_CHARACTER_WRAP);
            m_pEnrichedText->SetTextAbbreviationEnabled(true);

            // Create a TextElement
            TextElement* pTextElement = new TextElement();
            pTextElement->Construct(strText);
            // After Adding, set attributes of the TextElement
            pTextElement->SetTextColor(Color::COLOR_WHITE);
            pTextElement->SetFont(font);
            // Add the TextElement to the EnrichedText
            m_pEnrichedText->Add(*pTextElement);

            m_pEnrichedText->Refresh();
            dimensions.height = m_pEnrichedText->GetTotalLineHeight();
            m_pEnrichedText->SetSize(dimensions.width, dimensions.height);

            CC_SAFE_DELETE(m_pCanvas);
            m_pCanvas = new Canvas();
            m_pCanvas->Construct(Rectangle(0, 0, dimensions.width, dimensions.height));
            m_pCanvas->DrawText(Point(0, 0), *m_pEnrichedText);

            m_pEnrichedText->RemoveAllTextElements(true);
            CC_SAFE_DELETE(m_pEnrichedText);

            nRet = true;
        } while (0);
        return nRet;
    }