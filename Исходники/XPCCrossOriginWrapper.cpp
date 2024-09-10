JSBool
WrapObject(JSContext *cx, JSObject *parent, jsval *vp, XPCWrappedNative* wn)
{
  NS_ASSERTION(XPCPerThreadData::IsMainThread(cx),
               "Can't do this off the main thread!");

  // Our argument should be a wrapped native object, but the caller may have
  // passed it in as an optimization.
  JSObject *wrappedObj;
  if (JSVAL_IS_PRIMITIVE(*vp) ||
      !(wrappedObj = JSVAL_TO_OBJECT(*vp)) ||
      wrappedObj->getClass() == &XOWClass) {
    return JS_TRUE;
  }

  if (!wn &&
      !(wn = XPCWrappedNative::GetAndMorphWrappedNativeOfJSObject(cx, wrappedObj))) {
    return JS_TRUE;
  }

  CheckWindow(wn);

  // The parent must be the inner global object for its scope.
  parent = JS_GetGlobalForObject(cx, parent);
  OBJ_TO_INNER_OBJECT(cx, parent);
  if (!parent) {
    return JS_FALSE;
  }

  XPCWrappedNativeWithXOW *wnxow = nsnull;
  if (wn->NeedsXOW()) {
    JSObject *innerWrappedObj = wrappedObj;
    OBJ_TO_INNER_OBJECT(cx, innerWrappedObj);
    if (!innerWrappedObj) {
      return JS_FALSE;
    }

    if (innerWrappedObj == parent) {
      wnxow = static_cast<XPCWrappedNativeWithXOW *>(wn);
      JSObject *xow = wnxow->GetXOW();
      if (xow) {
        *vp = OBJECT_TO_JSVAL(xow);
        return JS_TRUE;
      }
    }
  }

  XPCWrappedNative *parentwn =
    XPCWrappedNative::GetWrappedNativeOfJSObject(cx, parent);
  XPCWrappedNativeScope *parentScope;
  if (NS_LIKELY(parentwn)) {
    parentScope = parentwn->GetScope();
  } else {
    parentScope = XPCWrappedNativeScope::FindInJSObjectScope(cx, parent);
  }

  JSObject *outerObj = nsnull;
  WrappedNative2WrapperMap *map = parentScope->GetWrapperMap();

  outerObj = map->Find(wrappedObj);
  if (outerObj) {
    NS_ASSERTION(outerObj->getClass() == &XOWClass,
                 "What crazy object are we getting here?");
    *vp = OBJECT_TO_JSVAL(outerObj);

    if (wnxow) {
      // NB: wnxow->GetXOW() must have returned false.
      SetFlags(cx, outerObj, AddFlags(GetFlags(cx, outerObj), FLAG_IS_CACHED));
      wnxow->SetXOW(outerObj);
    }

    return JS_TRUE;
  }

  outerObj = JS_NewObjectWithGivenProto(cx, js::Jsvalify(&XOWClass), nsnull,
                                        parent);
  if (!outerObj) {
    return JS_FALSE;
  }

  jsval flags = INT_TO_JSVAL(wnxow ? FLAG_IS_CACHED : 0);
  if (!JS_SetReservedSlot(cx, outerObj, sWrappedObjSlot, *vp) ||
      !JS_SetReservedSlot(cx, outerObj, sFlagsSlot, flags) ||
      !JS_SetReservedSlot(cx, outerObj, XPC_XOW_ScopeSlot,
                          PRIVATE_TO_JSVAL(parentScope))) {
    return JS_FALSE;
  }

  *vp = OBJECT_TO_JSVAL(outerObj);

  map->Add(wn->GetScope()->GetWrapperMap(), wrappedObj, outerObj);
  if(wnxow) {
    wnxow->SetXOW(outerObj);
  }

  return JS_TRUE;
}