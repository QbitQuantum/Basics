/*
 * SetScriptHints(fun, flags): Sets various internal hints to the ion
 * compiler for use when compiling |fun| or calls to |fun|.  Flags
 * should be a dictionary object.
 *
 * The function |fun| should be a self-hosted function (in particular,
 * it *must* be a JS function).
 *
 * Possible flags:
 * - |cloneAtCallsite: true| will hint that |fun| should be cloned
 *   each callsite to improve TI resolution.  This is important for
 *   higher-order functions like |Array.map|.
 */
static JSBool
intrinsic_SetScriptHints(JSContext *cx, unsigned argc, Value *vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);
    JS_ASSERT(args.length() >= 2);
    JS_ASSERT(args[0].isObject() && args[0].toObject().isFunction());
    JS_ASSERT(args[1].isObject());

    RootedFunction fun(cx, args[0].toObject().toFunction());
    RootedScript funScript(cx, fun->nonLazyScript());
    RootedObject flags(cx, &args[1].toObject());

    RootedId id(cx);
    RootedValue propv(cx);

    id = AtomToId(Atomize(cx, "cloneAtCallsite", strlen("cloneAtCallsite")));
    if (!JSObject::getGeneric(cx, flags, flags, id, &propv))
        return false;
    if (ToBoolean(propv))
        funScript->shouldCloneAtCallsite = true;

    return true;
}