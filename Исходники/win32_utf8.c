struct _ITEMIDLIST *SHBrowseForFolderUTF8(struct _browseinfoA *bi)
{
  if (bi && (WDL_HasUTF8(bi->pszDisplayName) || WDL_HasUTF8(bi->lpszTitle)) AND_IS_NOT_WIN9X)
  {
    MBTOWIDE(wfn,bi->pszDisplayName);
    if (wfn_ok)
    {
      MBTOWIDE(wtxt,bi->lpszTitle);
      if (wtxt_ok)
      {
        BROWSEINFOW biw ={ bi->hwndOwner,bi->pidlRoot,wfn,wtxt,bi->ulFlags,bi->lpfn,(LPARAM)bi->lParam,bi->iImage };
        LPITEMIDLIST idlist = SHBrowseForFolderW(&biw);
        MBTOWIDE_FREE(wfn);
        MBTOWIDE_FREE(wtxt);
        return (struct _ITEMIDLIST *) idlist;
      }
      MBTOWIDE_FREE(wtxt);
    }
    MBTOWIDE_FREE(wfn);
  }
  return (struct _ITEMIDLIST *)SHBrowseForFolderA(bi);
}