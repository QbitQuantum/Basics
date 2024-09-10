std::string  CompilerFactory::findNativeTool(const std::string &profile_tool_name,const Argv & _args) 
{
  FUNCTION_TRACE;
  Argv arg(_args);
  bool tool_found=false;
  std::string file;
  struct stat info_me;
  std::string exe_param=System::appendExecSuffix(arg[0]);
  std::string appli=application_path(exe_param);
  DEBUG3("exe_param %s -> %s\n",exe_param.c_str(),appli.c_str());
  if (profile_tool_name.empty())
  {
     file=appli;
  }
  else
  {
     if (stat(appli.c_str(),&info_me)!=0)
        FATAL2("Could not get information from %s\n",appli.c_str());
     exe_param=System::appendExecSuffix(profile_tool_name);
     int index=-1;
     file=application_path(exe_param);
     while (!file.empty())
     {
        struct stat info;
        DEBUG2("Tool: %s\n",file.c_str());
        char file_abs[MAX_PATH];
        if (realPath(file.c_str(),file_abs)!=NULL)
        {
           DEBUG2("Tool abs: %s\n",file_abs);
           if (stat(file_abs,&info)==0)
           {
              if ( ! (info.st_ctime==info_me.st_ctime
                       && info.st_size==info_me.st_size) )
              { // tool found
                 tool_found=true;
                 DEBUG2("Tool found: %s\n",file.c_str());
                 break;
              }
              else
              { // suppress path entry
#if SUPPRESS_PATH_ENTRY
                 suppressPathEntry(file.c_str());
#endif
                 setenv("COVERAGESCANNER_ARGS","",1);
              }
           }
        }
        index++;
        file=findFileInPath(exe_param,index);
     } 

     if (!tool_found)
        FATAL2("Could not find application: %s\n",exe_param.c_str());
  }
  return file;
}