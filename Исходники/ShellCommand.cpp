ShellCommand::ShellCommand(const QString & fullCommand)
{
    bool inQuotes = false;

    QString builder;

    for ( int i = 0 ; i < fullCommand.count() ; i++ ) {
        QChar ch = fullCommand[i];

        const bool isLastChar = ( i == fullCommand.count() - 1 );
        const bool isQuote = ( ch == '\'' || ch == '\"' );

        if ( !isLastChar && isQuote ) {
            inQuotes = !inQuotes;
        } else {
            if ( (!ch.isSpace() || inQuotes) && !isQuote ) {
                builder.append(ch);
            }

            if ( (ch.isSpace() && !inQuotes) || ( i == fullCommand.count()-1 ) ) {
                _arguments << builder;
                builder.clear();
            }
        }
    }
}