bool JPGDecoder::CanDecode(const std::string &filename)
{
  CFile *fp = new CFile();
  bool ret = false;
  unsigned char magic[2];
  if (fp->Open(filename))
  {

    //JPEG image files begin with FF D8 and end with FF D9.
    // check for FF D8 big + little endian on start
    uint64_t readbytes = fp->Read(magic, 2);
    if (readbytes == 2)
    {
      if ((magic[0] == 0xd8 && magic[1] == 0xff) ||
          (magic[1] == 0xd8 && magic[0] == 0xff))
        ret = true;
    }

    if (ret)
    {
      ret = false;
      //check on FF D9 big + little endian on end
      uint64_t fileSize = fp->GetFileSize();
      fp->Seek(fileSize - 2);
      readbytes = fp->Read(magic, 2);
      if (readbytes == 2)
      {
        if ((magic[0] == 0xd9 && magic[1] == 0xff) ||
           (magic[1] == 0xd9 && magic[0] == 0xff))
          ret = true;
      }
    }
  }
  delete fp;
  return ret;
}