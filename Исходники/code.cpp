void CodeInfo::construct(JSContext* cx, JS::CallArgs args) {
    uassert(ErrorCodes::BadValue,
            "Code needs 0, 1 or 2 arguments",
            args.length() == 0 || args.length() == 1 || args.length() == 2);
    auto scope = getScope(cx);

    JS::RootedObject thisv(cx);

    scope->getProto<CodeInfo>().newObject(&thisv);
    ObjectWrapper o(cx, thisv);

    if (args.length() == 0) {
        o.setString(InternedString::code, "");
    } else if (args.length() == 1) {
        JS::HandleValue codeArg = args.get(0);
        if (!codeArg.isString())
            uasserted(ErrorCodes::BadValue, "code must be a string");

        o.setValue(InternedString::code, codeArg);
    } else {
        if (!args.get(0).isString())
            uasserted(ErrorCodes::BadValue, "code must be a string");
        if (!args.get(1).isObject())
            uasserted(ErrorCodes::BadValue, "scope must be an object");

        o.setValue(InternedString::code, args.get(0));
        o.setValue(InternedString::scope, args.get(1));
    }

    args.rval().setObjectOrNull(thisv);
}