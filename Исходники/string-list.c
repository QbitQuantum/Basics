void string_list_sort(struct string_list *list)
{
	QSORT_S(list->items, list->nr, cmp_items,
		list->cmp ? list->cmp : strcmp);
}