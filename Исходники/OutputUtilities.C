  /** 
   * Stop a previously started Xrootd server 
   * 
   * @return true if stopped, false otherwise 
   */
  static Bool_t StopXrootd()
  {
    std::ifstream pidFile("xrd.pid");
    if (!pidFile) return false;

    TString s; s.ReadFile(pidFile);
    pidFile.close();
    gSystem->Unlink("xrd.pid");
    
    if (s.IsNull()) return false;

    Info("StopXrootd", "Stopping XRootd server (pid: %s)", s.Data());
    return gSystem->Exec(Form("kill -9 %s", s.Data())) == 0;
  }