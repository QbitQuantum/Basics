//! Runs consistency checks on the heap. 
//! This is enabled in release builds, unlike _CrtCheckMemory.
Value* heapcheck_cf(Value**, int count)
{
	check_arg_count(heapcheck, 0, count);
	int heap_status = _heapchk();
	/* I'll use these later
	switch (heap_status)
	{
	case _HEAPOK:
		break;
	case _HEAPEMPTY:
		break;
	case _HEAPBADPTR:
		break;
	case _HEAPBADNODE:
		break;
	case _HEAPBADBEGIN:
		break;
	}
	*/
	return (heap_status == _HEAPOK) ? &true_value : &false_value;
}