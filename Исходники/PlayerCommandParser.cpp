PlayerCommandParser::PlayerCommandParser( QString line ) throw( std::invalid_argument )
{
    line = line.trimmed();
    if (line.isEmpty()) throw invalid_argument( "Command string seems to be empty" );

    qDebug() << line;

    m_command = extractCommand( line ); //removes the command string from line

    line = line.trimmed();

    QMap<QChar, QString> const args = extractArgs( line );
    QString const required = requiredArgs( m_command );

    for (int i = 0; i < required.length(); ++i)
    {
        QChar const c = required[i];
        if (!args.contains( c ))
            throw invalid_argument( "Mandatory argument unspecified: " + c.toAscii() );
    }

    m_playerId = args['c'];
    
    if (m_playerId.isEmpty())
        throw invalid_argument( "Player ID cannot be zero length" );

    switch (m_command)
    {
        case CommandStart:
            m_track = extractTrack( args );
            break;
        case CommandBootstrap:
            m_username = args['u'];
            break;
        case CommandInit:
            m_applicationPath = args['f'];
        default:
            break;
    }
}