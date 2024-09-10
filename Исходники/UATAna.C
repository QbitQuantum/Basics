void UATAna(TString Cfg = "Config.cfg" , TString Steps = "R"){

  Steps.ToUpper();

  UATAnaConfig Config;
  Config.ReadCfg(Cfg);
  Config.Print();

  if (    Steps.Contains ('R') 
       || Steps.Contains ('T') ) {
    bool bWTree = false ;
    if ( Steps.Contains ('T') ) bWTree = true ;
    UATAnaReader Reader;
    Reader.Init   (Config , bWTree );
    Reader.Analyze(Config , bWTree );
    Reader.End    (Config , bWTree );
  }
  
  if (    Steps.Contains ('F')
       || Steps.Contains ('Y')
       || Steps.Contains ('L')
       || Steps.Contains ('C') ) {

    UATAnaDisplay Display;
    Display.Init   (Config);

    if ( Steps.Contains ('D') ) { Config.SetDrawRatio(true); Config.SetDrawBgError(true); }
    if ( Steps.Contains ('E') ) Config.SetDrawBgError(true);
    if ( Steps.Contains ('F') ) Display.Yields(Config,1);
    if ( Steps.Contains ('Y') ) Display.Yields(Config,0,0);
    if ( Steps.Contains ('C') ) { 
      if ( Steps.Contains ('S') ) Display.CPlot (Config,1);
      else                        Display.CPlot (Config,0);
    }
    if ( Steps.Contains ('L') ) Display.LimitCard (Config);

  }

} 