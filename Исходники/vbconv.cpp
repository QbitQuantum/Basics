int
main(int argc,char *argv[])
{
  if (argc==1) {
    vbconv_help();
    exit(0);
  }
  tokenlist args;
  string outfile;
  int floatflag=0,nanflag=0,extractflag=0;
  set<int> includeset,excludeset;
  list<string> filelist;
  VBFF nullff;

  args.Transfer(argc-1,argv+1);
  for (size_t i=0; i<args.size(); i++) {
    if (args[i]=="-f")
      floatflag=1;
    else if (args[i]=="-n")
      nanflag=1;
    else if (args[i]=="-i" && i<args.size()-1) {
      includeset=numberset(args[++i]);
      if (includeset.empty()) {
        cout << "[E] vbconv: invalid inclusion range specified with -i\n";
        exit(111);
      }
    }
    else if (args[i]=="-e" && i<args.size()-1) {
      excludeset=numberset(args[++i]);
      if (excludeset.empty()) {
        cout << "[E] vbconv: invalid exclusion range specified with -e\n";
        exit(111);
      }
    }
    else if (args[i]=="-x" && i<args.size()-1)
      extractflag=1;
    else if (args[i]=="-v") {
      vbconv_version();
      exit(0);
    }
    else if (args[i]=="-h") {
      vbconv_help();
      exit(0);
    }
    else if (args[i]=="-o" && i<args.size()-1)
      outfile=args[++i];
    else {
      filelist.push_back(args[i]);
    }
  }

  if (filelist.size()<1) {
    printf("[E] vbconv: requires at least one input file\n");
    exit(10);
  }
  // if there's no -o flag and exactly two files specified, convert
  // the first to the second
  if (filelist.size()==2 && outfile.size()==0) {
    outfile=filelist.back();
    filelist.pop_back();
  }
  if (outfile.size()==0) {
    printf("[E] vbconv: requires an output filename be provided\n");
    exit(11);
  }

  // multiple files, must be 3D/4D combination
  if (filelist.size()>1) {
    Tes newtes;
    ConvertMultiple(filelist,nanflag,floatflag,newtes);
    if (WriteTes(newtes,outfile,extractflag,floatflag,nanflag,includeset,excludeset))
      exit(223);
    exit(0);  // just in case
  }
  int err;
  // just one file, see what kind
  Cube cb;
  if (cb.ReadFile(filelist.front())==0) {
    cb.fileformat=nullff;
    if (floatflag && cb.datatype!=vb_float)
      cb.convert_type(vb_float);
    if (nanflag)
      cb.removenans();
    if ((err=cb.WriteFile(outfile))) {
      printf("[E] vbconv: error %d writing %s\n",err,outfile.c_str());
      exit(4);
    }
    else {
      printf("[I] vbconv: wrote cube %s\n",outfile.c_str());
      exit(0);
    }
  }
  Tes ts;
  if (ts.ReadFile(filelist.front())==0) {
    ts.fileformat=nullff;
    if ((err=WriteTes(ts,outfile,extractflag,floatflag,nanflag,includeset,excludeset))) {
      printf("[E] vbconv: error %d writing %s\n",err,outfile.c_str());
      exit(4);
    }
    else {
      printf("[I] vbconv: wrote 4D volume %s\n",outfile.c_str());
      exit(0);
    }
  }
  VB_Vector vv;
  if (vv.ReadFile(*filelist.begin())==0) {
    // vv.fileformat=nullff; // FIXME -- can we set 1d fileformat?
    if (vv.WriteFile(outfile)) {
      printf("[E] vbconv: error writing %s\n",outfile.c_str());
      exit(4);
    }
    else {
      printf("[I] vbconv: wrote vector %s\n",outfile.c_str());
      exit(0);
    }
  }
  printf("[E] vbconv: couldn't make sense of file %s\n",filelist.front().c_str());
  exit(100);
}