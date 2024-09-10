int main( void )
{
    TESTCASE(iswlower(L'a'));
    TESTCASE(iswlower(L'e'));
    TESTCASE(iswlower(L'z'));
    TESTCASE(!iswlower(L'A'));
    TESTCASE(!iswlower(L'E'));
    TESTCASE(!iswlower(L'Z'));
    return TEST_RESULTS;
}