/*
 * @implemented
 */
int itoa_s(int value, char *str, size_t size, int radix)
{
    return ltoa_s(value, str, size, radix);
}