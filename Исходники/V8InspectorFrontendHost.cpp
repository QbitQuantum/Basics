static v8::Handle<v8::Value> closeWindowCallback(const v8::Arguments& args)
{
    InspectorFrontendHost* imp = V8InspectorFrontendHost::toNative(args.Holder());
    imp->closeWindow();
    return v8Undefined();
}