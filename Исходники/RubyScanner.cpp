/**
  reads identifier and classifies it
  */
Token Scanner::readIdentifier()
{
    QChar ch = m_src.peek();
    while (ch.isLetterOrNumber() || ch == '_' || ch == '?' || ch == '!') {
        m_src.move();
        ch = m_src.peek();
    }
    QStringRef value = m_src.value();

    Token::Kind kind = Token::Identifier;
    if (m_src.peek() == ':' && m_src.peek(1) != ':') {
        m_src.move();
        kind = Token::SymbolHashKey;
    } else if (value.at(0) == '@') {
        kind = Token::ClassField;
    } else if (value.length() > 1 && value.at(0) == ':') {
        kind = Token::Symbol;
    } else if (value.at(0) == '$') {
        kind = Token::Global;
    } else if (value.at(0).isUpper()) {
        kind = Token::Constant;
        if (m_hasContextRecognition && m_contextPattern.match(m_tokenSequence).hasMatch()) {
            m_context << value.toString();
            m_contextDepths << m_indentDepth;
        }
    // TODO: Use gperf for this keywords hash
    } else if (value == "end") {
        kind = Token::KeywordEnd;
        m_indentDepth--;
        if (!m_contextDepths.empty() && m_indentDepth < m_contextDepths.last()) {
            m_context.pop_back();
            m_contextDepths.pop_back();
        }
    } else if (value == "self") {
        kind = Token::KeywordSelf;
    } else if (value == "def") {
        kind = Token::KeywordDef;
        m_indentDepth++;
    } else if (value == "module") {
        kind = Token::KeywordModule;
        m_indentDepth++;
    } else if (value == "class") {
        kind = Token::KeywordClass;
        m_indentDepth++;
    } else if (value == "if" || value == "unless") {
        kind = Token::KeywordFlowControl;
        if (m_controlFlowShouldIncIndentPattern.match(m_tokenSequence).hasMatch())
            m_indentDepth++;
    } else if (value == "while" || value == "until") {
        kind = Token::KeywordLoop;
        m_indentDepth++;
    } else if (value == "do" || value == "begin" || value == "case") {
        kind = Token::KeywordBlockStarter;
        m_indentDepth++;
    } else if (value == "else"
               || value == "elsif"
               || value == "ensure"
               || value == "rescue") {
        kind = Token::KeywordElseElsIfRescueEnsure;
    } else if (value == "protected" || value == "private" || value == "public") {
        kind = Token::KeywordVisibility;
    } else if (std::find(&RUBY_KEYWORDS[0], &RUBY_KEYWORDS[N_KEYWORDS], value.toUtf8()) != &RUBY_KEYWORDS[N_KEYWORDS]) {
        kind = Token::Keyword;
    } else if (m_methodPattern.match(m_tokenSequence).hasMatch()) {
        QChar ch = m_src.peek();
        while (!ch.isNull() && !ch.isSpace() && ch != '(' &&  ch != '#') {
            m_src.move();
            ch = m_src.peek();
        }
        kind = Token::Method;
    } else if (m_parameterPattern.match(m_tokenSequence).hasMatch()) {
        kind = Token::Parameter;
    }

    return Token(kind, m_src.anchor(), m_src.length());
}