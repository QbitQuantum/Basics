bool Symbol::IsSymbol(unsigned char sym)
{
    return isspace(sym) || isblank(sym) || ispunct(sym);
}