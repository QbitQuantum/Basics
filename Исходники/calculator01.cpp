double term(TokenStream& tokenStream)
{
    double result = primary(tokenStream);   // set result to value of primary
    Token token = tokenStream.getToken(); // get next token from tokenStream

    while (true)
    {
        if (token.kind == '*')
        {
            result *= primary(tokenStream);   // evaluate primary and multiply with result
            token = tokenStream.getToken(); // get next token from tokenStream
        }

        else if (token.kind == '/')
        {
            double divisor = primary(tokenStream);     // set divisor to value of primary
            if (divisor == 0) error("divide by zero"); // check for error
            result /= divisor;                           // divide result by divisor
            token = tokenStream.getToken();      // get next token from tokenStream
        }

        else if (token.kind == '%') // modulo will only work on ints for this implementation
        {
            int numer = result; // cast result to int
            int denom = primary(tokenStream); // cast denom to int
            if (denom == 0) error("%: divide by zero"); // error check
            result = numer % denom; // get result
            token = tokenStream.getToken();      // get next token from tokenStream
        }

        else
        {
            tokenStream.setToken(token);   // put token back into the Token stream
            return result;                 // return result
        }
    }
}