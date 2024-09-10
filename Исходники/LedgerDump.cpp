/**
 * Decode a JSON value representing a ledger (as found in a dump file) into
 * a 3-tuple of: #1 a Ledger object, #2 a SHAMap holding a set of
 * transactions, and #3 a vector of transaction IDs indicating the order
 * that the transactions in the SHAMap were applied in the Ledger.
 */
static std::tuple<Ledger::pointer, SHAMap::pointer, std::vector<uint256> >
loadLedgerAndTransactionsFromJSON(Application& app, Json::Value const& j)
{
    require (j.isMember ("raw") && j["raw"].isString (),
             "JSON ledger \"raw\" entry missing or non-string");

    std::pair<Blob, bool> ledgerBlob = strUnHex (j["raw"].asString ());
    require (ledgerBlob.second, "Error decoding ledger \"raw\" field ");

    Ledger::pointer ledger = boost::make_shared<Ledger> (ledgerBlob.first, true);

    require (j.isMember ("txs") && j["txs"].isArray(),
             "JSON ledger \"txs\" entry missing or non-array");

    // Fill a SHAMap full of the current transactions.
    SHAMap::pointer txSet =
        boost::make_shared<SHAMap> (smtTRANSACTION, app.getFullBelowCache());

    std::vector<uint256> txOrder;

    for (auto const& jtx : j["txs"])
    {
        std::pair<Blob, bool> txBlob = strUnHex (jtx.asString ());
        require (txBlob.second, "Error decoding tx");

        Serializer ser (txBlob.first);
        SerializerIterator sit (ser);
        SerializedTransaction stx (sit);

        auto txID = stx.getTransactionID();
        require (txSet->addItem (SHAMapItem (txID, ser), true, true),
                 "Error adding transaction");
        txOrder.push_back (txID);
    }
    return std::make_tuple (ledger, txSet, txOrder);
}