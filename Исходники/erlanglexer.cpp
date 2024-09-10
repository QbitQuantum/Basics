int Lexer::nextTokenKind()
{
    int token = Parser::Token_INVALID;
    if (m_curpos >= m_contentSize) {
        m_tokenBegin = -1;
        m_tokenEnd = -1;
        createNewline(m_curpos);
        return 0;
    }
    QChar* it = m_content.data();
    it += m_curpos;
    m_tokenBegin = m_curpos;

    if (it->isSpace())
    {
        token = Parser::Token_WHITESPACE;
        while (m_curpos < m_contentSize && it->isSpace())
        {
            if (it->unicode() == '\n')
            {
                createNewline(m_curpos);
            }
            it++;
            m_curpos++;
        }
        m_curpos--;
    }
    else if (it->isDigit())
    {
	QRegExp regex("\\d+\\.\\d+|\\d+\\.\\d+|\\d+\\.\\d+e-?\\d+|\\d+\\.\\d+e-?\\d+|[\\dABCDEF]+#\\d{1,2}|\\d+");
	
	if ( regex.indexIn(m_content, m_curpos) != -1)
	{
	  kDebug() << "Matched: " << regex.cap();
	  
	  m_curpos += regex.matchedLength() - 1;
	  token = Parser::Token_INTEGER_LITERAL;
	}
    }
    else if (it->unicode() == '-')
    {
	  if ((it + 1)->unicode() == '>')
	  {
	      m_curpos++;
	      token = Parser::Token_LEADS_TO;
	  }
	  else  if ((it + 1)->unicode() == '-')
	  {
	      m_curpos++;
	      token = Parser::Token_LIST_DIFFERENCE;
	  }
	  else
	  {
	      token = Parser::Token_MINUS;
	  }
    }    
    else if (it->unicode() == '+')
    {
	if ((it + 1)->unicode() == '+')
        {
            m_curpos++;
            token = Parser::Token_LIST_ADDITION;
        }
        else
        {
            token = Parser::Token_PLUS;
        }
    }
    else if (it->unicode() == '$' && processCharLiteral(it + 1))
    {
        token = Parser::Token_CHAR_LITERAL;
    }
    else if (it->unicode() == '}')
    {
        token = Parser::Token_RBRACE;
        if (state() == Tuple)
        {
            popState();
        }
    }
    else if (it->unicode() == '_')
    {
        token = Parser::Token_UNDERLINE;
    }
    else if (it->unicode() == '{')
    {
        token = Parser::Token_LBRACE;
        pushState(Tuple);
    }
    else if (it->unicode() == ')')
    {
        token = Parser::Token_RPAREN;
    }
    else if (it->unicode() == '(')
    {
        token = Parser::Token_LPAREN;
    }
    else if (it->unicode() == ']')
    {
        token = Parser::Token_RBRACKET;
    }
    else if (it->unicode() == '[')
    {
        token = Parser::Token_LBRACKET;
    }
    else if (it->unicode() == ',')
    {
        token = Parser::Token_COMMA;
    }
    else if (it->unicode() == '#')
    {
        token = Parser::Token_POUND_SIGN;
    }
    else if (it->unicode() == '!')
    {
        token = Parser::Token_EXCLAMATION;
    }
    else if (it->unicode() == '<')
    {
        if ( (it + 1)->unicode() == '-')
        {
            m_curpos += 1;
            token = Parser::Token_LIST_COMPREHENSION_LEADS_TO;
        }
        else if ( (it + 1)->unicode() == '<' )
        {
            m_curpos += 1;
            token = Parser::Token_BINARY_OPEN;
        }
        else
        {
            token = Parser::Token_IS_SMALLER;
        }
    }
    else if (it->unicode() == '>')
    {
        if ((it + 1)->unicode() == '=')
        {
            m_curpos++;
            token = Parser::Token_IS_GREATER_OR_EQUAL;
        }
        else if ( (it + 1)->unicode() == '>' )
        {
            m_curpos += 1;
            token = Parser::Token_BINARY_CLOSE;
        }
        else
        {
            token = Parser::Token_IS_GREATER;
        }
    }
    else if (it->unicode() == '?')
    {
        token = Parser::Token_QUESTION;
    }
    else if (it->unicode() == '%')
    {
        token = Parser::Token_COMMENT;
        while (it->unicode() != '\n')
        {
            m_curpos++;
            it++;
        }
        createNewline(m_curpos);
    }
    else if (it->unicode() == '/')
    {
        if ((it + 1)->unicode() == '=')
        {
            token = Parser::Token_IS_NOT_EQUAL;
        }
        else
        {
            token = Parser::Token_FORWARD_SLASH;
        }
    }
    else if (it->unicode() == '*')
    {
        token = Parser::Token_MUL;
    }
    else if (it->unicode() == '|')
    {
        if ((it + 1)->unicode() == '|')
        {
            m_curpos++;
            token = Parser::Token_DOUBLE_PIPE;
        }
        else
        {
            token = Parser::Token_PIPE;
        }
    }
    else if (it->unicode() == ':')
    {
        if ( (it + 1)->unicode() == ':')
        {
            m_curpos += 1;
            token = Parser::Token_DOUBLE_COLON;
        }
        else
        {
            token = Parser::Token_COLON;
        }
    }
    else if (it->unicode() == '.')
    {
        token = Parser::Token_DOT;
    }
    else if (it->unicode() == ';')
    {
        token = Parser::Token_SEMICOLON;
    }
    else if (it->unicode() == '\'')
    {
        token = Parser::Token_ATOM_LITERAL;
        it++;
        m_curpos++;
        int startPos = m_curpos;
        while (m_curpos < m_contentSize
                && (it->unicode() != '\'')) {
            if (it->unicode() == '\n') createNewline(m_curpos);
            it++;
            m_curpos++;
        }
        // if the string is never terminated, make sure we don't overflow the boundaries
        if ( m_curpos == m_contentSize ) {
            --m_curpos;
        }
    }
    else if (it->unicode() == '"')
    {
        token = Parser::Token_STRING_LITERAL;
        it++;
        m_curpos++;
        while (m_curpos < m_contentSize
                && (it->unicode() != '\"')) {
            if (it->unicode() == '\n') createNewline(m_curpos);
            it++;
            m_curpos++;
        }
        // if the string is never terminated, make sure we don't overflow the boundaries
        if ( m_curpos == m_contentSize ) {
            --m_curpos;
        }
    }
    else if (it->unicode() == '=')
    {
        if ((it + 1)->unicode() == '=')
        {
            m_curpos++;
            token = Parser::Token_IS_EQUAL;
        }
        else if ((it + 1)->unicode() == '<') {
            m_curpos++;
            token = Parser::Token_IS_SMALLER_OR_EQUAL;
        }
        else if ((it + 1)->unicode() == ':' && (it + 2)->unicode() == '=')
        {
            m_curpos += 2;
            token = Parser::Token_EXACT_EQUATIONAL;
        }
        else if ((it + 1)->unicode() == '/' && (it + 2)->unicode() == '=')
        {
            m_curpos += 2;
            token = Parser::Token_EXACT_NOT_EQUATIONAL;
        }
        else
        {
            token = Parser::Token_ASSIGN;
        }
    }
    else if (it->isLetter() && it->isUpper())
    {
        QString name;
        while (m_curpos < m_contentSize && (isValidVariableIdentifier(it))) {
            name.append(*it);
            it++;
            m_curpos++;
        }
        m_curpos--;
        token = Parser::Token_VARIABLE;
    }
    else if (it->isLetter() && it->isLower())
    {
        QString name;
        while (m_curpos < m_contentSize && (isValidVariableIdentifier(it))) {
            name.append(*it);
            it++;
            m_curpos++;
        }

        m_curpos--;

        if (name == "after") {
            token = Parser::Token_AFTER;
        } else if (name == "begin") {
            token = Parser::Token_BEGIN;
        } else if (name == "case") {
            token = Parser::Token_CASE;
        } else if (name == "if") {
            token = Parser::Token_IF;
        } else if (name == "catch") {
            token = Parser::Token_CATCH;
        } else if (name == "cond") {
            token = Parser::Token_COND;
        } else if (name == "end") {
            token = Parser::Token_END;
        } else if (name == "fun") {
            token = Parser::Token_FUN;
        } else if (name == "let") {
            token = Parser::Token_LET;
        } else if (name == "of") {
            token = Parser::Token_OF;
        } else if (name == "catch") {
            token = Parser::Token_CATCH;
        } else if (name == "receive") {
            token = Parser::Token_RECEIVE;
        } else if (name == "when") {
            token = Parser::Token_WHEN;
        } else if (name == "div") {
            token = Parser::Token_INT_DIV;
        } else if (name == "rem") {
            token = Parser::Token_INT_REM;
        } else if (name == "or") {
            token = Parser::Token_OR;
        } else if (name == "xor") {
            token = Parser::Token_XOR;
        } else if (name == "bor") {
            token = Parser::Token_BIT_OR;
        } else if (name == "bxor") {
            token = Parser::Token_BIT_XOR;
        } else if (name == "query") {
            token = Parser::Token_QUERY;
        } else if (name == "bsl") {
            token = Parser::Token_SL;
        } else if (name == "bsr") {
            token = Parser::Token_SR;
        } else if (name == "and") {
            token = Parser::Token_AND;
        } else if (name == "band") {
            token = Parser::Token_BIT_AND;
        } else if (name == "not") {
            token = Parser::Token_NOT;
        } else if (name == "bnot") {
            token = Parser::Token_BIT_NOT;
        } else if (name == "orelse") {
            token = Parser::Token_ORELSE;
        } else if (name == "andalso") {
            token = Parser::Token_ANDALSO;
        } else if (name == "module") {
            token = Parser::Token_MODULE_DIRECTIVE;
        } else if (name == "include") {
            token = Parser::Token_INCLUDE_DIRECTIVE;
        } else if (name == "export") {
            token = Parser::Token_EXPORT_DIRECTIVE;
        } else if (name == "file") {
            token = Parser::Token_FILE_DIRECTIVE;
        } else if (name == "record") {
            token = Parser::Token_RECORD_DIRECTIVE;
        } else if (name == "include") {
            token = Parser::Token_INCLUDE_DIRECTIVE;
        } else if (name == "behaviour"){
	  token = Parser::Token_BEHAVIOUR_DIRECTIVE;
	} else if (name == "define"){
	  token = Parser::Token_DEFINE_DIRECTIVE;
	}	
        else
        {
            token = Parser::Token_ATOM_LITERAL;
        }
    }

    m_tokenEnd = m_curpos;
    m_curpos++;

    return token;
}