    Status WriteCmd::checkAuthForCommand( ClientBasic* client,
                                          const std::string& dbname,
                                          const BSONObj& cmdObj ) {

        Status status( auth::checkAuthForWriteCommand( client->getAuthorizationSession(),
                _writeType,
                NamespaceString( parseNs( dbname, cmdObj ) ),
                cmdObj ));

        // TODO: Remove this when we standardize GLE reporting from commands
        if ( !status.isOK() ) {
            setLastError( status.code(), status.reason().c_str() );
        }

        return status;
    }