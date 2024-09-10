double RPNParser::evaluate(double x)
{
    size_t last_match_start = 0;
    size_t last_match_end = 0;
    while(last_match_end != std::string::npos)
    {
        last_match_end = m_expression.find(' ', last_match_start);
        std::string token = m_expression.substr(last_match_start, last_match_end - last_match_start);
        last_match_start = last_match_end + 1;
        // Evaluate it
        if( ! handle_token(token, x))
        {
            return nan("");
        }
    }
    return m_stack.top();
}