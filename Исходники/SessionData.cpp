Error initialize()
{
   using boost::bind;
   using namespace session::module_context;
   ExecBlock initBlock ;
   initBlock.addFunctions()
      (data::viewer::initialize)
      (bind(sourceModuleRFile, "SessionDataImport.R"))
      (bind(sourceModuleRFile, "SessionDataImportV2.R"));

   return initBlock.execute();
}