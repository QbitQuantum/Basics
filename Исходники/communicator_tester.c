/**
 * Tests the wide character output function "fwprintf".
 *
 * CAUTION! Some wide characters are not recognised by the gnu/linux console yet,
 * so that only question marks appear on the place of the corresponding character, e.g.:
 * - U+70BA CJK UNIFIED IDEOGRAPH-70BA 為
 * - U+256D BOX DRAWINGS LIGHT ARC DOWN AND RIGHT ╭
 *
 * The ASCII characters and the following wide characters are recognised properly:
 * - U+2500 BOX DRAWINGS LIGHT HORIZONTAL ─
 *
 * Results:
 * - if defining wide character array elements as symbol:
 *       use L before EACH single character to convert it into a wide character,
 *       since otherwise, it is interpreted as "normal" character and not displayed properly
 * - if defining wide character array elements as number/ code:
 *       use the UTF-16 encoding and NOT UTF-8, since UTF-8 may offer more than one number to be written
 *       and writing them one after the other into the array, separated by commata or not, brings wrong results
 * - a termination is NOT necessary for array definition, as the array count is given as usual in CYBOI
 * - the %s placeholder is not enough, since the wide character strings are not printed;
 *       a letter "l" HAS TO BE added to make output work, e.g.: %ls
 * - a cast to (wchar_t*) is NOT necessary, since the L before a string already does that
 *       and self-defined constants are of type wchar_t anyway
 */
