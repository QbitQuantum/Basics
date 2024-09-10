void sa_sort_dec_ignore_case(Array array) {
	sa_assert_element_size(array);
	qsort(array->a, array->n, sizeof(String), string_compare_dec_ignore_case);
}