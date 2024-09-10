v8::Handle<v8::Value> V8DatabaseSync::readTransactionCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.DatabaseSync.readTransaction()");
    return createTransaction(args, true);
}