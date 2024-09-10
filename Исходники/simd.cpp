bool
X4TypeDescr::call(JSContext *cx, unsigned argc, Value *vp)
{
    CallArgs args = CallArgsFromVp(argc, vp);
    const unsigned LANES = 4;

    if (args.length() < LANES) {
        JS_ReportErrorNumber(cx, js_GetErrorMessage, nullptr, JSMSG_MORE_ARGS_NEEDED,
                             args.callee().getClass()->name, "3", "s");
        return false;
    }

    double values[LANES];
    for (unsigned i = 0; i < LANES; i++) {
        if (!ToNumber(cx, args[i], &values[i]))
            return false;
    }

    Rooted<X4TypeDescr*> descr(cx, &args.callee().as<X4TypeDescr>());
    Rooted<TypedObject*> result(cx, TypedObject::createZeroed(cx, descr, 0));
    if (!result)
        return false;

    MOZ_ASSERT(!result->owner().isNeutered());
    switch (descr->type()) {
#define STORE_LANES(_constant, _type, _name)                                  \
      case _constant:                                                         \
      {                                                                       \
        _type *mem = reinterpret_cast<_type*>(result->typedMem());            \
        for (unsigned i = 0; i < LANES; i++)                                  \
            mem[i] = ConvertScalar<_type>(values[i]);                         \
        break;                                                                \
      }
      JS_FOR_EACH_X4_TYPE_REPR(STORE_LANES)
#undef STORE_LANES
    }
    args.rval().setObject(*result);
    return true;
}