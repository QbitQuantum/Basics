void Phobos::Register::Table::ParseSpecialValue(const String_t &idName, Parser &parser)
{
	String_t type;

	ParserTokens_e token;
	if((token = parser.GetToken(&type)) != TOKEN_ID)
	{
		RaiseParseException(parser, TOKEN_ID, token, type, "Phobos::Register::Table::ParseSpecialValue");
	}

	if(type.compare("CharMatrix") == 0)
	{
		if((token = parser.GetToken(NULL)) != TOKEN_OPEN_PAREN)
		{
			RaiseParseException(parser, TOKEN_OPEN_PAREN, token, type, "Phobos::Register::Table::ParseSpecialValue");
		}

		String_t matrix;
		String_t row;

		UInt16_t numColumns = 0;
		UInt16_t numRows = 0;

		bool first = true;
		for(;;)
		{
			token = parser.GetToken(&row);
			if(token == TOKEN_CLOSE_PAREN)
			{
				if(first)
				{
					//do not allow empty matrix
					RaiseParseException(parser, "matrix data", "closing parenthesis", "Phobos::Register::Table::ParseSpecialValue");
				}
					
				this->SetCharMatrix(idName, matrix, numRows, numColumns);
				break;
			}
			else if(token == TOKEN_STRING)
			{
				if(first)
				{
					numColumns = row.length();

					if(numColumns == 0)
						PH_RAISE(PARSER_EXCEPTION, "Phobos::Register::Table::ParseSpecialValue", "Matrix cannot be empty");

					first = false;
				}
				else if(numColumns != row.length())
				{
					PH_RAISE(PARSER_EXCEPTION, "Phobos::Register::Table::ParseSpecialValue", "Matrix rows should always have the same length");
				}

				matrix.append(row);
				++numRows;
			}
			else
			{
				RaiseParseException(parser, TOKEN_STRING, token, row, "Phobos::Register::Table::ParseSpecialValue");
			}
		}
	}	
	else
	{
		RaiseParseException(parser, " valid especial type, ie CharMatrix", type.c_str(), "Phobos::Register::Table::ParseSpecialValue");
	}
}