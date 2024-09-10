static TToken getToken()
{
	oSrcString = sSrcString;
	int ch = getNextChar();
	bool verbStr=false;

	switch (ch)
	{
		case EOFCH:
		case 0:    currTok = tEnd;    break;
		case L',': currTok = tComma;  break;
		case L'+': currTok = tPlus;   break;
		case L'-': currTok = tMinus;  break;
		case L'*': currTok = tMul;    break;
		case L'/': currTok = tDiv;    break;
		case L'(': currTok = tLp;     break;
		case L')': currTok = tRp;     break;
		case L'^':

			if ((ch = getChar()) == L'^')
				currTok = tBoolXor;
			else
			{
				putBack(ch);
				currTok = tBitXor;
			}

			break;
		case L'~':

			if ((ch = getChar()) != L' ')
			{
				putBack(ch);
				currTok = tBitNot;
				break;
			}

			putBack(ch);   //????
			currTok = tEnd;
			break;
		case L'|':

			if ((ch = getChar()) == L'|')
				currTok = tBoolOr;
			else
			{
				putBack(ch);
				currTok = tBitOr;
			}

			break;
		case L'&':

			if ((ch = getChar()) == L'&')
				currTok = tBoolAnd;
			else
			{
				putBack(ch);
				currTok = tBitAnd;
			}

			break;
		case L'=':

			if ((ch = getChar()) == L'=')
				currTok = tEq;
			else
			{
				putBack(ch);
				currTok = tLet;
			}

			break;
		case L'>':

			switch ((ch = getChar()))
			{
				case L'=': currTok = tGe;     break;
				case L'>': currTok = tBitShr; break;
				default:
					putBack(ch);
					currTok = tGt;
					break;
			}

			break;
		case L'<':

			switch (ch = getChar())
			{
				case L'=': currTok = tLe;     break;
				case L'<': currTok = tBitShl; break;
				default:
					putBack(ch);
					currTok = tLt;
					break;
			}

			break;
		case L'!':

			if ((ch = getChar()) != L'=')
			{
				putBack(ch);
				currTok = tNot;
				break;
			}
			else
				currTok = tNe;

			break;

		case L'@':

			ch = getChar();
			if (ch != L'"')
			{
				putBack(ch);
				break;
			}
			verbStr=true;

    	case L'\"':
		{
			TToken __currTok = tNo;
			currVar = L"";

			while (((ch = getChar()) != EOFCH))
			{
				if (ch == L'\"')
				{
					if (verbStr)
					{
						ch = getChar();
						if (ch != L'\"')
						{
							putBack(ch);
							break;
						}
					}
					else
						break;
				}

				if (ch == L'\\' && !verbStr)
				{
					switch (ch = getChar())
					{
						case L'a' : ch = L'\a'; break;
						case L'b' : ch = L'\b'; break;
						case L'f' : ch = L'\f'; break;
						case L'n' : ch = L'\n'; break;
						case L'r' : ch = L'\r'; break;
						case L't' : ch = L'\t'; break;
						case L'v' : ch = L'\v'; break;
						case L'\'': ch = L'\''; break;
						case L'\"': ch = L'\"'; break;
						case L'\\': ch = L'\\'; break;
						case L'0': case L'1': case L'2': case L'3': case L'4': case L'5': case L'6': case L'7': // octal: \d \dd \ddd
						{
							BYTE n = ch - L'0';

							if ((unsigned int)(ch = getChar()) >= L'0' && (unsigned int)ch < L'8')
							{
								n = 8 * n + ch - L'0';

								if ((unsigned int)(ch = getChar()) >= L'0' && (unsigned int)ch < L'8')
									n = 8 * n + ch - L'0';
								else
									putBack(ch);
							}
							else
								putBack(ch);

							ch = n;
							break;
						}
						case L'x':
						{
							if (iswxdigit(ch = getChar()))
							{
								wchar_t value=hex2ch(ch);

								for (int ii=0; ii<3; ii++)
								{
									if (iswxdigit(ch = getChar()))
									{
										value=(value<<4)|hex2ch(ch);
									}
									else
									{
										putBack(ch);
										break;
									}
								}

								ch = value;
							}
							else
							{
								keyMacroParseError(err_Bad_Hex_Control_Char,--sSrcString,pSrcString);
								__currTok = tEnd;
							}

							break;
						}
						default:
						{
							keyMacroParseError(err_Bad_Control_Char,--sSrcString,pSrcString);
							__currTok = tEnd;
							break;
						}
					}
				}

				if (__currTok != tNo)
					break;

				currVar.AppendStr((wchar_t)ch);
			}

			if (__currTok == tNo)
				currTok = tStr;
			else
				currTok = __currTok;

			break;
		}
		case L'.':
		{
			ch = getChar();

			if (iswdigit(ch))
			{
				putBack(ch);
				ch=L'.';
			}
			else
			{
				currTok = tEnd; //???
				break;
			}
		}
		case L'0': case L'1': case L'2': case L'3': case L'4':
		case L'5': case L'6': case L'7': case L'8': case L'9':
		{
			static wchar_t buffer[256];
			wchar_t *ptrbuffer=buffer;
			bool isNum   = false;
			bool isHex   = false;
			bool isE     = false;
			bool isPoint = false;
			int ch2;

			for (;;)
			{
				*ptrbuffer++=(wchar_t)ch;

				switch (ch)
				{
					case L'x':
					case L'X':

						if (ptrbuffer == buffer + 2)
						{
							ch = getChar();

							if (iswxdigit(ch))
							{
								isHex=true;
								putBack(ch);
							}
							else
							{
								putBack(ch);
								isNum=true;
								break;
							}
						}

						break;
					case L'.':

						if (isPoint || isE)
						{
							isNum=true;
							break;
						}

						isPoint=true;
						break;
					case L'e':
					case L'E':

						if (isHex)
							break;

						if (isE)
						{
							isNum=true;
							break;
						}

						isE=true;
						ch2 = getChar();

						if (ch2 == L'-' || ch2 == L'+')
						{
							int ch3=getChar();

							if (iswdigit(ch3))
							{
								*ptrbuffer++=(wchar_t)ch2;
								*ptrbuffer++=(wchar_t)ch3;
							}
							else
							{
								putBack(ch3);  // !iswdigit
								putBack(ch2);  // -+
								putBack(ch);   // eE
							}
						}
						else if (!iswdigit(ch2))
						{
							putBack(ch2); // !iswdigit
							putBack(ch);  // eE
						}
						else
							putBack(ch);

						break;
					case L'a': case L'A':
					case L'b': case L'B':
					case L'c': case L'C':
					case L'd': case L'D':
					case L'f': case L'F':

						if (!isHex)
						{
							isNum=true;
							break;
						}

					case L'0': case L'1': case L'2': case L'3': case L'4':
					case L'5': case L'6': case L'7': case L'8': case L'9':
						//isNum=true;
						break;
					default:
						isNum=true;
						break;
				}

				if (isNum)
					break;

				ch = getChar();
			}

			if (ch != EOFCH)
				putBack(ch);

			*ptrbuffer++=(wchar_t)0;
			bool CheckIntNumber=true;

			if (buffer[0])
			{
				if (!(buffer[1] == L'x' || buffer[1] == L'X'))
				{
					for (ptrbuffer=buffer; *ptrbuffer ; ptrbuffer++)
					{
						if (*ptrbuffer == L'e' || *ptrbuffer == L'E' || *ptrbuffer == L'.')
						{
							CheckIntNumber=false;
							break;
						}
						else if (!iswdigit(*ptrbuffer))
							break;
					}
				}
			}
			else
				CheckIntNumber=false;

			if (CheckIntNumber)
			{
				currVar = _wcstoi64(buffer,&ptrbuffer,0);
				currTok = tInt;
			}
			else
			{
				currVar = wcstod(buffer,&ptrbuffer);
				currTok = tFloat;
			}

			break;
		}
		case L'%':
			ch = getChar();

			if ((IsAlphaNum(ch) || ch == L'_') || (ch == L'%'  && (IsAlphaNum(*sSrcString) || *sSrcString == L'_')))
			{
				getVarName(ch);
				putBack(ch);
				currTok = tVar;
			}
			else
				keyMacroParseError(err_Var_Expected,L""); // BUG nameString

			break;
		default:
		{
			if (IsAlpha(ch))   // || ch == L'_' ????
			{
				TToken __currTok = tNo;
				getFarName(ch);

				if (ch == L' ')
				{
					while (ch == L' ')
						ch = getNextChar();
				}

				if (ch == L'(')   //!!!! а пробелы пропустить? ДА!
					__currTok = tFunc;
				else
				{
					putBack(ch);

					for (int i = 0 ; i < MKeywordsSize ; i++)
						if (!StrCmpI(nameString, MKeywords[i].Name))
						{
							FARVar = MKeywords[i].Value;
							__currTok = tFARVar;
							break;
						}

					if (__currTok == tNo)
					{
						if (IsProcessFunc || currTok == tFunc || currTok == tLt) // TODO: уточнить
						{
							if (KeyNameMacroToKey(nameString) == -1 && KeyNameToKey(nameString) == -1 && checkMacroConst(nameString))
								__currTok = tConst;
							else
							{
								DWORD k=KeyNameToKey(nameString);

								if (k != (DWORD)-1)
								{
									currVar = (__int64)k;
									__currTok = tInt; //??
								}
								else
								{
									keyMacroParseError(err_Var_Expected,oSrcString,pSrcString,nameString);
								}
							}
						}
						else
						{
							if (KeyNameMacroToKey(nameString) == -1)
							{
								if (KeyNameToKey(nameString) == -1)
								{
									if (checkMacroConst(nameString))
										__currTok = tConst;
									else
										keyMacroParseError(err_Unrecognized_keyword,nameString);
								}
								else
								{
									currVar = (__int64)KeyNameToKey(nameString);
									__currTok = tInt; //??
								}
							}
						}
					}
				}

				if (__currTok != tNo)
					currTok=__currTok;
			}
			else
				currTok = tEnd;

			break;
		}
	}

	return currTok;
}