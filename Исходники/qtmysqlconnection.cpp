void cQTMySQLConnection::setHostName( const QString &p_qsHost ) throw()
/* This function sets the Host Name for the MySQL database access.
 * If the database is already open, it will be closed first. */
{
    if( getHostName() != p_qsHost )
    {
        close();
        m_poDB->setHostName( p_qsHost );
    }
}