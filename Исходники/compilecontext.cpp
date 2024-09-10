bool CompileContext::loadClass(const String& classname)
{
   String lowercasename = classname;
   lowercasename.toLower();

   ClassMap::iterator it = mClasses.find(lowercasename);
   if ( it == mClasses.end() )
   {
      try
      {
         ASTRoot& root = mCompiler.load(classname);
         std::vector<ASTClass*> classes;
         root.collectClasses(classes);
         auto append = [this](ASTClass* pclass) { addClass(pclass); };
         std::for_each(classes.begin(), classes.end(), append);
      }
      catch ( FileNotFoundException* )
      {
         return false;
      }
   }

   return true;
}