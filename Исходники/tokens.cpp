TokenNumber::TokenNumber(const std::string &number)
 : Token(TokenType::NUMBER_LITERAL)
{
	value = atoll(number.c_str());
}