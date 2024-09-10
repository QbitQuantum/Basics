RCP<const Number> Number::div(const Number &other) const
{
    return mul(*other.pow(*integer(-1)));
}