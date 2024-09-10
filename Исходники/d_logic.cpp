        bool run(const char *cmdns, BSONObj& cmdObj, string& errmsg, BSONObjBuilder& result, bool){
            // see MoveShardStartCommand::run
            
            string ns = cmdObj["moveshard.finish"].valuestrsafe();
            if ( ns.size() == 0 ){
                errmsg = "need ns as cmd value";
                return false;
            }

            string to = cmdObj["to"].valuestrsafe();
            if ( to.size() == 0 ){
                errmsg = "need to specify server to move shard to";
                return false;
            }


            unsigned long long newVersion = getVersion( cmdObj["newVersion"] , errmsg );
            if ( newVersion == 0 ){
                errmsg = "have to specify new version number";
                return false;
            }
                                                        
            BSONObj finishToken = cmdObj.getObjectField( "finishToken" );
            if ( finishToken.isEmpty() ){
                errmsg = "need finishToken";
                return false;
            }
            
            if ( ns != finishToken["collection"].valuestrsafe() ){
                errmsg = "namespaced don't match";
                return false;
            }
            
            // now we're locked
            myVersions[ns] = newVersion;
            NSVersions * versions = clientShardVersions.get();
            if ( ! versions ){
                versions = new NSVersions();
                clientShardVersions.reset( versions );
            }
            (*versions)[ns] = newVersion;
            
            BSONObj res;
            bool ok;
            
            {
                dbtemprelease unlock;
                
                ScopedDbConnection conn( to );
                ok = conn->runCommand( "admin" , 
                                       BSON( "finishCloneCollection" << finishToken ) ,
                                       res );
                conn.done();
            }
            
            if ( ! ok ){
                // uh oh
                errmsg = "finishCloneCollection failed!";
                result << "finishError" << res;
                return false;
            }
            
            // wait until cursors are clean
            cerr << "WARNING: deleting data before ensuring no more cursors TODO" << endl;
            
            dbtemprelease unlock;

            DBDirectClient client;
            BSONObj removeFilter = finishToken.getObjectField( "query" );
            client.remove( ns , removeFilter );

            return true;
        }