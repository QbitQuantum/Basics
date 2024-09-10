// this implementation was pretty much copied verbatime from 
// Tony Robinson's code in nsExternalProtocolWin.cpp
nsresult
nsMIMEInfoWin::LoadUriInternal(nsIURI * aURL)
{
  nsresult rv = NS_OK;

  // 1. Find the default app for this protocol
  // 2. Set up the command line
  // 3. Launch the app.

  // For now, we'll just cheat essentially, check for the command line
  // then just call ShellExecute()!

  if (aURL)
  {
    // extract the url spec from the url
    nsCAutoString urlSpec;
    aURL->GetAsciiSpec(urlSpec);
 
    // Unescape non-ASCII characters in the URL
    nsCAutoString urlCharset;
    nsAutoString utf16Spec;
    rv = aURL->GetOriginCharset(urlCharset);
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsITextToSubURI> textToSubURI = do_GetService(NS_ITEXTTOSUBURI_CONTRACTID, &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    rv = textToSubURI->UnEscapeNonAsciiURI(urlCharset, urlSpec, utf16Spec);
    NS_ENSURE_SUCCESS(rv, rv);

    static const PRUnichar cmdVerb[] = L"open";
    SHELLEXECUTEINFOW sinfo;
    memset(&sinfo, 0, sizeof(sinfo));
    sinfo.cbSize   = sizeof(sinfo);
    sinfo.fMask    = SEE_MASK_FLAG_DDEWAIT |
      SEE_MASK_FLAG_NO_UI;
    sinfo.hwnd     = NULL;
    sinfo.lpVerb   = (LPWSTR)&cmdVerb;
    sinfo.nShow    = SW_SHOWNORMAL;
    
    LPITEMIDLIST pidl = NULL;
    SFGAOF sfgao;
    
    // Bug 394974
    if (SUCCEEDED(SHParseDisplayName(utf16Spec.get(),NULL, &pidl, 0, &sfgao))) {
      sinfo.lpIDList = pidl;
      sinfo.fMask |= SEE_MASK_INVOKEIDLIST;
    } else {
      // SHParseDisplayName failed. Bailing out as work around for
      // Microsoft Security Bulletin MS07-061
      rv = NS_ERROR_FAILURE;
    }
    if (NS_SUCCEEDED(rv)) {
      BOOL result = ShellExecuteExW(&sinfo);
      if (!result || ((LONG_PTR)sinfo.hInstApp) < 32)
        rv = NS_ERROR_FAILURE;
    }
    if (pidl)
      CoTaskMemFree(pidl);
  }
  
  return rv;
}