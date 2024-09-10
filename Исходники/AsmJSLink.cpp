static bool
DynamicallyLinkModule(JSContext *cx, CallArgs args, AsmJSModule &module)
{
    if (module.isLinked())
        return LinkFail(cx, "As a temporary limitation, modules cannot be linked more than "
                            "once. This limitation should be removed in a future release. To "
                            "work around this, compile a second module (e.g., using the "
                            "Function constructor).");

    RootedValue globalVal(cx, UndefinedValue());
    if (args.length() > 0)
        globalVal = args[0];

    RootedValue importVal(cx, UndefinedValue());
    if (args.length() > 1)
        importVal = args[1];

    RootedValue bufferVal(cx, UndefinedValue());
    if (args.length() > 2)
        bufferVal = args[2];

    Rooted<ArrayBufferObject*> heap(cx);
    if (module.hasArrayView()) {
        if (!IsTypedArrayBuffer(bufferVal))
            return LinkFail(cx, "bad ArrayBuffer argument");

        heap = &bufferVal.toObject().as<ArrayBufferObject>();

        if (!IsPowerOfTwo(heap->byteLength()) || heap->byteLength() < AsmJSAllocationGranularity)
            return LinkFail(cx, "ArrayBuffer byteLength must be a power of two greater than or equal to 4096");

        if (!ArrayBufferObject::prepareForAsmJS(cx, heap))
            return LinkFail(cx, "Unable to prepare ArrayBuffer for asm.js use");

        module.patchHeapAccesses(heap, cx);
    }

    AutoObjectVector ffis(cx);
    if (!ffis.resize(module.numFFIs()))
        return false;

    for (unsigned i = 0; i < module.numGlobals(); i++) {
        AsmJSModule::Global &global = module.global(i);
        switch (global.which()) {
          case AsmJSModule::Global::Variable:
            if (!ValidateGlobalVariable(cx, module, global, importVal))
                return false;
            break;
          case AsmJSModule::Global::FFI:
            if (!ValidateFFI(cx, global, importVal, &ffis))
                return false;
            break;
          case AsmJSModule::Global::ArrayView:
            if (!ValidateArrayView(cx, global, globalVal, bufferVal))
                return false;
            break;
          case AsmJSModule::Global::MathBuiltin:
            if (!ValidateMathBuiltin(cx, global, globalVal))
                return false;
            break;
          case AsmJSModule::Global::Constant:
            if (!ValidateGlobalConstant(cx, global, globalVal))
                return false;
            break;
        }
    }

    for (unsigned i = 0; i < module.numExits(); i++)
        module.exitIndexToGlobalDatum(i).fun = &ffis[module.exit(i).ffiIndex()]->as<JSFunction>();

    module.setIsLinked(heap);
    return true;
}