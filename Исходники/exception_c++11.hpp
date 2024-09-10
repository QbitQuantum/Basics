inline exception_ptr
make_exception_ptr( E const & e )
{
    try
    {
        throw e;
    }
    catch (...)
    {
        return current_exception();
    }
}