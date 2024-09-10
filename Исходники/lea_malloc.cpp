/* malloc() replacment functions are found below:
 * operator new() and operator new[]() are defined in malloc_extra.cpp
 * because this code is inside extern "C" { ... }
 */
void *constrained_malloc( size_t nbytes )
{
	if ( !using_opera_allocator() )
		return malloc(nbytes);

	void *res = NULL;

	MALLOC_WRAPPED_ACTION (
		if ( alloc_within_limits(nbytes) )
	    {
		    g_constrained_allocation = 1;
			res = mALLOc(nbytes);
			g_constrained_allocation = 0;
			constrain_tag_allocation(res);
		}
	);