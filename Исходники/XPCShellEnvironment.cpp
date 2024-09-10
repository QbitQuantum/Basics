bool
XPCShellEnvironment::EvaluateString(const nsString& aString,
                                    nsString* aResult)
{
  AutoEntryScript aes(GetGlobalObject(),
                      "ipc XPCShellEnvironment::EvaluateString");
  JSContext* cx = aes.cx();

  JS::CompileOptions options(cx);
  options.setFileAndLine("typein", 0);
  JS::Rooted<JSScript*> script(cx);
  if (!JS_CompileUCScript(cx, aString.get(), aString.Length(), options,
                          &script))
  {
     return false;
  }

  if (aResult) {
      aResult->Truncate();
  }

  JS::Rooted<JS::Value> result(cx);
  bool ok = JS_ExecuteScript(cx, script, &result);
  if (ok && !result.isUndefined()) {
      JS::WarningReporter old = JS::SetWarningReporter(cx, nullptr);
      JSString* str = JS::ToString(cx, result);
      nsAutoJSString autoStr;
      if (str)
          autoStr.init(cx, str);
      JS::SetWarningReporter(cx, old);

      if (!autoStr.IsEmpty() && aResult) {
          aResult->Assign(autoStr);
      }
  }

  return true;
}