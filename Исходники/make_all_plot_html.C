void make_all_plot_html(TString file,TString path)
{
  ///
  /// Load up the macros to make sure we can interpret everything
  /// in there!
  ///

  //  gInterpreter->ExecuteMacro ("topd0root_analysis/compile.C");

  ///
  /// Setup
  ///

  TFile *f = new TFile(file);
  TEnv *params = new TEnv ("make_all_plot_html");
  //  params->ReadFile ("topd0root_analysis/macros/make_all_plot_html.params", kEnvChange);
  params->ReadFile ("make_all_plot_html.params", kEnvChange);

  gStyle->SetPalette(1);

  ///
  /// Ok -- we are ready to recursively process this stuff!
  ///

  html_a_directory (f, path, params);
}