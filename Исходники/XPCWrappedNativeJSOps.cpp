bool
XPC_WN_CallMethod(JSContext* cx, unsigned argc, Value* vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    MOZ_ASSERT(JS_TypeOfValue(cx, args.calleev()) == JSTYPE_FUNCTION, "bad function");
    RootedObject funobj(cx, &args.callee());

    RootedObject obj(cx, JS_THIS_OBJECT(cx, vp));
    if (!obj)
        return false;

    obj = FixUpThisIfBroken(obj, funobj);
    XPCCallContext ccx(cx, obj, funobj, JSID_VOIDHANDLE, args.length(),
                       args.array(), vp);
    XPCWrappedNative* wrapper = ccx.GetWrapper();
    THROW_AND_RETURN_IF_BAD_WRAPPER(cx, wrapper);

    RefPtr<XPCNativeInterface> iface;
    XPCNativeMember*    member;

    if (!XPCNativeMember::GetCallInfo(funobj, &iface, &member))
        return Throw(NS_ERROR_XPC_CANT_GET_METHOD_INFO, cx);
    ccx.SetCallInfo(iface, member, false);
    return XPCWrappedNative::CallMethod(ccx);
}