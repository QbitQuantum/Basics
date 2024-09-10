/**
 * Get next token in the current string expr.
 * Uses the ExpParser data expr, e, token, t, token_type and err
 */
void ExpParser::getToken()
{
    token_type = NOTHING;
    char* t;           // points to a character in token
    t = token;         // let t point to the first character in token
    *t = '\0';         // set token empty

    //printf("\tgetToken e:{%c}, ascii=%i, col=%i\n", *e, *e, e-expr);

    // skip over whitespaces
    while (*e == ' ' || *e == '\t')     // space or tab
    {
        e++;
    }

    // check for end of expression
    if (*e == '\0')
    {
        // token is still empty
        token_type = DELIMETER;
        return;
    }

    // check for minus
    if (*e == '-')
    {
        token_type = DELIMETER;
        *t = *e;
        e++;
        t++;
        *t = '\0';  // add a null character at the end of token
        return;
    }

    // check for parentheses
    if (*e == '(' || *e == ')')
    {
        token_type = DELIMETER;
        *t = *e;
        e++;
        t++;
        *t = '\0';
        return;
    }

    // check for operators (delimeters)
    if (isDelimeter(*e))
    {
        token_type = DELIMETER;
        while (isDelimeter(*e))
        {
            *t = *e;
            e++;
            t++;
        }
        *t = '\0';  // add a null character at the end of token
        return;
    }

    // check for a value
    if (isDigitDot(*e))
    {
        token_type = NUMBER;
        while (isDigitDot(*e))
        {
            *t = *e;
            e++;
            t++;
        }

        // check for scientific notation like "2.3e-4" or "1.23e50"
        if (toupper(*e) == 'E')
        {
            *t = *e;
            e++;
            t++;

            if (*e == '+' || *e == '-')
            {
                *t = *e;
                e++;
                t++;
            }

            while (isDigit(*e))
            {
                *t = *e;
                e++;
                t++;
            }
        }

        *t = '\0';
        return;
    }

    // check for variables or functions
    if (isAlpha(*e))
    {
        while (isAlpha(*e) || isDigit(*e))
        //while (isNotDelimeter(*e))
        {
            *t = *e;
            e++;
            t++;
        }
        *t = '\0';  // add a null character at the end of token

        // check if this is a variable or a function.
        // a function has a parentesis '(' open after the name
        char* e2 = NULL;
        e2 = e;

        // skip whitespaces
        while (*e2 == ' ' || *e2 == '\t')     // space or tab
        {
            e2++;
        }

        if (*e2 == '(')
        {
            token_type = FUNCTION;
        }
        else
        {
            token_type = VARIABLE;
        }
        return;
    }

    // something unknown is found, wrong characters -> a syntax error
    token_type = UNKNOWN;
    while (*e != '\0')
    {
        *t = *e;
        e++;
        t++;
    }
    *t = '\0';
    throw Error(row(), col(), 1, token);

    return;
}