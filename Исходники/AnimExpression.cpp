AnimExpression::Token AnimExpression::consumeToken(const QString& str, QString::const_iterator& iter) const {
    if (!_tokenStack.empty()) {
        Token top = _tokenStack.top();
        _tokenStack.pop();
        return top;
    } else {
        while (iter != str.end()) {
            if (iter->isSpace()) {
                ++iter;
            } else if (iter->isLetter()) {
                return consumeIdentifier(str, iter);
            } else if (iter->isDigit()) {
                return consumeNumber(str, iter);
            } else {
                switch (iter->unicode()) {
                case '&': return consumeAnd(str, iter);
                case '|': return consumeOr(str, iter);
                case '>': return consumeGreaterThan(str, iter);
                case '<': return consumeLessThan(str, iter);
                case '(': ++iter; return Token(Token::LeftParen);
                case ')': ++iter; return Token(Token::RightParen);
                case '!': return consumeNot(str, iter);
                case '-': ++iter; return Token(Token::Minus);
                case '+': ++iter; return Token(Token::Plus);
                case '*': ++iter; return Token(Token::Multiply);
                case '/': ++iter; return Token(Token::Divide);
                case '%': ++iter; return Token(Token::Modulus);
                case ',': ++iter; return Token(Token::Comma);
                default:
                    qCCritical(animation) << "AnimExpression: unexpected char" << *iter << "at index " << (int)(iter - str.begin());
                    return Token(Token::Error);
                }
            }
        }
        return Token(Token::End);
    }
}