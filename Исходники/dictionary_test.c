/**
 Testuje dictionary_hints_word_without_ignores
 @param[in,out] state Środowisko
 */
static void dictionary_hints_word_without_ignores_test(void **state)
{
	(void)state;
	assert_int_equal(wcscoll(L"abc", dictionary_hints_word_without_ignores(L"^a^b^c^")), 0);
	assert_int_equal(wcscoll(L"", dictionary_hints_word_without_ignores(L"^^^")), 0);
}