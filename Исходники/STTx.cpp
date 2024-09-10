Json::Value STTx::getJson (int) const
{
    Json::Value ret = STObject::getJson (0);
    ret[jss::hash] = to_string (getTransactionID ());
    return ret;
}