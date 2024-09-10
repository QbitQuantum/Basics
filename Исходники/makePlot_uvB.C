/*
 * The Calibration function reads in the
 * calibration file and returns a graph
 * that is used to find the relation
 * between current and magentic field
 * for the Helmholtz coil.
 */
TF1* Calibrate(
		    const char* f_calib
		    )
{
  /*Read in Calibration File*/
  cout<< "processing file " << f_calib <<endl;
  TTree *TCalib = new TTree();
  TCalib->ReadFile(f_calib, "t/D:I:B");
  int n = TCalib->Draw("I:TMath::Abs(B)", "", "goff");
  TGraph *g_calib = new TGraph(n, TCalib->GetV1(), TCalib->GetV2() );
  g_calib->SetTitle("");
  // g_calib->Draw("AP");
  g_calib->Fit("pol1", "q");
  TF1* calib_fit = g_calib->GetFunction("pol1");

  return calib_fit;

}