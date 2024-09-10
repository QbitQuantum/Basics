int Ridgecntbbc::Init()
{
  coll = "";
  TString temp = OutputFileName;
  temp.ToLower();
  fetchdphidz();
  if(temp.Contains("pp") && temp.Contains("mbst")) coll = "ppminbias";
  else if(temp.Contains("pal") && temp.Contains("mbst")) coll = "pAlminbias";
  else if(temp.Contains("pal") && temp.Contains("mbcentral")) coll = "pAlcentral";
  else if(temp.Contains("pp") && temp.Contains("fvtxand")) coll = "ppfvtxand";
  else if(temp.Contains("pal") && temp.Contains("fvtxand")) coll = "pAlfvtxand";
  else if(temp.Contains("pp") && temp.Contains("fvtxor")) coll = "ppfvtxor";
  else if(temp.Contains("pal") && temp.Contains("fvtxor")) coll = "pAlfvtxor";
  else if(temp.Contains("pal") && temp.Contains("fvtxsouth")) coll = "pAlfvtxsouth";
  else if(temp.Contains("pal") && temp.Contains("fvtxnorth")) coll = "pAlfvtxnorth";
  else return 0;

//  OutputFileName.Insert(OutputFileName.Length()-5,coll);

  d_outfile = new TFile(OutputFileName,"recreate");
      d_infile = TFile::Open(InputFileName,"ReadOnly");
  if(!d_infile) return 0;
  tree = (TTree*)d_infile->Get("tree");
  if(!tree) return 0;
  
  tree -> SetBranchAddress("run", &run);
  tree -> SetBranchAddress("trig", &trig);
  tree -> SetBranchAddress("npc1hits", &npc1hits);
  tree -> SetBranchAddress("bbc_s", &bbc_s);
  tree -> SetBranchAddress("bbc_n", &bbc_n);
  tree -> SetBranchAddress("bbcv", &bbcv);
  if(coll.Contains("pp"))
  tree -> SetBranchAddress("vtxz", &vtxz);
//  tree -> SetBranchAddress("fvtxz", &fvtxz);
  tree -> SetBranchAddress("ntrack", &ntrack);
  tree -> SetBranchAddress("nbbc", &nbbc);
  if(coll.Contains("pp")){
  tree -> SetBranchAddress("nvtx", &nvtx);
  tree -> SetBranchAddress("nvtxtrack", &nvtxtrack);
  }
//  tree -> SetBranchAddress("nmpc", &nmpc);
// tree -> SetBranchAddress("nfvtxtrack", &nfvtxtrack);

  tree -> SetBranchAddress("mom", &mom);
  tree -> SetBranchAddress("phi0", &phi0);
  tree -> SetBranchAddress("the0", &the0);
  tree -> SetBranchAddress("charge", &charge);
  tree -> SetBranchAddress("arm", &arm);
  tree -> SetBranchAddress("pc3dphi", &pc3dphi);
  tree -> SetBranchAddress("pc3dz", &pc3dz);
  tree -> SetBranchAddress("slat", &slat);
  tree -> SetBranchAddress("tofdphi", &tofdphi);
  tree -> SetBranchAddress("tofdz", &tofdz);
  tree -> SetBranchAddress("tofpl", &tofpl);
  tree -> SetBranchAddress("qtof", &qtof);
  tree -> SetBranchAddress("ttof", &ttof);

  tree -> SetBranchAddress("bbccharge", &bbccharge);
  tree -> SetBranchAddress("bbcx", &bbcx);
  tree -> SetBranchAddress("bbcy", &bbcy);
  tree -> SetBranchAddress("bbcz", &bbcz);

  if(coll.Contains("pp")){
  tree -> SetBranchAddress("layer", &layer);
  tree -> SetBranchAddress("vtxX", &vtxX);
  tree -> SetBranchAddress("vtxY", &vtxY);
  tree -> SetBranchAddress("vtxZ", &vtxZ);

  tree -> SetBranchAddress("vtxnhits", &vtxnhits);
  tree -> SetBranchAddress("vtxpx", &vtxpx);
  tree -> SetBranchAddress("vtxpy", &vtxpy);
  tree -> SetBranchAddress("vtxpz", &vtxpz);
  }
 /*
  tree -> SetBranchAddress("mpc_e", &mpc_e);
  tree -> SetBranchAddress("mpc_x", &mpc_x);
  tree -> SetBranchAddress("mpc_y", &mpc_y);
  tree -> SetBranchAddress("mpc_z", &mpc_z);
*/
  /*
  tree -> SetBranchAddress("farm", &farm);
  tree -> SetBranchAddress("fnhits", &fnhits);
  tree -> SetBranchAddress("fthe", &fthe);
  tree -> SetBranchAddress("feta", &feta);
  tree -> SetBranchAddress("fphi", &fphi);
  tree -> SetBranchAddress("fvtxX", &fvtxX);
  tree -> SetBranchAddress("fvtxY", &fvtxY);
  tree -> SetBranchAddress("fvtxZ", &fvtxZ);
*/
char name[512];
 pi = acos(-1);


   sprintf(name,"hevent");
   hevent = new TH1F(name,name,1,0,1);

  for (int icent=0; icent<centbin; icent++) {
    //bbc correlation
    for(int ipt=0; ipt<ptbin; ipt++){
      //cnt with bbc
      sprintf(name,"hforesouthbbc_%d_%d",icent,ipt);
      hforesouthbbc[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"hbacksouthbbc_%d_%d",icent,ipt);
      hbacksouthbbc[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"hforenorthbbc_%d_%d",icent,ipt);
      hforenorthbbc[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"hbacknorthbbc_%d_%d",icent,ipt);
      hbacknorthbbc[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      //flip
      sprintf(name,"kforesouthbbc_%d_%d",icent,ipt);
      kforesouthbbc[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacksouthbbc_%d_%d",icent,ipt);
      kbacksouthbbc[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"kforenorthbbc_%d_%d",icent,ipt);
      kforenorthbbc[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacknorthbbc_%d_%d",icent,ipt);
      kbacknorthbbc[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);
//with weight
      sprintf(name,"hforesouthbbcw_%d_%d",icent,ipt);
      hforesouthbbcw[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"hbacksouthbbcw_%d_%d",icent,ipt);
      hbacksouthbbcw[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"hforenorthbbcw_%d_%d",icent,ipt);
      hforenorthbbcw[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"hbacknorthbbcw_%d_%d",icent,ipt);
      hbacknorthbbcw[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      //flip
      sprintf(name,"kforesouthbbcw_%d_%d",icent,ipt);
      kforesouthbbcw[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacksouthbbcw_%d_%d",icent,ipt);
      kbacksouthbbcw[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"kforenorthbbcw_%d_%d",icent,ipt);
      kforenorthbbcw[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacknorthbbcw_%d_%d",icent,ipt);
      kbacknorthbbcw[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);



      //mixing with bbc
      sprintf(name,"hbacksouthbbc2_%d_%d",icent,ipt);
      hbacksouthbbc2[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"hbacknorthbbc2_%d_%d",icent,ipt);
      hbacknorthbbc2[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      //flip
      sprintf(name,"kbacksouthbbc2_%d_%d",icent,ipt);
      kbacksouthbbc2[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacknorthbbc2_%d_%d",icent,ipt);
      kbacknorthbbc2[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      //with weight
      sprintf(name,"hbacksouthbbcw2_%d_%d",icent,ipt);
      hbacksouthbbcw2[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"hbacknorthbbcw2_%d_%d",icent,ipt);
      hbacknorthbbcw2[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      //flip
      sprintf(name,"kbacksouthbbcw2_%d_%d",icent,ipt);
      kbacksouthbbcw2[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacknorthbbcw2_%d_%d",icent,ipt);
      kbacknorthbbcw2[icent][ipt] = new TH1F(name,name,40, -0.5*pi, 1.5*pi);


      //2D
      sprintf(name,"kforesouthetabbc_%d_%d",icent,ipt);
      kforesouthetabbc[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacksouthetabbc_%d_%d",icent,ipt);
      kbacksouthetabbc[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kforenorthetabbc_%d_%d",icent,ipt);
      kforenorthetabbc[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacknorthetabbc_%d_%d",icent,ipt);
      kbacknorthetabbc[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacksouthetabbc2_%d_%d",icent,ipt);
      kbacksouthetabbc2[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacknorthetabbc2_%d_%d",icent,ipt);
      kbacknorthetabbc2[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      //with weight
      sprintf(name,"kforesouthetabbcw_%d_%d",icent,ipt);
      kforesouthetabbcw[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacksouthetabbcw_%d_%d",icent,ipt);
      kbacksouthetabbcw[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kforenorthetabbcw_%d_%d",icent,ipt);
      kforenorthetabbcw[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacknorthetabbcw_%d_%d",icent,ipt);
      kbacknorthetabbcw[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacksouthetabbcw2_%d_%d",icent,ipt);
      kbacksouthetabbcw2[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);

      sprintf(name,"kbacknorthetabbcw2_%d_%d",icent,ipt);
      kbacknorthetabbcw2[icent][ipt] = new TH2F(name, name, 100, -5.0, 5.0, 40, -0.5*pi, 1.5*pi);
    }
  }

  memset(ntrack_buff, 0, sizeof(ntrack_buff));
  memset(dtrack_buff, 0, sizeof(dtrack_buff));
  memset(buff_ntrack, 0, sizeof(buff_ntrack));

  memset(nbbcau_buff, 0, sizeof(nbbcau_buff));
  memset(dbbcau_buff, 0, sizeof(dbbcau_buff));
  memset(buff_nbbcau, 0, sizeof(buff_nbbcau));

  memset(nbbcde_buff, 0, sizeof(nbbcde_buff));
  memset(dbbcde_buff, 0, sizeof(dbbcde_buff));
  memset(buff_nbbcde, 0, sizeof(buff_nbbcde));

  return 0;
}