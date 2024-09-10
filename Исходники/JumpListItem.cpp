// (static) Creates a ShellLink that encapsulate a shortcut to local apps.
nsresult JumpListShortcut::GetShellLink(nsCOMPtr<nsIJumpListItem>& item, nsRefPtr<IShellLinkW>& aShellLink)
{
  HRESULT hr;
  IShellLinkW* psl;
  nsresult rv;

  // Shell links:
  // http://msdn.microsoft.com/en-us/library/bb776891(VS.85).aspx
  // http://msdn.microsoft.com/en-us/library/bb774950(VS.85).aspx

  PRInt16 type;
  if (NS_FAILED(item->GetType(&type)))
    return NS_ERROR_INVALID_ARG;

  if (type != nsIJumpListItem::JUMPLIST_ITEM_SHORTCUT)
    return NS_ERROR_INVALID_ARG;

  nsCOMPtr<nsIJumpListShortcut> shortcut = do_QueryInterface(item, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  nsCOMPtr<nsILocalHandlerApp> handlerApp;
  rv = shortcut->GetApp(getter_AddRefs(handlerApp));
  NS_ENSURE_SUCCESS(rv, rv);

  // Create a IShellLink 
  hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                        IID_IShellLinkW, (LPVOID*)&psl);
  if (FAILED(hr))
    return NS_ERROR_UNEXPECTED;

  // Retrieve the app path, title, description and optional command line args.
  nsAutoString appPath, appTitle, appDescription, appArgs;
  PRInt32 appIconIndex = 0;

  // Path
  nsCOMPtr<nsIFile> executable;
  handlerApp->GetExecutable(getter_AddRefs(executable));
  nsCOMPtr<nsILocalFile> localFile = do_QueryInterface(executable, &rv);
  NS_ENSURE_SUCCESS(rv, rv);

  rv = localFile->GetPath(appPath);
  NS_ENSURE_SUCCESS(rv, rv);

  // Command line parameters
  PRUint32 count = 0;
  handlerApp->GetParameterCount(&count);
  for (PRUint32 idx = 0; idx < count; idx++) {
    if (idx > 0)
      appArgs.Append(NS_LITERAL_STRING(" "));
    nsAutoString param;
    rv = handlerApp->GetParameter(idx, param);
    if (NS_FAILED(rv))
      return rv;
    appArgs.Append(param);
  }

  handlerApp->GetName(appTitle);
  handlerApp->GetDetailedDescription(appDescription);
  shortcut->GetIconIndex(&appIconIndex);

  // Store the title of the app
  if (appTitle.Length() > 0) {
    IPropertyStore* pPropStore = nsnull;
    hr = psl->QueryInterface(IID_IPropertyStore, (LPVOID*)&pPropStore);
    if (FAILED(hr))
      return NS_ERROR_UNEXPECTED;

    PROPVARIANT pv;
    InitPropVariantFromString(appTitle.get(), &pv);

    pPropStore->SetValue(PKEY_Title, pv);
    pPropStore->Commit();
    pPropStore->Release();

    PropVariantClear(&pv);
  }

  // Store the rest of the params
  psl->SetPath(appPath.get());
  psl->SetDescription(appDescription.get());
  psl->SetArguments(appArgs.get());
  psl->SetIconLocation(appPath.get(), appIconIndex);

  aShellLink = dont_AddRef(psl);

  return NS_OK;
}