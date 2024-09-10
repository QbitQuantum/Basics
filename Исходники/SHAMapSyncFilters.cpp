void ConsensusTransSetSF::gotNode (bool fromFilter, const SHAMapNode& id, uint256 const& nodeHash,
                                   Blob& nodeData, SHAMapTreeNode::TNType type)
{
    if (fromFilter)
        return;

    m_nodeCache.insert (nodeHash, nodeData);

    if ((type == SHAMapTreeNode::tnTRANSACTION_NM) && (nodeData.size () > 16))
    {
        // this is a transaction, and we didn't have it
        WriteLog (lsDEBUG, TransactionAcquire) << "Node on our acquiring TX set is TXN we may not have";

        try
        {
            Serializer s (nodeData.begin () + 4, nodeData.end ()); // skip prefix
            SerializerIterator sit (s);
            SerializedTransaction::pointer stx = boost::make_shared<SerializedTransaction> (boost::ref (sit));
            assert (stx->getTransactionID () == nodeHash);
            getApp().getJobQueue ().addJob (jtTRANSACTION, "TXS->TXN",
                                           BIND_TYPE (&NetworkOPs::submitTransaction, &getApp().getOPs (), P_1, stx));
        }
        catch (...)
        {
            WriteLog (lsWARNING, TransactionAcquire) << "Fetched invalid transaction in proposed set";
        }
    }
}