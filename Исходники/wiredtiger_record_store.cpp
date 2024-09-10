void WiredTigerRecordStore::deleteRecord(OperationContext* txn, const RecordId& loc) {
    WiredTigerCursor cursor(_uri, _tableId, true, txn);
    cursor.assertInActiveTxn();
    WT_CURSOR* c = cursor.get();
    c->set_key(c, _makeKey(loc));
    int ret = WT_OP_CHECK(c->search(c));
    invariantWTOK(ret);

    WT_ITEM old_value;
    ret = c->get_value(c, &old_value);
    invariantWTOK(ret);

    int old_length = old_value.size;

    ret = WT_OP_CHECK(c->remove(c));
    invariantWTOK(ret);

    _changeNumRecords(txn, -1);
    _increaseDataSize(txn, -old_length);
}