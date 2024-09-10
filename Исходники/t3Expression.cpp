t3Precedence t3Expression::getToken(int n)
{
    const char symbol = getChar(n);
    switch (symbol) {
        case '(':
            return lparen;
        case ')':
            return rparen;
        case '+':
            return plus;
        case '-':
            return minus;
        case '/':
            return divide;
        case '*':
            return times;
        case '%':
            return mod;
        case ' ':
            return eos;
        default:
            return operand;
    }
}