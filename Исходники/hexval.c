unsigned HexVal (int C)
/* Convert a hex digit into a value. The function will emit an error for
 * invalid hex digits.
 */
{
    if (!IsXDigit (C)) {
        Error ("Invalid hexadecimal digit: `%c'", C);
    }
    if (IsDigit (C)) {
        return C - '0';
    } else {
        return toupper (C) - 'A' + 10;
    }
}