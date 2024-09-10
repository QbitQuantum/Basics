KVTGID* KVTGID::ReadFromAsciiFile(const Char_t* name, ifstream& gridfile)
{
   // Read parameters of LTG fit in file (which must have been written with
   // current version of KVTGID::WriteToAsciiFile)

   KVTGID* LTGfit = 0;
   Int_t Ftyp, Flite, FZorA, Fmass;
   FZorA = Fmass = Ftyp = Flite = 0;

   KVString line;
   line.ReadLine(gridfile);
   TString buff = GetValue(line, '=');
   Ftyp = buff.Atoi();
   line.ReadLine(gridfile);
   buff = GetValue(line, '=');
   Flite = buff.Atoi();
   line.ReadLine(gridfile);
   buff = GetValue(line, '=');
   FZorA = buff.Atoi();
   if (FZorA) {
      line.ReadLine(gridfile);
      buff = GetValue(line, '=');
      Fmass = buff.Atoi();
   }

   LTGfit = MakeTGID(name, Ftyp, Flite, FZorA, Fmass);

   line.ReadLine(gridfile); // skip "Functional=" line : name of functional not used
   line.ReadLine(gridfile);
   LTGfit->SetValidRuns(KVNumberList(GetValue(line, '=').Data()));
   line.ReadLine(gridfile);
   LTGfit->SetStringTelescopes(GetValue(line, '='));
   line.ReadLine(gridfile);
   line.Remove(0, 6);
   line.Remove(KVString::kBoth, ' ');
   LTGfit->SetVarX(line.Data());
   line.ReadLine(gridfile);
   line.Remove(0, 6);
   line.Remove(KVString::kBoth, ' ');
   LTGfit->SetVarY(line.Data());
   line.ReadLine(gridfile);
   Int_t zmin, zmax;
   sscanf(line.Data(), "ZMIN=%d ZMAX=%d", &zmin, &zmax);
   LTGfit->SetIDmin(zmin);
   LTGfit->SetIDmax(zmax);
   Bool_t type1 = (Ftyp == 1);
   line.ReadLine(gridfile);
   buff = GetValue(line, '=');
   LTGfit->SetLambda(buff.Atof());
   if (type1) {
      line.ReadLine(gridfile);
      buff = GetValue(line, '=');
      LTGfit->SetAlpha(buff.Atof());
      line.ReadLine(gridfile);
      buff = GetValue(line, '=');
      LTGfit->SetBeta(buff.Atof());
   }
   line.ReadLine(gridfile);
   buff = GetValue(line, '=');
   LTGfit->SetMu(buff.Atof());
   if (type1) {
      line.ReadLine(gridfile);
      buff = GetValue(line, '=');
      LTGfit->SetNu(buff.Atof());
      line.ReadLine(gridfile);
      buff = GetValue(line, '=');
      LTGfit->SetXi(buff.Atof());
   }
   line.ReadLine(gridfile);
   buff = GetValue(line, '=');
   LTGfit->SetG(buff.Atof());
   line.ReadLine(gridfile);
   buff = GetValue(line, '=');
   LTGfit->SetPdx(buff.Atof());
   line.ReadLine(gridfile);
   buff = GetValue(line, '=');
   LTGfit->SetPdy(buff.Atof());
   if (Flite == 1) {
      line.ReadLine(gridfile);
      buff = GetValue(line, '=');
      LTGfit->SetEta(buff.Atof());
   }
   line.ReadLine(gridfile);
   return LTGfit;
}