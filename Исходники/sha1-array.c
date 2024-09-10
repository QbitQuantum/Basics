static void oid_array_sort(struct oid_array *array)
{
	QSORT(array->oid, array->nr, void_hashcmp);
	array->sorted = 1;
}