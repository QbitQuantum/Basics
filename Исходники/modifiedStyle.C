void PrintItLog(TPad *pad, TString title)//char *title)
{
  TLatex *latex = new TLatex();
  latex->SetTextFont(  42);
  latex->SetTextSize(0.05);

  // Get the most recent changes
  pad->Update();

  double xmin = pad->GetUxmin();
  double xmax = pad->GetUxmax();
  //double ymin = pad->GetUymin();
  double ymax = pad->GetUymax();

  //cout << "xmin = " << xmin << endl;
  //cout << "xmax = " << xmax << endl;
  //cout << "ymin = " << ymin << endl;
  //cout << "ymax = " << ymax << endl;
  //cout << "TMath::Power(10,ymax) = " << TMath::Power(10,ymax) << endl; 

  double xpos = xmin + 0.50*(xmax - xmin);
  double ypos = 1.5*TMath::Power(10,ymax);// + TMath::*(ymax - ymin);
  
  latex->SetTextAlign(22);
  latex->DrawLatex(xpos,ypos,title);
}