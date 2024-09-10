void basic_simple_nt6_event_log_backend< CharT >::do_consume(
    values_view_type const& values, target_string_type const& formatted_message)
{
    EventWriteString(m_pImpl->m_ProviderHandle, m_pImpl->get_level(values), 0ULL /* keyword */, formatted_message.c_str());
}