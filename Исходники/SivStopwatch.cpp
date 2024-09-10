	static String FormatStopwatch(int64 us, const String& format)
	{
		String result, keyPattern;

		if (us < 0)
		{
			result.push_back(U'-');

			us = -us;
		}

		bool inQuot = false;

		char32 previousChar = U'\0';

		for (size_t i = 0; i < format.length(); ++i)
		{
			const char32 ch = format[i];

			if (IsAlpha(ch))
			{
				if (inQuot)
				{
					result.push_back(ch);
				}
				else
				{
					if (keyPattern.isEmpty() || ch == previousChar)
					{
						keyPattern.push_back(ch);
					}
					else
					{
						result.append(GetFormattedElement(us, keyPattern));
						keyPattern.clear();
						keyPattern.push_back(ch);
					}
				}
			}
			else
			{
				if (!keyPattern.isEmpty())
				{
					result.append(GetFormattedElement(us, keyPattern));
					keyPattern.clear();
				}

				if (ch == U'\'')
				{
					if (format[i + 1] == U'\'')
					{
						result.push_back(U'\'');

						++i;

						continue;
					}

					inQuot = !inQuot;
				}
				else
				{
					result.push_back(ch);
				}
			}

			previousChar = ch;
		}

		if (!keyPattern.isEmpty())
		{
			result.append(GetFormattedElement(us, keyPattern));
		}

		return result;
	}