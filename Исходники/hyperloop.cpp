/**
 * return a new global context initialized with Hyperloop global objects
 */
EXPORTAPI JSGlobalContextRef HyperloopNewGlobalContext()
{
    auto ctx = JSGlobalContextCreate(nullptr);
    InitializeContext(ctx);
    return ctx;
}