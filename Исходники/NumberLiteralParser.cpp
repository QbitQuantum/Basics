	const Number FloatLiteralParser::Parse()
	{
		// Assert( NotAtEnd() && InClass(CharClass::NUMBER_HEAD) )

		char c = GetChar();

		NumberBuilder numberBuilder;

		if (c == '0')
		{
			Advance();
			if (AtEnd())
			{
				return Number::ZERO();
			}

			switch (GetChar())
			{
				case '.' : return ParseFractional(numberBuilder);
				case 'e' :
				case 'E' : return ParseExponent(numberBuilder);
				case 'b' : return config_.parse_binary ? ParseBinary() : Number::ZERO();
				case 'x' : return config_.parse_hexadecimal ? ParseHexadecimal() : Number::ZERO();
			}

			if (NotInClass(CharClass::DECIMAL))
			{
				return Number::ZERO();
			}

			if (config_.parse_octal)
			{
				return ParseOctal();
			}
		}
		else if (c == '-')
		{
			numberBuilder.SetNegative();
			Advance();
			if (AtEnd() || NotInClass(CharClass::DECIMAL))
			{
				ThrowError("Decimal digit expected");
			}
		}

		// Assert( NotAtEnd() && InClass(CharClass::DECIMAL) )
		do
		{
			numberBuilder.OnIntegerDigit(GetChar() - '0');

			Advance();
			if (AtEnd())
			{
				return numberBuilder.Release();
			}
		}
		while (InClass(CharClass::DECIMAL));

		if (GetChar() == '.')
		{
			return ParseFractional(numberBuilder);
		}
		else if (GetChar() == 'e' || GetChar() == 'E')
		{
			return ParseExponent(numberBuilder);
		}

		return numberBuilder.Release();
	}