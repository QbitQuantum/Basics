bool C4KeyboardInput::LoadCustomConfig()
{
    // load from INI file (2do: load from registry)
    C4Group GrpExtra;
    if (!GrpExtra.Open(C4CFN_Extra)) return false;
    StdBuf sFileContents;
    if (!GrpExtra.LoadEntry(C4CFN_KeyConfig, &sFileContents)) return false;
    StdStrBuf sFileContentsString((const char *) sFileContents.getData());
    if (!CompileFromBuf_LogWarn<StdCompilerINIRead>(*this, sFileContentsString, "Custom keys from" C4CFN_Extra DirSep C4CFN_KeyConfig))
        return false;
    LogF(LoadResStr("IDS_PRC_LOADEDKEYCONF"), C4CFN_Extra DirSep C4CFN_KeyConfig);
    return true;
}