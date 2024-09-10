bool
JetpackChild::RecvEvalScript(const nsString& code)
{
  JSAutoRequest request(mCx);

  JSObject *global = JS_GetGlobalObject(mCx);
  JSAutoEnterCompartment ac;
  if (!ac.enter(mCx, global))
    return false;

  jsval ignored;
  (void) JS_EvaluateUCScript(mCx, global, code.get(),
                             code.Length(), "", 1, &ignored);
  return true;
}