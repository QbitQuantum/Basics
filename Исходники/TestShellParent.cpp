JSBool
TestShellCommandParent::RunCallback(const nsString& aResponse)
{
  NS_ENSURE_TRUE(*mCallback.ToJSValPtr() != JSVAL_NULL && mCx, JS_FALSE);

  JSAutoRequest ar(mCx);
  NS_ENSURE_TRUE(mCallback.ToJSObject(), JS_FALSE);
  JSAutoCompartment ac(mCx, mCallback.ToJSObject());
  JS::Rooted<JSObject*> global(mCx, JS::CurrentGlobalOrNull(mCx));

  JSString* str = JS_NewUCStringCopyN(mCx, aResponse.get(), aResponse.Length());
  NS_ENSURE_TRUE(str, JS_FALSE);

  JS::Rooted<JS::Value> strVal(mCx, JS::StringValue(str));

  JS::Rooted<JS::Value> rval(mCx);
  JSBool ok = JS_CallFunctionValue(mCx, global, mCallback, 1, strVal.address(),
                                   rval.address());
  NS_ENSURE_TRUE(ok, JS_FALSE);

  return JS_TRUE;
}