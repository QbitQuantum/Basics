const char* wxURI::ParsePort(const char* uri)
{
    // port          = *DIGIT
    if( *uri == ':' )
    {
        ++uri;
        while ( IsDigit(*uri) )
        {
            m_port += *uri++;
        }

        m_fields |= wxURI_PORT;
    }

    return uri;
}