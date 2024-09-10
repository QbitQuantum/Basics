/*
 * normalize process parameters (Offset-->Pointer)
 *
 * @implemented
 */
PRTL_USER_PROCESS_PARAMETERS NTAPI
RtlNormalizeProcessParams(PRTL_USER_PROCESS_PARAMETERS Params)
{
   if (Params && !(Params->Flags & RTL_USER_PROCESS_PARAMETERS_NORMALIZED))
     {
	NORMALIZE(Params->CurrentDirectory.DosPath.Buffer, Params);
	NORMALIZE(Params->DllPath.Buffer, Params);
	NORMALIZE(Params->ImagePathName.Buffer, Params);
	NORMALIZE(Params->CommandLine.Buffer, Params);
	NORMALIZE(Params->WindowTitle.Buffer, Params);
	NORMALIZE(Params->DesktopInfo.Buffer, Params);
	NORMALIZE(Params->ShellInfo.Buffer, Params);
	NORMALIZE(Params->RuntimeData.Buffer, Params);

	Params->Flags |= RTL_USER_PROCESS_PARAMETERS_NORMALIZED;
     }

   return Params;
}