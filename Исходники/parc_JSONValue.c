static long double
_parcJSONValue_GetNumber(const PARCJSONValue *value)
{
    long double fraction = value->value.number.fraction / powl(10.0, value->value.number.fractionLog10);
    long double number = (long double) value->value.number.sign * ((long double) value->value.number.whole + fraction);

    long double result = number * powl(10.0, (long double) value->value.number.exponent);

    return result;
}