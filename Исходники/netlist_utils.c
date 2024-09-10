void sort_signal_list_alphabetically(signal_list_t *list)
{
	qsort(list->pins, list->count,  sizeof(npin_t *), compare_npin_t_names);
}