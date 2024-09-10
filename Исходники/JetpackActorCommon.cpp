bool
JetpackActorCommon::RecvMessage(JSContext* cx,
                                const nsString& messageName,
                                const nsTArray<Variant>& data,
                                nsTArray<Variant>* results)
{
  if (results)
    results->Clear();

  RecList* list;
  if (!mReceivers.Get(messageName, &list))
    return true;
  nsAutoTArray<jsval, 4> snapshot;
  list->copyTo(snapshot);
  if (!snapshot.Length())
    return true;
  
  nsAutoTArray<jsval, 4> args;
  PRUint32 argc = data.Length() + 1;
  jsval* argv = args.AppendElements(argc);
  if (!argv)
    return false;
  for (PRUint32 i = 0; i < argc; ++i)
    argv[i] = JSVAL_VOID;
  js::AutoArrayRooter argvRooter(cx, argc, argv);

  JSString* msgNameStr =
    JS_NewUCStringCopyN(cx,
                        messageName.get(),
                        messageName.Length());
  if (!msgNameStr)
    return false;
  argv[0] = STRING_TO_JSVAL(msgNameStr);

  for (PRUint32 i = 0; i < data.Length(); ++i)
    if (!jsval_from_Variant(cx, data.ElementAt(i), argv + i + 1))
      return false;

  JSObject* implGlobal = JS_GetGlobalObject(cx);
  js::AutoValueRooter rval(cx);

  for (PRUint32 i = 0; i < snapshot.Length(); ++i) {
    Variant* vp = results ? results->AppendElement() : NULL;
    rval.set(JSVAL_VOID);
    if (!JS_CallFunctionValue(cx, implGlobal, snapshot[i], argc, argv,
                              rval.jsval_addr())) {
      (void) JS_ReportPendingException(cx);
      if (vp)
        *vp = void_t();
    } else if (vp && !jsval_to_Variant(cx, rval.jsval_value(), vp))
      *vp = void_t();
  }

  return true;
}