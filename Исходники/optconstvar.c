static void cvalue_list_sort_abs(cvalue_list *l)
{
    qsort(l->data, l->len, sizeof(l->data[0]), cvalue_sort_abs_comp);
}