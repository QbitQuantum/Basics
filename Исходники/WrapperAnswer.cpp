bool
WrapperAnswer::AnswerCallOrConstruct(const ObjectId &objId,
                                     const nsTArray<JSParam> &argv,
                                     const bool &construct,
                                     ReturnStatus *rs,
                                     JSVariant *result,
                                     nsTArray<JSParam> *outparams)
{
    AutoSafeJSContext cx;
    JSAutoRequest request(cx);

    // The outparam will be written to the buffer, so it must be set even if
    // the parent won't read it.
    *result = UndefinedVariant();

    RootedObject obj(cx, findObjectById(cx, objId));
    if (!obj)
        return fail(cx, rs);

    JSAutoCompartment comp(cx, obj);

    MOZ_ASSERT(argv.Length() >= 2);

    RootedValue objv(cx);
    if (!fromVariant(cx, argv[0], &objv))
        return fail(cx, rs);

    *result = JSVariant(UndefinedVariant());

    AutoValueVector vals(cx);
    AutoValueVector outobjects(cx);
    for (size_t i = 0; i < argv.Length(); i++) {
        if (argv[i].type() == JSParam::Tvoid_t) {
            // This is an outparam.
            JSCompartment *compartment = js::GetContextCompartment(cx);
            RootedObject global(cx, JS_GetGlobalForCompartmentOrNull(cx, compartment));
            RootedObject obj(cx, xpc::NewOutObject(cx, global));
            if (!obj)
                return fail(cx, rs);
            if (!outobjects.append(ObjectValue(*obj)))
                return fail(cx, rs);
            if (!vals.append(ObjectValue(*obj)))
                return fail(cx, rs);
        } else {
            RootedValue v(cx);
            if (!fromVariant(cx, argv[i].get_JSVariant(), &v))
                return fail(cx, rs);
            if (!vals.append(v))
                return fail(cx, rs);
        }
    }

    RootedValue rval(cx);
    {
        AutoSaveContextOptions asco(cx);
        ContextOptionsRef(cx).setDontReportUncaught(true);

        HandleValueArray args = HandleValueArray::subarray(vals, 2, vals.length() - 2);
        bool success;
        if (construct)
            success = JS::Construct(cx, vals[0], args, &rval);
        else
            success = JS::Call(cx, vals[1], vals[0], args, &rval);
        if (!success)
            return fail(cx, rs);
    }

    if (!toVariant(cx, rval, result))
        return fail(cx, rs);

    // Prefill everything with a dummy jsval.
    for (size_t i = 0; i < outobjects.length(); i++)
        outparams->AppendElement(JSParam(void_t()));

    // Go through each argument that was an outparam, retrieve the "value"
    // field, and add it to a temporary list. We need to do this separately
    // because the outparams vector is not rooted.
    vals.clear();
    for (size_t i = 0; i < outobjects.length(); i++) {
        RootedObject obj(cx, &outobjects[i].toObject());

        RootedValue v(cx);
        bool found;
        if (JS_HasProperty(cx, obj, "value", &found)) {
            if (!JS_GetProperty(cx, obj, "value", &v))
                return fail(cx, rs);
        } else {
            v = UndefinedValue();
        }
        if (!vals.append(v))
            return fail(cx, rs);
    }

    // Copy the outparams. If any outparam is already set to a void_t, we
    // treat this as the outparam never having been set.
    for (size_t i = 0; i < vals.length(); i++) {
        JSVariant variant;
        if (!toVariant(cx, vals[i], &variant))
            return fail(cx, rs);
        outparams->ReplaceElementAt(i, JSParam(variant));
    }

    LOG("%s.call(%s) = %s", ReceiverObj(objId), argv, OutVariant(*result));

    return ok(rs);
}