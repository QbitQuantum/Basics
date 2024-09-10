static bool
File(JSContext *cx, unsigned argc, Value *vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);

    if (args.length() == 0) {
        XPCThrower::Throw(NS_ERROR_UNEXPECTED, cx);
        return false;
    }

    nsCOMPtr<nsISupports> native;
    nsresult rv = nsDOMMultipartFile::NewFile(getter_AddRefs(native));
    if (NS_FAILED(rv)) {
        XPCThrower::Throw(rv, cx);
        return false;
    }

    nsCOMPtr<nsIJSNativeInitializer> initializer = do_QueryInterface(native);
    MOZ_ASSERT(initializer);

    rv = initializer->Initialize(nullptr, cx, nullptr, args);
    if (NS_FAILED(rv)) {
        XPCThrower::Throw(rv, cx);
        return false;
    }

    nsXPConnect* xpc = nsXPConnect::XPConnect();
    JSObject* glob = CurrentGlobalOrNull(cx);

    nsCOMPtr<nsIXPConnectJSObjectHolder> holder;
    rv = xpc->WrapNativeToJSVal(cx, glob, native, nullptr,
                                &NS_GET_IID(nsISupports),
                                true, args.rval().address());
    if (NS_FAILED(rv)) {
        XPCThrower::Throw(rv, cx);
        return false;
    }
    return true;
}