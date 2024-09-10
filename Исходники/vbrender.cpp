int
RenderMe::Go(tokenlist &args)
{
  if (!args.size()) {
    help();
    return 102;
  }
  for (int i=0; i<args.size(); i++) {
    if (args[i]=="-m" && i+1 < args.size()) {
      maskname=args[i+1];
      i++;
    }
    else if (args[i]=="-d" && i+1 < args.size()) {
      overlayname=args[i+1];
      i++;
    }
    else if (args[i]=="-o" && i+1 < args.size()) {
      outfilename=args[i+1];
      i++;
    }
    else if (args[i]=="-a" && i+1 < args.size()) {
      anatomyname=args[i+1];
      i++;
    }
    else if (args[i]=="-1") {
      vbr.twotailed=0;
    }
    else if (args[i]=="-t" && i+2 < args.size()) {
      vbr.low=strtod(args[i+1]);
      vbr.high=strtod(args[i+2]);
      i+=2;
    }
  }

  if (outfilename.size() && !anatomyname.size() && !overlayname.size()) {
    help();
    return 101;
  }

  char tmp[STRINGLEN];

  if (anatomyname.size()) {
    anatomy.ReadFile(anatomyname);
    if (!anatomy.data_valid){
      sprintf(tmp,"vbrender: anatomy file %s not valid",anatomyname.c_str());
      printErrorMsg(VB_ERROR,tmp);
      return 102;
    }
    vbr.anatomy=&anatomy;
  }

  if (overlayname.size()) {
    overlay.ReadFile(overlayname);
    if (!overlay.data_valid){
      sprintf(tmp,"vbrender: statistical overlay file %s not valid",overlayname.c_str());
      printErrorMsg(VB_ERROR,tmp);
      return 102;
    }
    vbr.overlay=&overlay;
  }

  if (maskname.size()) {
    mask.ReadFile(maskname);
    if (!mask.data_valid){
      sprintf(tmp,"vbrender: mask file %s not valid",maskname.c_str());
      printErrorMsg(VB_ERROR,tmp);
      return 102;
    }
    vbr.mask=&mask;
  }

  QImage im;
  if (vbr.RenderSlices())
    return 103;
  if (vbr.SavePNG(outfilename))
    return 103;
  return 0;
}