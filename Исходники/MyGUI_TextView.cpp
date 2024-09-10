	void TextView::update(const UString& _text, IFont* _font, int _height, Align _align, VertexColourType _format, int _maxheight)
	{
		mFontHeight = _height;

		// массив дл¤ быстрой конвертации цветов
		static const char convert_colour[64] =
		{
			0,  1,  2,  3,  4,  5,  6, 7, 8, 9, 0, 0, 0, 0, 0, 0,
			0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};

		mViewSize.clear();

		RollBackPoint roll_back;
		IntSize result;
		int width = 0;
		size_t count = 0;
		mLength = 0;
		mLineInfo.clear();
		LineInfo line_info;
		int font_height = _font->getDefaultHeight();

		UString::const_iterator end = _text.end();
		UString::const_iterator index = _text.begin();

		/*if (index == end)
			return;*/

		result.height += _height;

		for (; index != end; ++index)
		{
			Char character = *index;

			// нова¤ строка
			if (character == FontCodeType::CR
				|| character == FontCodeType::NEL
				|| character == FontCodeType::LF)
			{
				if (character == FontCodeType::CR)
				{
					UString::const_iterator peeki = index;
					++peeki;
					if ((peeki != end) && (*peeki == FontCodeType::LF))
						index = peeki; // skip both as one newline
				}

				line_info.width = width;
				line_info.count = count;
				mLength += line_info.count + 1;

				result.height += _height;
				if (result.width < width)
					result.width = width;
				width = 0;
				count = 0;

				mLineInfo.push_back(line_info);
				line_info.clear();

				// отмен¤ем откат
				roll_back.clear();

				continue;
			}
			// тег
			else if (character == L'#')
			{
				// берем следующий символ
				++ index;
				if (index == end)
				{
					--index;    // это защита
					continue;
				}

				character = *index;
				// если два подр¤д, то рисуем один шарп, если нет то мен¤ем цвет
				if (character != L'#')
				{
					// парсим первый символ
					uint32 colour = convert_colour[(character-48) & 0x3F];

					// и еще п¤ть символов после шарпа
					for (char i = 0; i < 5; i++)
					{
						++ index;
						if (index == end)
						{
							--index;    // это защита
							continue;
						}
						colour <<= 4;
						colour += convert_colour[ ((*index) - 48) & 0x3F ];
					}

					// если нужно, то мен¤ем красный и синий компоненты
					texture_utility::convertColour(colour, _format);

					line_info.simbols.push_back( CharInfo(colour) );

					continue;
				}
			}

			GlyphInfo* info = _font->getGlyphInfo(character);
			if (FontCodeType::Space == character)
			{
				roll_back.set(line_info.simbols.size(), index, count, width);
			}
			else if (FontCodeType::Tab == character)
			{
				roll_back.set(line_info.simbols.size(), index, count, width);
			}

			int char_width = info->width;
			if (font_height != _height)
			{
				char_width = char_width * _height / font_height;
				if (!char_width) char_width = 1;
			}

			// перенос слов
			if (_maxheight != -1
				&& (width + char_width) > _maxheight
				&& !roll_back.empty())
			{
				// откатываем до последнего пробела
				width = roll_back.getLenght();
				count = roll_back.getCount();
				index = roll_back.getTextIter();
				line_info.simbols.erase(line_info.simbols.begin() + roll_back.getPosition(), line_info.simbols.end());

				// запоминаем место отката, как полную строку
				line_info.width = width;
				line_info.count = count;
				mLength += line_info.count + 1;

				result.height += _height;
				if (result.width < width)
					result.width = width;
				width = 0;
				count = 0;

				mLineInfo.push_back(line_info);
				line_info.clear();

				// отмен¤ем откат
				roll_back.clear();

				continue;
			}

			line_info.simbols.push_back(CharInfo(info->uvRect, char_width));
			width += char_width;
			count ++;
		}

		line_info.width = width;
		line_info.count = count;
		mLength += line_info.count;

		mLineInfo.push_back(line_info);

		if (result.width < width)
			result.width = width;

		// теперь выравниванием строки
		for (VectorLineInfo::iterator line = mLineInfo.begin(); line != mLineInfo.end(); ++line)
		{
			if (_align.isRight())
				line->offset = result.width - line->width;
			else if (_align.isHCenter())
				line->offset = (result.width - line->width) / 2;
		}

		mViewSize = result;
	}