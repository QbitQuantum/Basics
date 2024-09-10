    void BreakpointsContextTest(JsRuntimeHandle runtime)
    {
        JsContextRef context = JS_INVALID_REFERENCE;
        REQUIRE(JsGetCurrentContext(&context) == JsNoError);

        // Verify no errors with a context set
        JsValueRef scriptsArray = JS_INVALID_REFERENCE;
        REQUIRE(JsDiagGetScripts(&scriptsArray) == JsNoError);

        // Verify the APIs return an error when no current context set
        JsSetCurrentContext(nullptr);
        CHECK(JsDiagGetScripts(&scriptsArray) == JsErrorNoCurrentContext);

        JsValueRef breakpoint = JS_INVALID_REFERENCE;
        CHECK(JsDiagSetBreakpoint(0, 0, 0, &breakpoint) == JsErrorNoCurrentContext);

        CHECK(JsDiagRemoveBreakpoint(0) == JsErrorNoCurrentContext);
    }