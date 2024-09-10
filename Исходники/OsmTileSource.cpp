void
OsmTileSource::cancelTileRequest(const OsmIndex &index)
{
    OsmIndexSet::const_iterator i = _pendingRequests.find(index);
    if (i == _pendingRequests.end())
        return; // it's not a pending request
    _pendingRequests.erase(i);
    for (OsmReplyMap::Iterator i=_pendingReplies.begin();
         i != _pendingReplies.end(); )
    {
        if (i.value() == index) {
            QNetworkReply *reply = i.key();
            _pendingReplies.remove(reply);
            reply->abort();
            break;
        } else {
            ++i;
        }
    }
    
}