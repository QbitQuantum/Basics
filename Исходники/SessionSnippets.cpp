core::Error initialize()
{
   using namespace module_context;
   using boost::bind;
   
   events().afterSessionInitHook.connect(afterSessionInitHook);
   events().onClientInit.connect(onClientInit);
   
   ExecBlock initBlock;
   initBlock.addFunctions()
         (bind(registerRpcMethod, "save_snippets", saveSnippets))
         (bind(registerRpcMethod, "get_snippets", getSnippets));
   
   return initBlock.execute();
}