bool IsRelativeSymlinkSafe(CommandData *Cmd,const wchar *SrcName,const wchar *PrepSrcName,const wchar *TargetName)
{
  // Catch root dir based /path/file paths also as stuff like \\?\.
  // Do not check PrepSrcName here, it can be root based if destination path
  // is a root based.
  if (IsFullRootPath(SrcName) || IsFullRootPath(TargetName))
    return false;
  
  // We could check just prepared src name, but for extra safety
  // we check both original (as from archive header) and prepared
  // (after applying the destination path and -ep switches) names.

  int AllowedDepth=CalcAllowedDepth(SrcName); // Original name depth.

  // Remove the destination path from prepared name if any. We should not
  // count the destination path depth, because the link target must point
  // inside of this path, not outside of it.
  size_t ExtrPathLength=wcslen(Cmd->ExtrPath);
  if (ExtrPathLength>0 && wcsncmp(PrepSrcName,Cmd->ExtrPath,ExtrPathLength)==0)
  {
    PrepSrcName+=ExtrPathLength;
    while (IsPathDiv(*PrepSrcName))
      PrepSrcName++;
  }
  int PrepAllowedDepth=CalcAllowedDepth(PrepSrcName);

  // Number of ".." in link target.
  int UpLevels=0;
  for (int Pos=0;*TargetName!=0;Pos++)
  {
    bool Dot2=TargetName[0]=='.' && TargetName[1]=='.' && 
              (IsPathDiv(TargetName[2]) || TargetName[2]==0) &&
              (Pos==0 || IsPathDiv(*(TargetName-1)));
    if (Dot2)
      UpLevels++;
    TargetName++;
  }
  return AllowedDepth>=UpLevels && PrepAllowedDepth>=UpLevels;
}