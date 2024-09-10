static void
printProps(UChar32 codePoint) {
    char buffer[100];
    UErrorCode errorCode;

    /* get the character name */
    errorCode=U_ZERO_ERROR;
    u_charName(codePoint, U_UNICODE_CHAR_NAME, buffer, sizeof(buffer), &errorCode);

    /* print the code point and the character name */
    printf("U+%04lx\t%s\n", codePoint, buffer);

    /* print some properties */
    printf("  general category (numeric enum value): %u\n", u_charType(codePoint));

    /* note: these APIs do not provide the data from SpecialCasing.txt */
    printf("  is lowercase: %d  uppercase: U+%04lx\n", u_islower(codePoint), u_toupper(codePoint));

    printf("  is digit: %d  decimal digit value: %d\n", u_isdigit(codePoint), u_charDigitValue(codePoint));

    printf("  BiDi directional category (numeric enum value): %u\n", u_charDirection(codePoint));
}