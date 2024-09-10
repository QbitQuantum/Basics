Error initialize()
{
   // install rpc methods
   using boost::bind;
   using namespace module_context;
   ExecBlock initBlock ;
   initBlock.addFunctions()
      (tex::compile_pdf::initialize)
      (bind(registerRpcMethod, "is_tex_installed", isTexInstalled))
      (bind(registerRpcMethod, "get_tex_capabilities", getTexCapabilities))
   ;
  return initBlock.execute();
}