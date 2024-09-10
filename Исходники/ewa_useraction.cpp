EWAUserAction& EWAUserAction::operator=( const EWAUserAction& other )
{
    m_pWebView = other.m_pWebView;
    //m_clickedElement = other.m_clickedElement;
    m_webViewSize = other.m_webViewSize;

    setTime( other.getTime() );
    setEvent( other.getEvent() );
    
    return *this;
}