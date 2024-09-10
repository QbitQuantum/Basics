static JSBool
XPC_SOW_RewrapValue(JSContext *cx, JSObject *wrapperObj, jsval *vp)
{
  jsval v = *vp;
  if (JSVAL_IS_PRIMITIVE(v)) {
    return JS_TRUE;
  }

  JSObject *obj = JSVAL_TO_OBJECT(v);

  if (JS_ObjectIsFunction(cx, obj)) {
    // NB: The JS_ValueToFunction call is guaranteed to succeed.
    JSNative native = JS_GetFunctionNative(cx, JS_ValueToFunction(cx, v));

    // This is really tricky! We need to unwrap this when calling native
    // functions to preserve their assumptions, but *not* when calling
    // scripted functions, since they expect 'this' to be wrapped.
    if (!native) {
     return JS_TRUE;
    }

    if (native == XPC_SOW_FunctionWrapper) {
      // If this is a system function wrapper, make sure its ours, otherwise,
      // its prototype could come from the wrong scope.
      if (wrapperObj->getProto() == obj->getParent()) {
        return JS_TRUE;
      }

      // It isn't ours, rewrap the wrapped function.
      if (!JS_GetReservedSlot(cx, obj, eWrappedFunctionSlot, &v)) {
        return JS_FALSE;
      }
      obj = JSVAL_TO_OBJECT(v);
    }

    return XPC_SOW_WrapFunction(cx, wrapperObj, obj, vp);
  }

  if (obj->getClass() == &SOWClass) {
    // We are extra careful about content-polluted wrappers here. I don't know
    // if it's possible to reach them through objects that we wrap, but figuring
    // that out is more expensive (and harder) than simply checking and
    // rewrapping here.
    if (wrapperObj->getParent() == obj->getParent()) {
      // Already wrapped.
      return JS_TRUE;
    }

    obj = GetWrappedObject(cx, obj);
    if (!obj) {
      // XXX Can this happen?
      *vp = JSVAL_NULL;
      return JS_TRUE;
    }
    v = *vp = OBJECT_TO_JSVAL(obj);
  }

  return WrapObject(cx, wrapperObj->getParent(), v, vp);
}