int DoIt(const char* outFile, const char* regFile, const char* maskFile, const char* resultFile,
          int mask_x, int mask_y, int mask_size_x, int mask_size_y)
{
  // Read maskfile
  FILE *mfp = fopen(maskFile, "r");
//      FILE *mfp=fopen("/project/geoaida/tmp/mask.pbm","r");

  if (!mfp) {
    fprintf(stderr, "mask file %s not found\n", maskFile);
    return 1;
  }
  GaMaskImage mask;
  mask.read(mfp);
  fclose(mfp);

  QList<ArgDict> *regionSourceList=readRegionFile(regFile);
  if (!regionSourceList) return 1;
  QList<ArgDict> regionList;

  // Process regions
  for (ArgDict* arg = regionSourceList->first();
       arg;
       arg=regionSourceList->next()) {
    ArgDict* args=new ArgDict(*arg);
    if (processRegion
	(*args, mask, mask_x, mask_y, mask_size_x, mask_size_y))
      regionList.append(args);
    else
      delete args;
  }
  
  // Write labels
  QFile rfp(outFile ? outFile : regFile);
  if (outFile) {
    if (labelImageDict.count() > 1) {
      fprintf(stderr, "regionmask: Cannot generate multiple labelfiles\n");
      return 1;
    }
    else {
      if (regionList.count()>0) {
        ArgDict *dict = regionList.first();
        QString *oldfile = (*dict)["file"];
        QString *labelfile = new QString();
        if (resultFile)
          labelfile->sprintf("%s", resultFile);
        else
          labelfile->sprintf("%s.plm", outFile);
        LabelImage *im = labelImageDict.take(*oldfile);
        labelImageDict.replace(*labelfile, im);
        QListIterator < ArgDict > it(regionList);
        for (; it.current(); ++it) {
          ArgDict *argDict = it.current();
          assert(argDict);
          argDict->replace("file", labelfile);
        }
      }
    }
  }
  else {
    printf("regionmask: overwriting %s\n",regFile);
    outFile = regFile;
  }
  QDictIterator < LabelImage > git(labelImageDict);
  if (regionList.count()>0) {
    for (; git.current(); ++git) {
      LabelImage *im = git.current();
      qDebug("Writing %s", git.currentKey().latin1());
      im->image.write(git.currentKey().latin1());
    }
  }
  // Write regions
  if (!rfp.open(IO_WriteOnly)) {
    fprintf(stderr, "cannot open regionfile %s for writing\n", outFile);
    return 1;
  }
  if (regionList.count()>0) {
    QListIterator < ArgDict > it(regionList);
    QTextStream ts(&rfp);
    for (; it.current(); ++it) {
      ArgDict *argDict = it.current();
      assert(argDict);
      ts << "<region ";
      ts << (*argDict);
      ts << " />" << endl;
    }
  }
  rfp.close();
  labelImageDict.setAutoDelete(true);
  labelImageDict.clear();
  regionList.setAutoDelete(true);
  return 0;
}