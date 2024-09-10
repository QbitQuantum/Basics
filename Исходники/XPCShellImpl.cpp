static bool
SimulateActivityCallback(JSContext* cx, unsigned argc, jsval* vp)
{
    // Sanity-check args.
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (args.length() != 1 || !args[0].isBoolean()) {
        JS_ReportError(cx, "Wrong number of arguments");
        return false;
    }
    xpc::SimulateActivityCallback(args[0].toBoolean());
    return true;
}