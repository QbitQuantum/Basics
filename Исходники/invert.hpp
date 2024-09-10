inline
mat< typename detail::promote< T >::type, N >
inv( const mat< T, N >& rhs )
{
    mat< typename detail::promote< T >::type, N > res( rhs );

    if ( !static_cast< bool >( invert( res ) ) )
    {
        throw ::std::runtime_error( "mat<>: inverting singular matrix" );
    }

    return res;
}