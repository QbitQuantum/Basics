Status apply_unary_operator(const Operator *operator, Stack **operands)
{
    double x = pop_double(operands);

    switch (operator->symbol)
    {
        case '+':
            break;
        case '-':
            x = -x;
            break;
        case '!':
            x = tgamma(x + 1);
            break;
        default:
            return ERROR_UNRECOGNIZED;
    }

    push_double(x, operands);

    return OK;
}