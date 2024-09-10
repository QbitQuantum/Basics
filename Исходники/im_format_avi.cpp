void imFileFormatAVI::Close()
{
  if (this->dib) imDibDestroy(this->dib);

  if (this->use_compressor) 
  {
    ICSeqCompressFrameEnd(&this->compvars);
    ICCompressorFree(&this->compvars);
  }

  if (this->frame) AVIStreamGetFrameClose(this->frame);
  if (this->stream) AVIStreamRelease(this->stream);

  AVIFileRelease(this->file);
  AVIFileExit();    /* called one for each AVIFileInit */
}