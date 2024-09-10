static void sort_ref_range(int bottom, int top)
{
	QSORT(ref_name + bottom, top - bottom, compare_ref_name);
}