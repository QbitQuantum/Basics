Double_t CalcLednicR(Double_t zr, Double_t zt, Double_t v)
{
  TString cmd = Form("echo '%0.5f,%0.5f,%0.5f'", zr, zt, v);
  cmd+= " | ./lednic_input.exe";
  Printf("%s", cmd.Data());
  cmd = gSystem->GetFromPipe(cmd.Data());
  if (!cmd.IsFloat()) {
    Printf("Problem with program 'lednic_input.exe'");
    return 0;
  }
  return cmd.Atof();
}