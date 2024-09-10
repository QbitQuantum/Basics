void TimestampInfo::construct(JSContext* cx, JS::CallArgs args) {
    auto scope = getScope(cx);

    JS::RootedObject thisv(cx);
    scope->getProto<TimestampInfo>().newObject(&thisv);
    ObjectWrapper o(cx, thisv);

    if (args.length() == 0) {
        o.setNumber(InternedString::t, 0);
        o.setNumber(InternedString::i, 0);
    } else if (args.length() == 2) {
        o.setNumber(InternedString::t, getTimestampArg(cx, args, 0, "Timestamp time (seconds)"));
        o.setNumber(InternedString::i, getTimestampArg(cx, args, 1, "Timestamp increment"));
    } else {
        uasserted(ErrorCodes::BadValue, "Timestamp needs 0 or 2 arguments");
    }

    args.rval().setObjectOrNull(thisv);
}