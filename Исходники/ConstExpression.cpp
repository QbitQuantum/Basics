int ConstExpression::expression_eval(quex::Token *tokenInput)
{
    m_InputToken = tokenInput;
    int t = Exp(0);
    Expect(TKN_TERMINATION);
    std::cout<<t<<std::endl;
    return EXIT_SUCCESS;
}