int
VBri::openconfig(string configfile)
{
  ifstream infile;
  infile.open(configfile.c_str());
  if (!infile) {
    QMessageBox::critical(this,"Error","Couldn't open config file.");
    return 2;
  }
  chdir(xdirname(configfile).c_str());

  char buf[STRINGLEN];
  tokenlist args;
  while (infile.getline(buf,STRINGLEN,'\n')) {
    args.ParseLine(buf);
    if (args.size()==0) continue;
    if (args[0][0]=='#' || args[0][0] == ';')
      continue;
    if (args[0]=="image" && args.size()==3) {
      Cube cb;
      if (cb.ReadFile(args[2])) {
        QMessageBox::critical(this,"Error",(format("Couldn't open image %s")%args[2]).str().c_str());
        infile.close();
        return 3;
      }
      find_origin(cb);
      cubelist.push_back(cb);
      cubemap[args[1]]=--cubelist.end();
    }
    else if (args[0]=="left") {
      leftimg=args[1];
    }
    else if (args[0]=="right") {
      rightimg=args[1];
    }
    else if (args[0]=="mask") {
      VBmask vbm;
      vbm.imgname=args[1];
      if (args.size()>2) {
        vbm.rating=strtol(args[2]);
        vbm.xslice=strtol(args[3]);
        vbm.yslice=strtol(args[3]);
        vbm.zslice=strtol(args[3]);
        vbm.notes=args.Tail(4);
      }
      else if (cubemap.count(vbm.imgname)) {
        // FIXME get it from the header...
        vbm.xslice=cubemap[vbm.imgname]->origin[0];
        vbm.yslice=cubemap[vbm.imgname]->origin[1];
        vbm.zslice=cubemap[vbm.imgname]->origin[2];
      }
      masklist.push_back(vbm);
    }
    else if (args[0]=="outfile") {
      if (args.size()>1)
        outfile=args[1];
    }
    else if (args[0]=="randomize") {
      randomizemasks();
    }
    else {
      QMessageBox::critical(this,"Error",((string)"Bad config line: "+buf).c_str());
      infile.close();
      return 4;
    }
  }
  infile.close();
  return 0;
}