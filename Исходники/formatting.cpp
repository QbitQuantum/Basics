    void BookTextParser::parseSubText(std::string text)
    {
        if (text[0] == '<')
        {
            const size_t tagStart = 1;
            const size_t tagEnd = text.find('>', tagStart);
            if (tagEnd == std::string::npos)
                throw std::runtime_error("BookTextParser Error: Tag is not terminated");
            const std::string tag = text.substr(tagStart, tagEnd - tagStart);

            if (boost::algorithm::starts_with(tag, "IMG"))
                parseImage(tag);
            if (boost::algorithm::starts_with(tag, "FONT"))
                parseFont(tag);
            if (boost::algorithm::starts_with(tag, "DIV"))
                parseDiv(tag);

            text.erase(0, tagEnd + 1);
        }

        size_t tagStart = std::string::npos;
        std::string realText; // real text, without tags
        for (size_t i = 0; i<text.size(); ++i)
        {
            char c = text[i];
            if (c == '<')
            {
                if ((i + 1 < text.size()) && text[i+1] == '/') // ignore closing tags
                {
                    while (c != '>')
                    {
                        if (i >= text.size())
                            throw std::runtime_error("BookTextParser Error: Tag is not terminated");
                        ++i;
                        c = text[i];
                    }
                    continue;
                }
                else
                {
                    tagStart = i;
                    break;
                }
            }
            else
                realText += c;
        }

        MyGUI::EditBox* box = mParent->createWidget<MyGUI::EditBox>("NormalText",
            MyGUI::IntCoord(0, mHeight, mWidth, 24), MyGUI::Align::Left | MyGUI::Align::Top,
            mParent->getName() + boost::lexical_cast<std::string>(mParent->getChildCount()));
        box->setProperty("Static", "true");
        box->setProperty("MultiLine", "true");
        box->setProperty("WordWrap", "true");
        box->setProperty("NeedMouse", "false");
        box->setMaxTextLength(realText.size());
        box->setTextAlign(mTextStyle.mTextAlign);
        box->setTextColour(mTextStyle.mColour);
        box->setFontName(mTextStyle.mFont);
        box->setCaption(realText);
        box->setSize(box->getSize().width, box->getTextSize().height);
        mHeight += box->getTextSize().height;

        if (tagStart != std::string::npos)
        {
            parseSubText(text.substr(tagStart, text.size()));
        }
    }