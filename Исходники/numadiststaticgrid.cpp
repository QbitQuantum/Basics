void grid::NumaDistStaticGrid::getAt(void* buf, types::Type::converter_t converter,
        unsigned long x, unsigned long y, unsigned long z) {
    unsigned long block = getBlockByCoords(x, y, z);
    int remoteMPIRank = getBlockRank(block);
    unsigned long remoteThreadId = getThreadId(block);
    if (remoteMPIRank == getMPIRank() && pthread_equal(remoteThreadId, pthread_self())) {
        // Nice, this is a block where we are the master
        NumaLocalStaticGrid::getAt(buf, converter, x, y, z);
        return;
    }
    // This function will call getBlock, if we need to transfer the block
    NumaLocalCacheGrid::getAt(buf, converter, x, y, z);
}