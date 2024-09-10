Value GetBlock::operator()(const Array& params, bool fHelp) {
    if (fHelp || params.size() != 1)
        throw RPC::error(RPC::invalid_params, "getblock <hash>\n"
                            "Returns details of a block with given block-hash.");
    
    std::string strHash = params[0].get_str();
    uint256 hash(strHash);
    
    BlockIterator blk = _node.blockChain().iterator(hash);
    
    Block block;
    _node.blockChain().getBlock(hash, block);
    
    if (block.isNull())
        throw RPC::error(RPC::invalid_request,  "Block not found");
        
    Object result;
    result.push_back(Pair("hash", blk->hash.GetHex()));
    result.push_back(Pair("blockcount", blk.height()));
    result.push_back(Pair("version", block.getVersion()));
    result.push_back(Pair("merkleroot", block.getMerkleRoot().GetHex()));
    result.push_back(Pair("time", (boost::int64_t)block.getBlockTime()));
    result.push_back(Pair("nonce", (boost::uint64_t)block.getNonce()));
    result.push_back(Pair("difficulty", _node.blockChain().getDifficulty(blk)));
    Array txhashes;
    BOOST_FOREACH (const Transaction&tx, block.getTransactions())
    txhashes.push_back(tx.getHash().GetHex());
    
    result.push_back(Pair("tx", txhashes));

    BlockIterator prev = blk + 1;
    BlockIterator next = blk - 1;
    if (!!prev)
        result.push_back(Pair("hashprevious", prev->hash.GetHex()));
    if (!!next )
        result.push_back(Pair("hashnext", next->hash.GetHex()));
    
    return result;
}        