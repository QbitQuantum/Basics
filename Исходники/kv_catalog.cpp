Status KVCatalog::renameCollection(OperationContext* opCtx,
                                   StringData fromNS,
                                   StringData toNS,
                                   bool stayTemp) {
    RecordId loc;
    BSONObj old = _findEntry(opCtx, fromNS, &loc).getOwned();
    {
        BSONObjBuilder b;

        b.append("ns", toNS);

        BSONCollectionCatalogEntry::MetaData md;
        md.parse(old["md"].Obj());
        md.rename(toNS);
        if (!stayTemp)
            md.options.temp = false;
        b.append("md", md.toBSON());

        b.appendElementsUnique(old);

        BSONObj obj = b.obj();
        Status status = _rs->updateRecord(opCtx, loc, obj.objdata(), obj.objsize());
        fassert(28522, status.isOK());
    }

    stdx::lock_guard<stdx::mutex> lk(_identsLock);
    const NSToIdentMap::iterator fromIt = _idents.find(fromNS.toString());
    invariant(fromIt != _idents.end());

    opCtx->recoveryUnit()->registerChange(new RemoveIdentChange(this, fromNS, fromIt->second));
    opCtx->recoveryUnit()->registerChange(new AddIdentChange(this, toNS));

    _idents.erase(fromIt);
    _idents[toNS.toString()] = Entry(old["ident"].String(), loc);

    return Status::OK();
}