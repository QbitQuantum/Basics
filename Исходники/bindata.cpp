void BinDataInfo::Functions::MD5::call(JSContext* cx, JS::CallArgs args) {
    if (args.length() != 1)
        uasserted(ErrorCodes::BadValue, "MD5 needs 1 argument");

    auto arg = args.get(0);
    auto str = ValueWriter(cx, arg).toString();

    if (str.length() != 32)
        uasserted(ErrorCodes::BadValue, "MD5 string must have 32 characters");

    hexToBinData(cx, MD5Type, arg, args.rval());
}