// synchronously send a string from Node to browser, then return string result from browser to Node
Handle<Value> Window::SendSync(const Arguments& args) {
  HandleScope scope;

  NativeWindow *window = ObjectWrap::Unwrap<NativeWindow> (args.This());

  if (window->GetBrowser()) {
    // find browser's v8 context
    CefRefPtr<CefV8Context> context = window->GetBrowser()->GetMainFrame()->GetV8Context();

    // ensure it's usable and enter
    if (context.get() && context->Enter()) {
      // try to get "appjs.onmessage" function
      CefRefPtr<CefV8Value> appjsObject = context->GetGlobal()->GetValue("appjs");
      CefRefPtr<CefV8Value> callback = appjsObject->GetValue("onmessage");
      if (callback.get()) {

        // convert Node V8 string to Cef V8 string
        CefV8ValueList argsOut;
        argsOut.push_back(CefV8Value::CreateString(V8StringToChar(args[0]->ToString())));

        // execute window.appjs fuction, passing in the string,
        // then convert the return value from a CefValue to a Node V8 string
        Handle<String> ret = CefStringToV8(callback->ExecuteFunction(appjsObject, argsOut)->GetStringValue());

        // exit browser v8 context, return string result to Node caller
        context->Exit();
        return scope.Close(ret);
      }
    }
  }
  // likely error condition
  return scope.Close(Undefined());
}