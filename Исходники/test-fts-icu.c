static void test_fts_icu_translate(void)
{
	const char *translit_id = "Any-Lower";
	UTransliterator *translit;
	buffer_t *dest = buffer_create_dynamic(pool_datastack_create(), 64);
	const UChar src[] = { 0xbd, 'B', 'C' };
	const char *error;
	unsigned int i;

	test_begin("fts_icu_translate");
	translit = get_translit(translit_id);
	for (i = N_ELEMENTS(src); i > 0; i--) {
		buffer_set_used_size(dest, 0);
		test_assert(fts_icu_translate(dest, src, i,
					      translit, &error) == 0);
		test_assert(dest->used == i * sizeof(UChar));
	}
	utrans_close(translit);
	test_end();
}