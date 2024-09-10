int
main(int argc,char *argv[])
{
  tokenlist args;
  string maskfile;
  vector<string> filelist;

  args.Transfer(argc-1,argv+1);
  for (size_t i=0; i<args.size(); i++) {
    if (args[i]=="-m" && i<args.size()-1)
      maskfile=args[++i];
    else if (args[i]=="-h") {
      vbcmp_help();
      exit(0);
    }
    else if (args[i]=="-v") {
      vbcmp_version();
      exit(0);
    }
    else
      filelist.push_back(args[i]);
  }

  if (filelist.size() < 2) {
    vbcmp_help();
    exit(0);
  }
  Cube mask;
  if (maskfile.size()) {
    if (mask.ReadFile(maskfile)) {
      cout << format("[E] vbcmp: error reading mask file %s\n")%maskfile;
      exit(2);
    }
  }

  string spacer;
  if (filelist.size()>2) spacer="   ";
  for (size_t i=0; i<filelist.size(); i++) {
    for (size_t j=0; j<filelist.size(); j++) {
      if (i>=j) continue;
      if (filelist.size()>2)
        cout << format("[I] vbcmp: comparing %s and %s\n")%filelist[i]%filelist[j];
      int err1,err2;
      Cube cb1,cb2;
      err1=cb1.ReadFile(filelist[i]);
      err2=cb2.ReadFile(filelist[j]);
      if (!err1 && !err2) {
        cmp3d(cb1,cb2,mask,spacer);
        continue;
      }
      Tes ts1,ts2;
      err1=ts1.ReadFile(filelist[i]);
      err2=ts2.ReadFile(filelist[j]); 
      if (!err1 && !err2) {
        cmp4d(ts1,ts2,mask,spacer);
        continue;
      }
      // try vectors before matrices, because all vectors are matrices
      VB_Vector v1,v2;
      err1=v1.ReadFile(filelist[i]);
      err2=v2.ReadFile(filelist[j]);
      if (!err1 && !err2) {
        cmp1d(v1,v2,spacer);
        continue;
      }
      VBMatrix m1,m2;
      err1=m1.ReadFile(filelist[i]);
      err2=m2.ReadFile(filelist[j]);
      if (!err1 && !err2) {
        cmp2d(m1,m2,spacer);
        continue;
      }
      cout << format("[E] vbcmp: couldn't read %s and %s as same type\n")%filelist[i]%filelist[j];
    }
  }
  exit(100);
}