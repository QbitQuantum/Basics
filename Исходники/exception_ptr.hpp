inline
std::string
diagnostic_information( exception_ptr const & p )
{
    if( p )
        try
        {
            rethrow_exception(p);
        }
        catch(
                ... )
        {
            return current_exception_diagnostic_information();
        }
    return "<empty>";
}