outputfile::outputfile(const festring& FileName, truth AbortOnErr)
: Buffer(fopen(FileName.CStr(), "wb")), FileName(FileName)
{
  if(AbortOnErr && !IsOpen())
    ABORT("Can't open %s for output!", FileName.CStr());
}