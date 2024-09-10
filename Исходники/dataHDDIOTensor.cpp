bool DataHDDIOTensorQuantized2G::_readIdsRanksScales( )
{
    assert( _nodesIds && _ranks && _scales );

    const size_t size = _nodesIds->size();

    if( _ranks->size()  != size ||
        _scales->size() != size )
    {
        LOG_ERROR << "Size of _ranks or _scales is incorect " << std::endl;
        return false;
    }

    memset( &((*_nodesIds)[ 0]), 0, size*sizeof((*_nodesIds)[0]));
    memset( &((*_ranks)[    0]), 0, size*sizeof((*_ranks)[   0]));
    memset( &((*_scales)[   0]), 0, size*sizeof((*_scales)[  0]));

    std::string fName = getRanksFileName();

// Read ranks, build ids
    std::vector<double> data( size );
    const uint32_t bytesToRead = data.size()*sizeof(data[0]);

    util::InFile inFile;
    if( !inFile.open( fName, std::ios::binary, true ) ||
        !inFile.read( bytesToRead, bytesToRead, &data[0] ))
        return false;

    byte     maxRank   = 0;
    uint32_t currentId = 0;
    for( size_t i = 0; i < data.size(); ++i )
    {
        int32_t rank = static_cast<int32_t>( data[i]+0.5 );
        if( rank < 0 || rank > 255 )
        {
            LOG_ERROR << "Incorrect rank? (" << rank << ")" << std::endl;
            break;
        }
        if( rank > 0 )
        {
            currentId++;
            (*_nodesIds)[i] = currentId;
            (*_ranks)[   i] = rank;
            if( maxRank < rank )
                maxRank = rank;
        }
    }
    setMaxRankDim( maxRank );

    // check that all non zero ranks have the same size
    for( size_t i = 0; i < size; ++i )
        if( (*_ranks)[i] != 0 && (*_ranks)[i] != maxRank )
        {
            LOG_ERROR << "One of the non-zero ranks is not equal to maxRank!" << std::endl;
            abort();
        }

    // Read scales
    if( !inFile.read( bytesToRead*4, bytesToRead, &data[0] ))
        return false;

    for( size_t i = 0; i < data.size(); ++i )
    {
        if( (*_ranks)[i] > 0 )
            (*_scales)[i] = log2f( 1.0 + data[i] ) / 127.f;
    }

#if 0 // print first elements of rank array
    for( size_t i = 0; i < 1+8+64; ++i )
    {
        std::cout << "i: " << i << " id: " << (int)nodes[i].id << " rank: " << (int)ranks[i] << " scale: " << scales[i] << std::endl;
    }
#endif
    return true;
}