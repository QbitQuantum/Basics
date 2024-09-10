    return stream
        << credential.m_serverUuid
        << credential.m_userName
        << credential.m_login
        << encrypt( credential.m_password );
}

QDataStream& operator >>( QDataStream& stream, ServerCredential& credential )
{
    QByteArray password;
    stream
        >> credential.m_serverUuid
        >> credential.m_userName
        >> credential.m_login
        >> password;
    credential.m_password = decrypt( password );
    return stream;
}

HttpCredential::HttpCredential()
{
}

HttpCredential::HttpCredential( const QString& hostName, const QString& login, const QString& password ) :
    m_hostName( hostName ),
    m_login( login ),
    m_password( password )
{
}

HttpCredential::~HttpCredential()