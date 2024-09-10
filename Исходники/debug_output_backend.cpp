BOOST_LOG_EXPORT bool basic_debug_output_backend< CharT >::debugger_presence_filter::operator() (values_view_type const& values) const
{
    return (IsDebuggerPresent() != FALSE);
}