Nan::NAN_METHOD_RETURN_TYPE TxnWrap::putCommon(Nan::NAN_METHOD_ARGS_TYPE info, void (*fillFunc)(Nan::NAN_METHOD_ARGS_TYPE info, MDB_val&), void (*freeData)(MDB_val&)) {
    Nan::HandleScope scope;

    TxnWrap *tw = Nan::ObjectWrap::Unwrap<TxnWrap>(info.This());
    DbiWrap *dw = Nan::ObjectWrap::Unwrap<DbiWrap>(info[0]->ToObject());

    if (!tw->txn) {
        return Nan::ThrowError("The transaction is already closed.");
    }

    int flags = 0;
    MDB_val key, data;

    void (*freeKey)(MDB_val&) = argToKey(info[1], key, dw->keyIsUint32);
    if (!freeKey) {
        return;
    }

    fillFunc(info, data);

    int rc = mdb_put(tw->txn, dw->dbi, &key, &data, flags);
    freeKey(key);
    freeData(data);

    if (rc != 0) {
        return Nan::ThrowError(mdb_strerror(rc));
    }

    return;
}