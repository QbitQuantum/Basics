TGraphErrors* plot_ramp(
			 const TString scan_file,
			 double R,
			 double R_sig
)
{

  /*Read in Data File to ROOT Tree*/
  cout<< "processing file " << scan_file <<endl;
  TTree *TData = new TTree();
  TData->ReadFile(scan_file, "t/D:x:y:z:B1:B1Range:B2:B2Range:B3:B3Range:V:T1:T2:T3:T4:T5:T6:T7:T8");
  /*Use TTree Draw command to write branches to usable vector*/
  int n = TData->Draw("TMath::Abs(B2):TMath::Abs(B3):0.0:0.005", "", "goff");

  vector<double> B_ext, B_in, Bratio, u, u_err;
  for(int i = 0; i < n; i++)
    {
  //     if(i == 0)
  //     {
  //     	B_ext.push_back(100.00);
  //     }
  //     else{
  //     	  B_ext.push_back( TData->GetV1()[i]);
  //     }
      B_ext.push_back( TData->GetV1()[i] );
      B_in.push_back( TData->GetV2()[i]);
      // B_in.push_back( 90.53);
      // if(TMath::Abs(B_in[i]) <= TMath::Abs(B_ext[i]))
      // {
	Bratio.push_back( B_in[i] / B_ext[i]);
	u.push_back( (Bratio[i]*(R**2) + Bratio[i] - 2 - 2*sqrt((Bratio[i]**2)*(R**2) - Bratio[i]*(R**2) - Bratio[i] + 1 ) ) / (Bratio[i]*(R**2) - Bratio[i]) );
	// u_err.push_back( u[i]*( 5.5*((0.005/Bratio[i])**2.) + 10*((R_sig/R)**2.)  )**0.5 );
	u_err.push_back( 0.01 );
	// u_err.push_back( u[i]*( 5.5*((0.01/Bratio[i])**2.))  )**0.5 );
	// }
      }

  TGraphErrors *g_uvB = new TGraphErrors(n, &B_ext[0], &u[0], TData->GetV3(), &u_err[0]);

  return g_uvB;
}