bool expression_calc::is_operator( const std::string& s ) 
{
	return prio( s ) < strlen( operators() );
}