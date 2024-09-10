void TextComponent::onTextChanged()
{
	calculateExtent();

	if(!mFont || mText.empty())
	{
		mTextCache.reset();
		return;
	}

	std::string text = mUppercase ? strToUpper(mText) : mText;

	std::shared_ptr<Font> f = mFont;
	const bool isMultiline = (mSize.y() == 0 || mSize.y() > f->getHeight()*1.2f);

	bool addAbbrev = false;
	if(!isMultiline)
	{
		size_t newline = text.find('\n');
		text = text.substr(0, newline); // single line of text - stop at the first newline since it'll mess everything up
		addAbbrev = newline != std::string::npos;
	}

	Eigen::Vector2f size = f->sizeText(text);
	if(!isMultiline && mSize.x() && text.size() && (size.x() > mSize.x() || addAbbrev))
	{
		// abbreviate text
		const std::string abbrev = "...";
		Eigen::Vector2f abbrevSize = f->sizeText(abbrev);

		while(text.size() && size.x() + abbrevSize.x() > mSize.x())
		{
			size_t newSize = Font::getPrevCursor(text, text.size());
			text.erase(newSize, text.size() - newSize);
			size = f->sizeText(text);
		}

		text.append(abbrev);

		mTextCache = std::shared_ptr<TextCache>(f->buildTextCache(text, Eigen::Vector2f(0, 0), (mColor >> 8 << 8) | mOpacity, mSize.x(), mAlignment, mLineSpacing));
	}else{