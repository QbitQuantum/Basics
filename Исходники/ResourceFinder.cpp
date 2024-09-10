 ConstString context2path(Property& config, const ConstString& context ) {
     ConstString cap =
         config.check("capability_directory",Value("app")).asString();
     ConstString path = getPath(root,cap,context,"");
     if (path.length()>1) {
         if (path[path.length()-1]=='/') {
             path = path.substr(0,path.length()-1);
         }
     }
     return path;
 }