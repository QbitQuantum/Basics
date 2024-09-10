void AccessLog::log( HttpConnection* pConn )
{
    int  n;
    HttpReq*  pReq  = pConn->getReq();
    HttpResp* pResp = pConn->getResp();
    const char * pUser = pReq->getAuthUser();
    long contentWritten = pResp->getBodySent();
    const ClientInfo * pInfo = pConn->getClientInfo();
    const char * pAddr = pInfo->getHostName();
    pResp->needLogAccess( 0 );
    if ( m_iPipedLog )
    {
        if ( !m_pManager )
            return;
        m_pAppender = m_pManager->getAppender();
        if ( !m_pAppender )
            return;
    }
    
    if ( m_pCustomFormat )
        return customLog( pConn );
    
    if (( pAddr )&&( *pAddr ))
    {
        n = pInfo->getHostNameLen();
    }
    else
    {
        pAddr = pInfo->getAddrString();
        n = pInfo->getAddrStrLen();
    }
    m_buf.appendNoCheck( pAddr, n );
    if ( ! *pUser )
    {
        m_buf.appendNoCheck( " - - ", 5 );
    }
    else
    {
        n = safe_snprintf( m_buf.end(), 70, " - \"%s\" ", pUser );
        m_buf.used( n );
    }

    DateTime::getLogTime( pConn->getReqTime(), m_buf.end() );
    m_buf.used( 30 );
    n = pReq->getOrgReqLineLen();
    char * pOrgReqLine = (char *)pReq->getOrgReqLine();
    if ( pReq->getVersion() == HTTP_1_0 )
        *(pOrgReqLine + n - 1) = '0';
    if (( n > 4096 )||( m_buf.available() < 100 + n ))
    {
        flush();
        m_pAppender->append( pOrgReqLine, n );
    }
    else
        m_buf.appendNoCheck(pOrgReqLine, n );
    m_buf.append( '"' );
    m_buf.appendNoCheck(
        HttpStatusCode::getCodeString( pReq->getStatusCode() ), 5 );
    if ( contentWritten == 0 )
    {
        m_buf.append( '-' );
    }
    else
    {
        n = safe_snprintf( m_buf.end(), 20, "%ld", contentWritten );
        m_buf.used( n );
    }
    if ( getAccessLogHeader() & LOG_REFERER )
    {
        m_buf.append( ' ' );
        appendStr( pReq->getHeader( HttpHeader::H_REFERER ),
                pReq->getHeaderLen( HttpHeader::H_REFERER ));
    }
    if ( getAccessLogHeader() & LOG_USERAGENT )
    {
        m_buf.append( ' ' );
        appendStr( pReq->getHeader( HttpHeader::H_USERAGENT),
                pReq->getHeaderLen( HttpHeader::H_USERAGENT) );
    }
    if ( getAccessLogHeader() & LOG_VHOST )
    {
        m_buf.append( ' ' );
        appendStr( pReq->getHeader( HttpHeader::H_HOST ),
                pReq->getHeaderLen( HttpHeader::H_HOST ) );
    }
    m_buf.append( '\n' );
    if (( m_buf.available() < MAX_LOG_LINE_LEN )
        ||!asyncAccessLog() )
    {
        flush();
    }
}