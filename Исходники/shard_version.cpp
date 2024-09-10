    /**
     * @return true if had to do something
     */
    bool checkShardVersion( DBClientBase& conn_in , const string& ns , bool authoritative , int tryNumber ) {
        // TODO: cache, optimize, etc...

        WriteBackListener::init( conn_in );

        DBConfigPtr conf = grid.getDBConfig( ns );
        if ( ! conf )
            return false;

        DBClientBase* conn = getVersionable( &conn_in );
        assert(conn); // errors thrown above

        unsigned long long officialSequenceNumber = 0;

        ChunkManagerPtr manager;
        const bool isSharded = conf->isSharded( ns );
        if ( isSharded ) {
            manager = conf->getChunkManagerIfExists( ns , authoritative );
            // It's possible the chunk manager was reset since we checked whether sharded was true,
            // so must check this here.
            if( manager ) officialSequenceNumber = manager->getSequenceNumber();
        }

        // has the ChunkManager been reloaded since the last time we updated the connection-level version?
        // (ie., last time we issued the setShardVersions below)
        unsigned long long sequenceNumber = connectionShardStatus.getSequence(conn,ns);
        if ( sequenceNumber == officialSequenceNumber ) {
            return false;
        }


        ShardChunkVersion version = 0;
        if ( isSharded && manager ) {
            version = manager->getVersion( Shard::make( conn->getServerAddress() ) );
        }

        if( version == 0 ){
            LOG(0) << "resetting shard version of " << ns << " on " << conn->getServerAddress() << ", " <<
                      ( ! isSharded ? "no longer sharded" :
                      ( ! manager ? "no chunk manager found" :
                                    "version is zero" ) ) << endl;
        }


        LOG(2) << " have to set shard version for conn: " << conn << " ns:" << ns
               << " my last seq: " << sequenceNumber << "  current: " << officialSequenceNumber
               << " version: " << version << " manager: " << manager.get()
               << endl;

        BSONObj result;
        if ( setShardVersion( *conn , ns , version , authoritative , result ) ) {
            // success!
            LOG(1) << "      setShardVersion success: " << result << endl;
            connectionShardStatus.setSequence( conn , ns , officialSequenceNumber );
            return true;
        }

        LOG(1) << "       setShardVersion failed!\n" << result << endl;

        if ( result["need_authoritative"].trueValue() )
            massert( 10428 ,  "need_authoritative set but in authoritative mode already" , ! authoritative );

        if ( ! authoritative ) {
            checkShardVersion( *conn , ns , 1 , tryNumber + 1 );
            return true;
        }
        
        if ( result["reloadConfig"].trueValue() ) {
            if( result["version"].timestampTime() == 0 ){
                // reload db
                conf->reload();
            }
            else {
                // reload config
                conf->getChunkManager( ns , true );
            }
        }

        const int maxNumTries = 7;
        if ( tryNumber < maxNumTries ) {
            LOG( tryNumber < ( maxNumTries / 2 ) ? 1 : 0 ) 
                << "going to retry checkShardVersion host: " << conn->getServerAddress() << " " << result << endl;
            sleepmillis( 10 * tryNumber );
            checkShardVersion( *conn , ns , true , tryNumber + 1 );
            return true;
        }
        
        string errmsg = str::stream() << "setShardVersion failed host: " << conn->getServerAddress() << " " << result;
        log() << "     " << errmsg << endl;
        massert( 10429 , errmsg , 0 );
        return true;
    }