/**
 * FsExecuteFile is	called to execute a	file on	the	plugin's file system, 
 * or show its property	sheet.
 */
int __stdcall FsExecuteFile(HWND MainWin, char *RemoteName, char *Verb)
{
    if (!StrCmpI(Verb, "open"))
    {
        if (RequestProc(PluginNumber, RT_MsgYesNo, NULL, "Execute file?", NULL, 0))
        {
            return FS_EXEC_YOURSELF;
        }
        else if (!StrCmpI(Verb, "properties"))
        {
            return FS_EXEC_OK;
        }
    }
}