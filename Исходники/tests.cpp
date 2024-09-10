bool JSAPITest::init()
{
    rt = createRuntime();
    if (!rt)
        return false;
    cx = createContext();
    if (!cx)
        return false;
#ifdef JS_GC_ZEAL
    JS_SetGCZeal(cx, 0, 0);
#endif
    JS_BeginRequest(cx);
    js::RootedObject global(cx, createGlobal());
    if (!global)
        return false;
    oldCompartment = JS_EnterCompartment(cx, global);
    return oldCompartment != NULL;
}