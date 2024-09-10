    TEST(DBHelperTests, FindDiskLocsTooBig) {

        DBDirectClient client;
        OperationContextImpl txn;

        client.remove( ns, BSONObj() );

        int numDocsInserted = 10;
        for ( int i = 0; i < numDocsInserted; ++i ) {
            client.insert( ns, BSON( "_id" << i ) );
        }

        // Very small max size
        long long maxSizeBytes = 10;

        set<DiskLoc> locs;
        long long numDocsFound;
        long long estSizeBytes;
        {
            Lock::DBRead lk(txn.lockState(), ns);
            Client::Context ctx( ns );
            KeyRange range( ns,
                            BSON( "_id" << 0 ),
                            BSON( "_id" << numDocsInserted ),
                            BSON( "_id" << 1 ) );

            Status result = Helpers::getLocsInRange( &txn,
                                                     range,
                                                     maxSizeBytes,
                                                     &locs,
                                                     &numDocsFound,
                                                     &estSizeBytes );

            // Make sure we get the right error code and our count and size estimates are valid
            ASSERT_EQUALS( result.code(), ErrorCodes::InvalidLength );
            ASSERT_EQUALS( numDocsFound, numDocsInserted );
            ASSERT_GREATER_THAN( estSizeBytes, maxSizeBytes );
        }
    }