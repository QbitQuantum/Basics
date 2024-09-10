int
main(int argc,char *argv[])
{
  cout << "vbmakeregress is currently broken.\n";
  exit(0);
  if (argc<2) {
    vbmakeregress_help();
    exit(0);
  }

  vbp.init();
  tokenlist args;
  string contrast;
  args.Transfer(argc-1,argv+1);
  string perm_mat;
  int spcount=0;
  int opcount=0;
  vector<string>ivnames;
  vector<string>gvnames;
  string dvname;
  int permcount=0;
  string flags;
  string glmdir;

  for (size_t i=0; i<args.size(); i++) {
    if (args[i]=="-v") {
      vbmakeregress_version();
      exit(0);
    }
    else if (args[i]=="-v") {
      vbmakeregress_help();
      exit(0);
    }
    else if (args[i]=="-d" && i<args.size()-1)
      glmdir=args[++i];
    else if (args[i]=="-sp" && i<args.size()-1)
      permcount=spcount=strtol(args[++i]);
    else if (args[i]=="-op" && i<args.size()-1)
      permcount=opcount=strtol(args[++i]);
    else if (args[i]=="-c" && i<args.size()-1) {
      flags+=" -c \""+args[++i]+"\"";
    }
    else if (args[i]=="-dv"&&i<args.size()-1) {
      dvname=args[++i];
      flags+=" -dv "+dvname;
    }
    else if (args[i]=="-iv"&&i<args.size()-1)
      flags+=" -iv "+args[++i];
    else if (args[i]=="-m"&&i<args.size()-1)
      flags+=" -m "+args[++i];
    else if (args[i]=="-int")
      flags+=" -int";
    else if (args[i]=="-gv"&&i<args.size()-1)
      flags+=" -gv "+args[++i];
  }

  if (glmdir=="") {
    printf("[E] vbmakeregress: you must set the output directory with the -d flag\n");
    exit(102);
  }
  // get size of data
  int ndata;
  Tes mytes;
  if (mytes.ReadFile(dvname)) {
    VB_Vector vv;
    if (vv.ReadFile(dvname)) {
      printf("[E] vbmakeregress: couldn't read your dependent variable for size\n");
      exit(102);
    }
    else
      ndata=vv.size();
  }
  else
    ndata=mytes.dimt;
  
  VBSequence seq;
  VBJobSpec js;
  int jobnum=0,mkdirnum=0,mkmatnum=0;
  seq.name="volregress";

  // make the directory
  if (glmdir.size()) {
    js.init();
    js.dirname=xgetcwd();
    js.jobtype="shellcommand";
    js.name="make directory";
    js.arguments["command"]=(string)"mkdir -p "+glmdir;
    js.jnum=jobnum++;
    mkdirnum=js.jnum;
    seq.addJob(js);
  }

  // make the permutation matrix
  js.init();
  js.dirname=xgetcwd();
  js.jobtype="vb_makepermmat";
  js.name="make perm matrix";
  js.arguments["outfile"]=glmdir+"/perm.mat";
  js.arguments["ndata"]=strnum(ndata);
  if (spcount) {
    js.arguments["nperms"]=strnum(spcount);
    js.arguments["permtype"]="sign";
  }
  else if (opcount) {
    js.arguments["nperms"]=strnum(opcount);
    js.arguments["permtype"]="data";
  }
  else {
    printf("[E] vbmakeregress: must specify either -sp or -op\n");
    exit(101);
  }
  if (glmdir.size())
    js.waitfor.insert(mkdirnum);
  js.jnum=jobnum++;
  mkmatnum=js.jnum;
  seq.addJob(js);

  for (int i=0; i<permcount; i++) {
    string myflags=flags;
    myflags+=" -mapfile "+glmdir+"/permcube_"+strnum(i,5)+".cub.gz";
    if (spcount)
      myflags+=" -sp "+glmdir+"/perm.mat "+strnum(i);
    else if (opcount)
      myflags+=" -op "+glmdir+"/perm.mat "+strnum(i);
    js.init();
    js.dirname=xgetcwd();
    js.jobtype="vb_volregress";
    js.name="volregress "+strnum(i+1)+"/"+strnum(permcount);
    js.arguments["flags"]=myflags;
    js.jnum=jobnum++;
    js.waitfor.insert(mkmatnum);
    seq.addJob(js);
  }
  seq.Submit(vbp);
  exit(0);
}