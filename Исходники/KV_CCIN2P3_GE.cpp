void KV_CCIN2P3_GE::GetBatchSystemParameterList(KVNameValueList& nl)
{
   // Fill the list with all relevant parameters for batch system,
   // set to their default values.
   //
   // Parameters defined here are:
   //   JobTime        [string]
   //   JobMemory      [string]
   //   JobDisk        [string]
   //   MultiJobsMode  [bool]
   //   RunsPerJob     [int]
   //   EMailOnStart   [bool]
   //   EMailOnEnd     [bool]
   //   EMailAddress   [string]

   KVBatchSystem::GetBatchSystemParameterList(nl);
   nl.SetValue("JobTime", fDefJobTime);
   nl.SetValue("JobMemory", fDefJobMem);
   nl.SetValue("JobDisk", fDefJobDisk);
   nl.SetValue("MultiJobsMode", MultiJobsMode());
   nl.SetValue("RunsPerJob", fRunsPerJob);
   nl.SetValue("EMailOnStart", kFALSE);
   nl.SetValue("EMailOnEnd", kFALSE);
   TString email = gSystem->GetFromPipe("email");
   if (email.Index('=') > -1) {
      email.Remove(0, email.Index('=') + 2);
      nl.SetValue("EMailAddress", email);
   }
   else
      nl.SetValue("EMailAddress", "");
}