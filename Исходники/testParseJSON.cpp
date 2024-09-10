static bool
Censor(JSContext* cx, unsigned argc, JS::Value* vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    MOZ_RELEASE_ASSERT(args.length() == 2);
    MOZ_RELEASE_ASSERT(args[0].isString());
    args.rval().setNull();
    return true;
}