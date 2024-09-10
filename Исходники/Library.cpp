bool
Library::Declare(JSContext* cx, unsigned argc, Value* vp)
{
  CallArgs args = CallArgsFromVp(argc, vp);
  RootedObject obj(cx, JS_THIS_OBJECT(cx, vp));
  if (!obj)
    return false;
  if (!IsLibrary(obj)) {
    JS_ReportErrorASCII(cx, "not a library");
    return false;
  }

  PRLibrary* library = GetLibrary(obj);
  if (!library) {
    JS_ReportErrorASCII(cx, "library not open");
    return false;
  }

  // We allow two API variants:
  // 1) library.declare(name, abi, returnType, argType1, ...)
  //    declares a function with the given properties, and resolves the symbol
  //    address in the library.
  // 2) library.declare(name, type)
  //    declares a symbol of 'type', and resolves it. The object that comes
  //    back will be of type 'type', and will point into the symbol data.
  //    This data will be both readable and writable via the usual CData
  //    accessors. If 'type' is a PointerType to a FunctionType, the result will
  //    be a function pointer, as with 1).
  if (args.length() < 2) {
    JS_ReportErrorASCII(cx, "declare requires at least two arguments");
    return false;
  }

  if (!args[0].isString()) {
    JS_ReportErrorASCII(cx, "first argument must be a string");
    return false;
  }

  RootedObject fnObj(cx, nullptr);
  RootedObject typeObj(cx);
  bool isFunction = args.length() > 2;
  if (isFunction) {
    // Case 1).
    // Create a FunctionType representing the function.
    fnObj = FunctionType::CreateInternal(cx, args[1], args[2],
                                         HandleValueArray::subarray(args, 3, args.length() - 3));
    if (!fnObj)
      return false;

    // Make a function pointer type.
    typeObj = PointerType::CreateInternal(cx, fnObj);
    if (!typeObj)
      return false;
  } else {
    // Case 2).
    if (args[1].isPrimitive() ||
        !CType::IsCType(args[1].toObjectOrNull()) ||
        !CType::IsSizeDefined(args[1].toObjectOrNull())) {
      JS_ReportErrorASCII(cx, "second argument must be a type of defined size");
      return false;
    }

    typeObj = args[1].toObjectOrNull();
    if (CType::GetTypeCode(typeObj) == TYPE_pointer) {
      fnObj = PointerType::GetBaseType(typeObj);
      isFunction = fnObj && CType::GetTypeCode(fnObj) == TYPE_function;
    }
  }

  void* data;
  PRFuncPtr fnptr;
  RootedString nameStr(cx, args[0].toString());
  AutoCString symbol;
  if (isFunction) {
    // Build the symbol, with mangling if necessary.
    FunctionType::BuildSymbolName(nameStr, fnObj, symbol);
    AppendString(symbol, "\0");

    // Look up the function symbol.
    fnptr = PR_FindFunctionSymbol(library, symbol.begin());
    if (!fnptr) {
      JS_ReportErrorASCII(cx, "couldn't find function symbol in library");
      return false;
    }
    data = &fnptr;

  } else {
    // 'typeObj' is another data type. Look up the data symbol.
    AppendString(symbol, nameStr);
    AppendString(symbol, "\0");

    data = PR_FindSymbol(library, symbol.begin());
    if (!data) {
      JS_ReportErrorASCII(cx, "couldn't find symbol in library");
      return false;
    }
  }

  RootedObject result(cx, CData::Create(cx, typeObj, obj, data, isFunction));
  if (!result)
    return false;

  if (isFunction)
    JS_SetReservedSlot(result, SLOT_FUNNAME, StringValue(nameStr));

  args.rval().setObject(*result);

  // Seal the CData object, to prevent modification of the function pointer.
  // This permanently associates this object with the library, and avoids
  // having to do things like reset SLOT_REFERENT when someone tries to
  // change the pointer value.
  // XXX This will need to change when bug 541212 is fixed -- CData::ValueSetter
  // could be called on a sealed object.
  if (isFunction && !JS_FreezeObject(cx, result))
    return false;

  return true;
}