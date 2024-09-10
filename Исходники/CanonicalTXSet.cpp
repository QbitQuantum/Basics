void CanonicalTXSet::insert (std::shared_ptr<STTx const> const& txn)
{
    map_.insert (
        std::make_pair (
            Key (
                accountKey (txn->getAccountID(sfAccount)),
                txn->getSequence (),
                txn->getTransactionID ()),
            txn));
}