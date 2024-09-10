Error initialize()
{
    using boost::bind;
    using namespace session::module_context;
    ExecBlock initBlock ;
    initBlock.addFunctions()
    (bind(registerUriHandler, "/content", handleContentRequest))
    (bind(registerRpcMethod, "remove_content_url", removeContentUrl));
    return initBlock.execute();
}