ex evalf( const ex& x )
{
	if( is_a<numeric>(x) )
		return bealab::erf( ex_to<numeric>(x).to_double() );
	else
		return erf(x).hold();
}