void test_wide_character_wprintf() {

    /** The test wide character string. */
    // The following does NOT work and will bring the compilation warning:
    // "cast to pointer from integer of different size"
    // The reason is that an "L" is needed before EACH character, to make it a wide character!
    // Therefore, the following three lines are commented out.
    // static wchar_t TEST_WIDE_CHARACTER_STRING_ARRAY[] = {'r', 'e', 'c', 't', 'a', 'n', 0xE7, 0x82, 0xBA, 'l', 'e'};
    // static wchar_t TEST_WIDE_CHARACTER_STRING_ARRAY[] = {'r', 'e', 'c', 't', 'a', 'n', 0xE2, 0x94, 0x80, 'l', 'e'};
    // static wchar_t* TEST_WIDE_CHARACTER_STRING = TEST_WIDE_CHARACTER_STRING_ARRAY;

//??    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_TERMINATION_ARRAY[] = {'r', 'e', 'c', 't', 'a', 'n', '為', 'l', 'e', '\0'};
    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_TERMINATION_ARRAY[] = {'r', 'e', 'c', 't', 'a', 'n', '─', 'l', 'e', '\0'};
    static wchar_t* TEST_WIDE_CHARACTER_STRING_WITH_TERMINATION = TEST_WIDE_CHARACTER_STRING_WITH_TERMINATION_ARRAY;

//??    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_L_ARRAY[] = {L'r', L'e', L'c', L't', L'a', L'n', L'為', L'l', L'e'};
    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_L_ARRAY[] = {L'r', L'e', L'c', L't', L'a', L'n', L'─', L'l', L'e'};
    static wchar_t* TEST_WIDE_CHARACTER_STRING_WITH_L = TEST_WIDE_CHARACTER_STRING_WITH_L_ARRAY;

//??    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_L_AND_TERMINATION_ARRAY[] = {L'r', L'e', L'c', L't', L'a', L'n', L'為', L'l', L'e', 0x0000};
    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_L_AND_TERMINATION_ARRAY[] = {L'r', L'e', L'c', L't', L'a', L'n', L'─', L'l', L'e', 0x0000};
    static wchar_t* TEST_WIDE_CHARACTER_STRING_WITH_L_AND_TERMINATION = TEST_WIDE_CHARACTER_STRING_WITH_L_AND_TERMINATION_ARRAY;

//??    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_UTF_8_CODES_AND_TERMINATION_ARRAY[] = {0x0072, 0x0065, 0x0063, 0x0074, 0x0061, 0x006E, 0xE7, 0x82, 0xBA, 0x006C, 0x0065, 0x0000};
    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_UTF_8_CODES_AND_TERMINATION_ARRAY[] = {0x0072, 0x0065, 0x0063, 0x0074, 0x0061, 0x006E, 0xE2, 0x94, 0x80, 0x006C, 0x0065, 0x0000};
    static wchar_t* TEST_WIDE_CHARACTER_STRING_WITH_UTF_8_CODES_AND_TERMINATION = TEST_WIDE_CHARACTER_STRING_WITH_UTF_8_CODES_AND_TERMINATION_ARRAY;

//??    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_UTF_16_CODES_AND_TERMINATION_ARRAY[] = {0x0072, 0x0065, 0x0063, 0x0074, 0x0061, 0x006E, 0x70BA, 0x006C, 0x0065, 0x0000};
    static wchar_t TEST_WIDE_CHARACTER_STRING_WITH_UTF_16_CODES_AND_TERMINATION_ARRAY[] = {0x0072, 0x0065, 0x0063, 0x0074, 0x0061, 0x006E, 0x2500, 0x006C, 0x0065, 0x0000};
    static wchar_t* TEST_WIDE_CHARACTER_STRING_WITH_UTF_16_CODES_AND_TERMINATION = TEST_WIDE_CHARACTER_STRING_WITH_UTF_16_CODES_AND_TERMINATION_ARRAY;

    // Set stream orientation to wide character mode.
    // The second function argument has the following meaning:
    // - positive value: wide character mode
    // - negative value: (narrow) character mode
    fwide(stdout, *NUMBER_1_INTEGER_MEMORY_MODEL);

    log_write_terminated_message((void*) stdout, L"Test fputws.\n");
//??    log_write_terminated_message((void*) stdout, (wchar_t*) TEST_WIDE_CHARACTER_STRING);
    wprintf(L"Test wprintf without stream argument.\n");

    // Test wide character constants.
    fwprintf(stdout, L"Test hello world ls: %10ls \n", "hello world");
    fwprintf(stdout, L"Test hello world s: %10s \n", "hello world");
    fwprintf(stdout, L"Test hello world L ls with cast: %10ls \n", (wchar_t*) L"hello world");
    fwprintf(stdout, L"Test hello world L s with cast: %10s \n", (wchar_t*) L"hello world");
    fwprintf(stdout, L"Test hello world L ls without cast: %10ls\n", L"hello world");
    fwprintf(stdout, L"Test hello world L s without cast: %10s\n", L"hello world");

//??    fwprintf(stdout, L"Test wide character string ls: %5ls \n", TEST_WIDE_CHARACTER_STRING);
//??    fwprintf(stdout, L"Test wide character string s: %5s \n", TEST_WIDE_CHARACTER_STRING);
    fwprintf(stdout, L"Test wide character string with termination: %5ls \n", TEST_WIDE_CHARACTER_STRING_WITH_TERMINATION);

    fwprintf(stdout, L"Test wide character string L ls: %5ls \n", TEST_WIDE_CHARACTER_STRING_WITH_L);
    fwprintf(stdout, L"Test wide character string L s: %5s \n", TEST_WIDE_CHARACTER_STRING_WITH_L);
    fwprintf(stdout, L"Test wide character string L and termination: %5ls \n", TEST_WIDE_CHARACTER_STRING_WITH_L_AND_TERMINATION);

    fwprintf(stdout, L"Test wide character string with UTF-8 codes and termination ls: %5ls \n", TEST_WIDE_CHARACTER_STRING_WITH_UTF_8_CODES_AND_TERMINATION);
    fwprintf(stdout, L"Test wide character string with UTF-8 codes and termination s: %5s \n", TEST_WIDE_CHARACTER_STRING_WITH_UTF_8_CODES_AND_TERMINATION);
    fwprintf(stdout, L"Test wide character string with UTF-16 codes and termination ls: %5ls \n", TEST_WIDE_CHARACTER_STRING_WITH_UTF_16_CODES_AND_TERMINATION);
    fwprintf(stdout, L"Test wide character string with UTF-16 codes and termination s: %5s \n", TEST_WIDE_CHARACTER_STRING_WITH_UTF_16_CODES_AND_TERMINATION);

//??    fwprintf(stdout, L"Test wide character string fourth letter with cast: %lc \n", (wchar_t*) TEST_WIDE_CHARACTER_STRING[3]);
//??    fwprintf(stdout, L"Test wide character string fourth letter without cast: %lc \n", TEST_WIDE_CHARACTER_STRING[3]);

    log_write_terminated_message((void*) stdout, L"Test END.\n");
}