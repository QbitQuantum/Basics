	vlVoid GetNextToken() {
		CToken *Token;

		Token = this->ByteTokenizer->Next();

		// Consume all whitespace.
		while (Token->GetToken() == TOKEN_WHITESPACE) {
			Token = this->ByteTokenizer->Next();
		}

		vlUInt uiIndex = 0;
		vlChar cBuffer[4096];

		switch (Token->GetToken()) {
				// Comment (these are removed for the parser).
			case TOKEN_FORWARD_SLASH :
				Token = this->ByteTokenizer->Next();
				
				if (Token->GetToken() != TOKEN_FORWARD_SLASH) {
					throw "expected comment string";
				}
				do {
					Token = this->ByteTokenizer->Next("\n");
				} while (Token->GetToken() == TOKEN_CHAR);
				
				if (Token->GetToken() == TOKEN_EOF) {
					this->NextToken = new CToken(TOKEN_EOF);
				} else {
					this->NextToken = new CToken(TOKEN_NEWLINE);
				}
				break;
				// Quoted string.
			case TOKEN_QUOTE:
				while (true) {
					Token = this->ByteTokenizer->Next("\"");
					
					if (Token->GetToken() != TOKEN_CHAR) {
						break;
					}
					if (Token->GetChar() == '\r' || Token->GetChar() == '\n') {
						throw "newline in string";
					}
					cBuffer[uiIndex++] = Token->GetChar();
				}
				cBuffer[uiIndex++] = '\0';
				
				if (Token->GetToken() != TOKEN_SPECIAL) {
					throw "expected closing quote";
				} else {
					this->NextToken = new CToken(cBuffer, vlTrue);
				}
				break;
				// Unquoted string.
			case TOKEN_CHAR:
				cBuffer[uiIndex++] = Token->GetChar();
				
				while (this->ByteTokenizer->Peek()->GetToken() == TOKEN_CHAR) {
					Token = this->ByteTokenizer->Next();
					
					cBuffer[uiIndex++] = Token->GetChar();
				}
				cBuffer[uiIndex++] = '\0';
				
				assert(uiIndex <= 4096);
				
				this->NextToken = new CToken(cBuffer, vlFalse);
				break;
				// Let these byte tokens "pass through".
			case TOKEN_EOF:
			case TOKEN_NEWLINE:
			case TOKEN_OPEN_BRACE:
			case TOKEN_CLOSE_BRACE:
				this->NextToken = new CToken(*Token);
				break;
				// The parser doesn't care about anything else.
			default:
				throw "unexpected token";
				break;
		}
	}