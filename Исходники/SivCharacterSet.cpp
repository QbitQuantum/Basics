		std::u32string StringToUTF32(const StringView str)
		{
			if (str.empty())
			{
				return std::u32string();
			}

			const wchar* begin = &str[0];
			const wchar* end = begin + str.length();

			if (const auto length = detail::CountCodePoints(begin, end))
			{
				std::u32string result(length.value(), L'\0');

				while (begin != end)
				{
					const auto ch = *begin++;

					if (!IsUTF16Surrogate(ch))
					{
						result.push_back(ch);
					}
					else
					{
						result.push_back(SurrogateToUTF32(ch, *begin++));
					}
				}

				return result;
			}
			else
			{
				return std::u32string();
			}
		}