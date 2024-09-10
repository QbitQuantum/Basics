void SessionInfo::Functions::setTxnState::call(JSContext* cx, JS::CallArgs args) {
    auto holder = getHolder(args);
    invariant(holder);
    uassert(ErrorCodes::BadValue, "setTxnState takes 1 argument", args.length() == 1);

    auto arg = args.get(0);
    holder->txnState = transactionStateEnum(ValueWriter(cx, arg).toString().c_str());
    args.rval().setUndefined();
}