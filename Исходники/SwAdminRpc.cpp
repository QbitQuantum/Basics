bool SwAdminRpcMethod::buildOutputFiles(const UtlString&     command,
                         UtlString&      stdoutfn,
                         UtlString&      stderrfn
                        )
{
   bool result = true;
   stdoutfn.remove(0);
   stderrfn.remove(0);
   if ( command.compareTo(SwAdminVersion_cmd, UtlString::ignoreCase) == 0)
   {
       stdoutfn.append(SwAdminVersion_cmd);
       stderrfn.append(SwAdminVersion_cmd);
   }
   else
      if ( command.compareTo(SwAdminCheckUpdate_cmd, UtlString::ignoreCase) == 0)
      {
         stdoutfn.append(SwAdminCheckUpdate_cmd);
         stderrfn.append(SwAdminCheckUpdate_cmd);
      }
      else
         if ( command.compareTo(SwAdminUpdate_cmd, UtlString::ignoreCase) == 0)
         {
            stdoutfn.append(SwAdminUpdate_cmd);
            stderrfn.append(SwAdminUpdate_cmd);
         }
         else
            if ( command.compareTo(SwAdminRestart_cmd, UtlString::ignoreCase) == 0)
            {
               stdoutfn.append(SwAdminRestart_cmd);
               stderrfn.append(SwAdminRestart_cmd);
            }
            else
               if ( command.compareTo(SwAdminReboot_cmd, UtlString::ignoreCase) == 0)
               {
                  stdoutfn.append(SwAdminReboot_cmd);
                  stderrfn.append(SwAdminReboot_cmd);
               }
               else
               {
                  return false;
               }

   stderrfn.append(SwAdminStdErr_filetype);
   stdoutfn.append(SwAdminStdOut_filetype);

   return result;
}