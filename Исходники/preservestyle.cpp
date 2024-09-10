static std::list<PreserveStyleToken> InternalPreserveStyleTokenize(const string& strStr, size_t From, size_t Length)
{
	FN_RETURN_TYPE(InternalPreserveStyleTokenize) Result;

	std::vector<bool> Seps(Length, false);
	for (size_t I = From+1; I+1 < From+Length; I++)
	{
		if (IsPreserveStyleTokenSeparator(strStr[I])
				&& !IsPreserveStyleTokenSeparator(strStr[I-1])
				&& !IsPreserveStyleTokenSeparator(strStr[I+1]))
		{
			Seps[I-From] = true;
		}
	}

	size_t L = From;
	for (size_t I = From+1; I < From+Length; I++)
	{
		if (Seps[I-From])
		{
			PreserveStyleToken T;
			T.Token = strStr.substr(L, I-L);
			T.PrependChar = 0;
			if (L >= From + 1 && Seps[L-1-From])
				T.PrependChar = strStr[L-1];
			Result.emplace_back(T);
			L = I+1;
			I++;
			continue;
		}

		if (!Seps[I-From-1] && IsLower(strStr[I-1]) && IsUpper(strStr[I]))
		{
			PreserveStyleToken T;
			T.Token = strStr.substr(L, I-L);
			T.PrependChar = 0;
			if (L >= From + 1 && Seps[L-1-From])
				T.PrependChar = strStr[L-1];
			Result.emplace_back(T);
			L = I;
		}
	}

	if (L < From+Length)
	{
		PreserveStyleToken T;
		T.Token = strStr.substr(L, From+Length-L);
		T.PrependChar = 0;
		if (L >= From + 1 && Seps[L-1-From])
			T.PrependChar = strStr[L-1];
		Result.emplace_back(T);
	}

	if (Result.size() > 1)
	{
		wchar_t PrependChar = std::next(Result.cbegin())->PrependChar;
		FOR (const auto& i, make_range(std::next(Result.cbegin(), 2), Result.cend()))
		{
			if (PrependChar != i.PrependChar)
			{
				Result.clear();
				PreserveStyleToken T;
				T.Token = strStr.substr(From, Length);
				T.PrependChar = 0;
				T.TypeMask = 1 << UNKNOWN;
				Result.emplace_back(T);
				return Result;
			}
		}
	}