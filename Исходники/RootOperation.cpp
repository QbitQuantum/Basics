void RootOperationData::sendContents(Bridge & b) const
{
    sendSerialno(b);
    sendRefno(b);
    sendFrom(b);
    sendTo(b);
    sendSeconds(b);
    sendFutureSeconds(b);
    sendArgs(b);
    RootData::sendContents(b);
}