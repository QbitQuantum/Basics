bool
FieldSetterImpl(JSContext *cx, JS::CallArgs args)
{
  const JS::Value &thisv = args.thisv();
  MOZ_ASSERT(ValueHasISupportsPrivate(thisv));

  JS::Rooted<JSObject*> thisObj(cx, &thisv.toObject());

  // We should be in the compartment of |this|. If we got here via nativeCall,
  // |this| is not same-compartment with |callee|, and it's possible via
  // asymmetric security semantics that |args.calleev()| is actually a security
  // wrapper. In this case, we know we want to do an unsafe unwrap, and
  // InstallXBLField knows how to handle cross-compartment pointers.
  bool installed = false;
  JS::Rooted<JSObject*> callee(cx, js::UncheckedUnwrap(&args.calleev().toObject()));
  JS::Rooted<jsid> id(cx);
  if (!InstallXBLField(cx, callee, thisObj, &id, &installed)) {
    return false;
  }

  if (installed) {
    JS::Rooted<JS::Value> v(cx,
                            args.length() > 0 ? args[0] : JS::UndefinedValue());
    if (!::JS_SetPropertyById(cx, thisObj, id, v.address())) {
      return false;
    }
  }
  args.rval().setUndefined();
  return true;
}