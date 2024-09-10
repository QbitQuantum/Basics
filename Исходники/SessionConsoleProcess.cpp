Error initialize()
{
    // install rpc methods
    using boost::bind;
    using namespace module_context;
    ExecBlock initBlock ;
    initBlock.addFunctions()
    (bind(registerRpcMethod, "process_prepare", procInit))
    (bind(registerRpcMethod, "process_start", procStart))
    (bind(registerRpcMethod, "process_interrupt", procInterrupt));

    return initBlock.execute();
}