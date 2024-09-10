bool
js::intl_patternForSkeleton(JSContext* cx, unsigned argc, Value* vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);
    MOZ_ASSERT(args.length() == 2);
    MOZ_ASSERT(args[0].isString());
    MOZ_ASSERT(args[1].isString());

    JSAutoByteString locale(cx, args[0].toString());
    if (!locale)
        return false;

    AutoStableStringChars skeleton(cx);
    if (!skeleton.initTwoByte(cx, args[1].toString()))
        return false;

    mozilla::Range<const char16_t> skelChars = skeleton.twoByteRange();

    UErrorCode status = U_ZERO_ERROR;
    UDateTimePatternGenerator* gen = udatpg_open(IcuLocale(locale.ptr()), &status);
    if (U_FAILURE(status)) {
        intl::ReportInternalError(cx);
        return false;
    }
    ScopedICUObject<UDateTimePatternGenerator, udatpg_close> toClose(gen);

    JSString* str =
        CallICU(cx, [gen, &skelChars](UChar* chars, uint32_t size, UErrorCode* status) {
            return udatpg_getBestPattern(gen, skelChars.begin().get(), skelChars.length(),
                                         chars, size, status);
        });
    if (!str)
        return false;

    args.rval().setString(str);
    return true;
}