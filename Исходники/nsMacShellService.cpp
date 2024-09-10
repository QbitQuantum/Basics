NS_IMETHODIMP
nsMacShellService::OpenApplicationWithURI(nsIFile* aApplication,
                                          const nsACString& aURI) {
  nsCOMPtr<nsILocalFileMac> lfm(do_QueryInterface(aApplication));
  CFURLRef appURL;
  nsresult rv = lfm->GetCFURL(&appURL);
  if (NS_FAILED(rv)) return rv;

  const nsCString spec(aURI);
  const UInt8* uriString = (const UInt8*)spec.get();
  CFURLRef uri = ::CFURLCreateWithBytes(nullptr, uriString, aURI.Length(),
                                        kCFStringEncodingUTF8, nullptr);
  if (!uri) return NS_ERROR_OUT_OF_MEMORY;

  CFArrayRef uris = ::CFArrayCreate(nullptr, (const void**)&uri, 1, nullptr);
  if (!uris) {
    ::CFRelease(uri);
    return NS_ERROR_OUT_OF_MEMORY;
  }

  LSLaunchURLSpec launchSpec;
  launchSpec.appURL = appURL;
  launchSpec.itemURLs = uris;
  launchSpec.passThruParams = nullptr;
  launchSpec.launchFlags = kLSLaunchDefaults;
  launchSpec.asyncRefCon = nullptr;

  OSErr err = ::LSOpenFromURLSpec(&launchSpec, nullptr);

  ::CFRelease(uris);
  ::CFRelease(uri);

  return err != noErr ? NS_ERROR_FAILURE : NS_OK;
}