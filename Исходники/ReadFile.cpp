ReadFile* ReadFile::makeInvertedReadFile(string filename, float countFactor){
  FileType fileType = getFileType(filename);
  ReadFile* rf;
  if (fileType == FASTQFILE){ rf = new ReadFileFastqSingle(true,filename,ReadFileFastqSingle::fastqSystem,countFactor); }
  else if (fileType == PRICEQFILE){ rf = new ReadFilePriceqSingle(true,filename); }
  else if (fileType == FASTAFILE){ rf = new ReadFileFastaSingle(filename,countFactor,true); }
  else if (fileType == ILLUMINAFILE){ rf = new ReadFileFastqSingle(true,filename,ReadFileFastqSingle::illuminaSystem,countFactor); }
  else { throw AssemblyException::ArgError("read file is of an inappropriate type."); }
  return rf;
}