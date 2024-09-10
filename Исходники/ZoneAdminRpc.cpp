bool ZoneAdminRpcMethod::buildOutputFiles(const UtlString&     command,
                         UtlString&      stdoutfn,
                         UtlString&      stderrfn
                        )
{
   bool result = true;
   stdoutfn.remove(0);
   stderrfn.remove(0);
   stdoutfn.append(ZoneAdminGenerate_cmd);
   stderrfn.append(ZoneAdminGenerate_cmd);
   stderrfn.append(ZoneAdminStdErr_filetype);
   stdoutfn.append(ZoneAdminStdOut_filetype);

   return result;
}