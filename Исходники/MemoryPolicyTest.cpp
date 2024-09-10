    void BasicTest(JsRuntimeAttributes attributes, LPCSTR fileName)
    {
        LPCWSTR script = nullptr;
        REQUIRE(FileLoadHelpers::LoadScriptFromFile(fileName, script) == S_OK);
        REQUIRE(script != nullptr);

        // Create the runtime
        JsRuntimeHandle runtime = JS_INVALID_RUNTIME_HANDLE;
        REQUIRE(JsCreateRuntime(attributes, nullptr, &runtime) == JsNoError);

        // Set memory limit
        REQUIRE(JsSetRuntimeMemoryLimit(runtime, MemoryLimit) == JsNoError);

        size_t memoryLimit;
        size_t memoryUsage;

        REQUIRE(JsGetRuntimeMemoryLimit(runtime, &memoryLimit) == JsNoError);
        CHECK(memoryLimit == MemoryLimit);
        REQUIRE(JsGetRuntimeMemoryUsage(runtime, &memoryUsage) == JsNoError);
        CHECK(memoryUsage < MemoryLimit);

        // Create and initialize the script context
        JsContextRef context = JS_INVALID_RUNTIME_HANDLE;
        REQUIRE(JsCreateContext(runtime, &context) == JsNoError);
        REQUIRE(JsSetCurrentContext(context) == JsNoError);

        // Invoke the script
        REQUIRE(JsRunScript(script, JS_SOURCE_CONTEXT_NONE, _u(""), nullptr) == JsErrorScriptException);

        ValidateOOMException();

        REQUIRE(JsGetRuntimeMemoryLimit(runtime, &memoryLimit) == JsNoError);
        CHECK(memoryLimit == MemoryLimit);
        REQUIRE(JsGetRuntimeMemoryUsage(runtime, &memoryUsage) == JsNoError);
        CHECK(memoryUsage <= MemoryLimit);

        // Destroy the runtime
        REQUIRE(JsSetCurrentContext(JS_INVALID_REFERENCE) == JsNoError);
        REQUIRE(JsCollectGarbage(runtime) == JsNoError);
        REQUIRE(JsDisposeRuntime(runtime) == JsNoError);
    }