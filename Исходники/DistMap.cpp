void DistMap::Translate
( vector<Int>& localInds, const vector<int>& origOwners ) const
{
    DEBUG_CSE
    const Int numLocalInds = localInds.size();

    // Count how many indices we need each process to map
    // Avoid unncessary branching within the loop by avoiding RowToProcess
    vector<int> requestSizes( commSize_, 0 );
    for( Int s=0; s<numLocalInds; ++s )
    {
        const Int i = localInds[s];
        if( i < numSources_ )
            ++requestSizes[origOwners[s]];
    }

    // Send our requests and find out what we need to fulfill
    vector<int> fulfillSizes( commSize_ );
    mpi::AllToAll( requestSizes.data(), 1, fulfillSizes.data(), 1, comm_ );

    // Prepare for the AllToAll to exchange request sizes
    vector<int> requestOffs, fulfillOffs;
    const int numRequests = Scan( requestSizes, requestOffs );
    const int numFulfills = Scan( fulfillSizes, fulfillOffs );

    // Pack the requested information 
    vector<int> requests( numRequests );
    auto offs = requestOffs;
    for( Int s=0; s<numLocalInds; ++s )
    {
        const Int i = localInds[s];
        if( i < numSources_ )
            requests[offs[origOwners[s]]++] = i;
    }

    // Perform the first index exchange
    vector<int> fulfills( numFulfills );
    mpi::AllToAll
    ( requests.data(), requestSizes.data(), requestOffs.data(),
      fulfills.data(), fulfillSizes.data(), fulfillOffs.data(), comm_ );

    // Map all of the indices in 'fulfills'
    for( int s=0; s<numFulfills; ++s )
    {
        const Int i = fulfills[s];
        const Int iLocal = i - blocksize_*commRank_;
        DEBUG_ONLY(
          if( iLocal < 0 || iLocal >= (Int)map_.size() )
              LogicError
              ("invalid request: i=",i,", iLocal=",iLocal,
               ", commRank=",commRank_,", blocksize=",blocksize_);
        )
        fulfills[s] = map_[iLocal];
    }