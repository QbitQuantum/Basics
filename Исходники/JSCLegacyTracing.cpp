static JSValueRef nativeTraceBeginLegacy(
    JSContextRef ctx,
    JSObjectRef function,
    JSObjectRef thisObject,
    size_t argumentCount,
    const JSValueRef arguments[],
    JSValueRef* exception) {
  if (FBSYSTRACE_LIKELY(argumentCount >= 1)) {
    uint64_t tag = facebook::react::tracingTagFromJSValue(ctx, arguments[0], exception);
    if (!fbsystrace_is_tracing(tag)) {
      return JSValueMakeUndefined(ctx);
    }
  }

  JSStringRef title = JSStringCreateWithUTF8CString(ENABLED_FBSYSTRACE_PROFILE_NAME);
  #if WITH_REACT_INTERNAL_SETTINGS
  JSStartProfiling(ctx, title, true);
  #else
  JSStartProfiling(ctx, title);
  #endif
  JSStringRelease(title);

  return JSValueMakeUndefined(ctx);
}