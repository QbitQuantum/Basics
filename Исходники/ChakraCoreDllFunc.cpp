void DummyJSRTCall() {
    JsRuntimeHandle *runtime;
    JsRuntimeAttributes attr;
    JsCreateRuntime(attr, nullptr, runtime);
}