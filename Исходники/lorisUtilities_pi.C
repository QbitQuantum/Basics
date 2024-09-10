/*	Apply a function to each Breakpoint in a Partial. The function
	is called once for each Breakpoint in the source Partial. The
	function may modify the Breakpoint (but should not otherwise attempt 
	to modify the Partial). The data parameter can be used to supply extra
	user-defined data to the function. Pass 0 if no additional data is needed.
	The function should return 0 if successful. If the function returns
	a non-zero value, then forEachBreakpoint immediately returns that value
	without applying the function to any other Breakpoints in the Partial.
	forEachBreakpoint returns zero if all calls to func return zero.
 */
int forEachBreakpoint( Partial * p,
		 			   int ( * func )( Breakpoint * p, double time, void * data ),
			 		   void * data )
{
	int result = 0;
	try 
	{
		ThrowIfNull((Partial *) p);

		Partial::iterator it;
		for ( it = p->begin(); 0 == result && it != p->end(); ++it )
		{
			result = func( &(it.breakpoint()), it.time(), data );
		}
	}
	catch( Exception & ex ) 
	{
		std::string s("Loris exception in forEachBreakpoint(): " );
		s.append( ex.what() );
		handleException( s.c_str() );
	}
	catch( std::exception & ex ) 
	{
		std::string s("std C++ exception in forEachBreakpoint(): " );
		s.append( ex.what() );
		handleException( s.c_str() );
	}
	
	return result;
}