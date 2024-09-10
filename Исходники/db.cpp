void DBInfo::construct(JSContext* cx, JS::CallArgs args) {
    auto scope = getScope(cx);

    if (args.length() != 2)
        uasserted(ErrorCodes::BadValue, "db constructor requires 2 arguments");

    for (unsigned i = 0; i < args.length(); ++i) {
        uassert(ErrorCodes::BadValue,
                "db initializer called with undefined argument",
                !args.get(i).isUndefined());
    }

    JS::RootedObject thisv(cx);
    scope->getProto<DBInfo>().newObject(&thisv);
    ObjectWrapper o(cx, thisv);

    o.setValue(InternedString::_mongol, args.get(0));
    o.setValue(InternedString::_name, args.get(1));

    std::string dbName = ValueWriter(cx, args.get(1)).toString();

    if (!NamespaceString::validDBName(dbName))
        uasserted(ErrorCodes::BadValue,
                  str::stream() << "[" << dbName << "] is not a valid database name");

    args.rval().setObjectOrNull(thisv);
}