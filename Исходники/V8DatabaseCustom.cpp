v8::Handle<v8::Value> V8Database::transactionCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.Database.transaction()");
    return createTransaction(args, false);
}