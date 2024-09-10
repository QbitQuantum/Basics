void
FrameworkView::ProcessActivationArgs(IActivatedEventArgs* aArgs, bool aStartup)
{
  ActivationKind kind;
  if (!aArgs || FAILED(aArgs->get_Kind(&kind)))
    return;
  ComPtr<IActivatedEventArgs> args(aArgs);
  if (kind == ActivationKind::ActivationKind_Protocol) {
    WinUtils::Log("Activation argument kind: Protocol");
    ComPtr<IProtocolActivatedEventArgs> protoArgs;
    AssertHRESULT(args.As(&protoArgs));
    ComPtr<IUriRuntimeClass> uri;
    AssertHRESULT(protoArgs->get_Uri(uri.GetAddressOf()));
    if (!uri)
      return;

    HString data;
    AssertHRESULT(uri->get_AbsoluteUri(data.GetAddressOf()));
    if (WindowsIsStringEmpty(data.Get()))
      return;

    if (aStartup) {
      WindowsDuplicateString(data.Get(), &sActivationURI);
    } else {
      PerformURILoad(data);
    }
  } else if (kind == ActivationKind::ActivationKind_Search) {
    WinUtils::Log("Activation argument kind: Search");
    ComPtr<ISearchActivatedEventArgs> searchArgs;
    args.As(&searchArgs);
    SearchActivated(searchArgs, aStartup);
  } else if (kind == ActivationKind::ActivationKind_File) {
    WinUtils::Log("Activation argument kind: File");
    ComPtr<IFileActivatedEventArgs> fileArgs;
    args.As(&fileArgs);
    FileActivated(fileArgs, aStartup);
  } else if (kind == ActivationKind::ActivationKind_Launch) {
    WinUtils::Log("Activation argument kind: Launch");
    ComPtr<ILaunchActivatedEventArgs> launchArgs;
    args.As(&launchArgs);
    LaunchActivated(launchArgs, aStartup);
  }
}