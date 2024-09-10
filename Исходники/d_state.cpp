    ShardChunkManagerPtr ShardingState::getShardChunkManager( const string& ns ){
        ConfigVersion version;
        { 
            // check cache
            scoped_lock lk( _mutex );

            NSVersionMap::const_iterator it = _versions.find( ns );
            if ( it == _versions.end() ) {
                return ShardChunkManagerPtr();
            }

            version = it->second;

            // TODO SERVER-1849 pending drop work
            // the manager should use the cached version only if the versions match exactly
            ShardChunkManagerPtr p = _chunks[ns];
            if ( p && p->getVersion() >= version ){
                // our cached version is good, so just return
                return p;                
            }
        }

        // load the chunk information for this shard from the config database
        // a reminder: ShardChunkManager may throw on construction
        const string c = (_configServer == _shardHost) ? "" /* local */ : _configServer;
        ShardChunkManagerPtr p( new ShardChunkManager( c , ns , _shardName ) );

        // TODO SERVER-1849 verify that the manager's version is exactly the one requested
        // If not, do update _chunks, but fail the request.
        { 
            scoped_lock lk( _mutex );
            _chunks[ns] = p;
        }

        return p;
    }