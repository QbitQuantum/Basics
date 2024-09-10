static JSValueRef nativeProfilerStart(
    JSContextRef ctx,
    JSObjectRef function,
    JSObjectRef thisObject,
    size_t argumentCount,
    const JSValueRef arguments[],
    JSValueRef* exception) {
  if (argumentCount < 1) {
    if (exception) {
      *exception = facebook::react::makeJSCException(
        ctx,
        "nativeProfilerStart: requires at least 1 argument");
    }
    return JSValueMakeUndefined(ctx);
  }

  JSStringRef title = JSValueToStringCopy(ctx, arguments[0], exception);
  JSStartProfiling(ctx, title);
  JSStringRelease(title);
  return JSValueMakeUndefined(ctx);
}