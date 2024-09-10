SqlCommandList KraftDB::parseCommandFile( const QString& file )
{
    QString sqlFile;
    QString env = QString::fromUtf8( qgetenv( "KRAFT_HOME" ) );
    if( !env.isEmpty() && env.right(1) != QDir::separator () ) {
        env += QDir::separator ();
    }

    QString driverPrefix = "mysql"; // Default on mysql
    if( mDatabaseDriver.toLower() == "qsqlite") {
        driverPrefix = "sqlite3";
    }

    // kDebug() << "XXXXXXXXXX: " << stdDirs.resourceDirs("data");

    if( env.isEmpty() ) {
        // Environment-Variable is empty, search in KDE paths
        QString fragment = QString("kraft/dbmigrate/%1/%2").arg(driverPrefix).arg(file );
        sqlFile = KStandardDirs::locate("data", fragment );
        kDebug() << "Searching for this fragment: " << fragment;
        // search in dbcreate as well.
        if ( sqlFile.isEmpty() ) {
            fragment = QString("kraft/dbinit/%1/%2").arg(driverPrefix).arg(file );
            kDebug() << "Also searching in " << fragment;
            sqlFile = KStandardDirs::locate( "data", fragment );
        }
    } else {
        // read from environment variable path
        QString envPath = QString( "%1/database/%2/%3").arg(env).arg(driverPrefix).arg(file);
        kDebug() << "Environment variable KRAFT_HOME set, searching for DB setup files in " << envPath;
        if( QFile::exists( envPath ) ) {
            sqlFile = envPath;
        } else if( QFile::exists( QString( "%1/database/%2/migration/%3").arg(env).arg(driverPrefix).arg(file ) ) ){
            sqlFile = QString( "%1/database/%2/migration/%3").arg(env).arg(driverPrefix).arg(file );
        }
    }

    SqlCommandList retList;

    if ( ! sqlFile.isEmpty() ) {
        kDebug() << "Opening migration file " << sqlFile << endl;

        QFile f( sqlFile );
        if ( !f.open( QIODevice::ReadOnly ) ) {
            kDebug() << "Could not open " << sqlFile << endl;
        } else {
            QTextStream ts( &f );
            ts.setCodec("UTF-8");

            QString allSql = ts.readAll(); //Not sure of this one!
            QStringList sqlList = allSql.split(";");

            QRegExp reg( "\\s*(#|--)\\s*message:? ?(.*)\\s*\\n" );
            QRegExp failreg( "\\s*(#|--)\\s*mayfail\\s*\\n" );
            reg.setMinimal( true );

            QListIterator<QString> it(sqlList);

            while( it.hasNext() ) {
                QString msg, command;

                QString sqlFragment = it.next().trimmed();

                int pos = reg.indexIn( sqlFragment.toLower(),  0 );
                if ( pos > -1 ) {
                    msg = reg.cap( 2 );
                    // kDebug() << "SQL-Commands-Parser: Msg: >" << msg << "<" << endl;
                }

                bool mayfail = false;
                pos = failreg.indexIn( sqlFragment.toLower(), 0 );
                if( pos > -1 ) {
                    mayfail = true;
                }
                bool clean = false;
                while( ! clean ) {
                    if(  sqlFragment.startsWith("#") || sqlFragment.startsWith("--") ) {
                        // remove the comment line.
                        int newLinePos = sqlFragment.indexOf('\n');
                        // kDebug() << "Found newline in <" << sqlFragment << ">:" << newLinePos;
                        if(newLinePos > 0) {
                            sqlFragment = sqlFragment.remove( 0, 1+sqlFragment.indexOf('\n') );
                        } else {
                            sqlFragment = QString();
                        }
                        // kDebug() << "Left over SQL Fragment:" << sqlFragment;
                    } else {
                        clean = true;
                    }
                }

                if( !sqlFragment.isEmpty() ) {

                    if( sqlFragment.startsWith( "CREATE TRIGGER", Qt::CaseInsensitive )) {
                        // Triggers contain a ; which scares the parser. In case of triggers we pull
                        // the next item in the list which should be the END; keyword.
                        command = sqlFragment + ";";
                        if( it.hasNext())
                            command += it.next();
                    } else {
                        // ordinary command, we take it as it is.
                        command = sqlFragment;
                    }
                    if( !( command.isEmpty() && msg.isEmpty() ) ) {
                        retList.append( SqlCommand( command, msg, mayfail ) );
                    }
                }
            }
        }
    } else {
        kDebug() << "ERR: Can not find sql file " << file;
    }

    return retList;
}