/* Decompress a seekable compressed stream */
int SzipDecompress::run(const char *name, Buffer &origBuf,
                        const char *outName, Buffer &outBuf)
{
  size_t origSize = origBuf.GetLength();
  if (origSize < sizeof(SeekableZStreamHeader)) {
    log("%s is not compressed", name);
    return 0;
  }

  SeekableZStream zstream;
  if (!zstream.Init(origBuf, origSize))
    return 0;

  size_t size = zstream.GetUncompressedSize();

  /* Give enough room for the uncompressed data */
  if (!outBuf.Resize(size)) {
    log("Error resizing %s: %s", outName, strerror(errno));
    return 1;
  }

  if (!zstream.Decompress(outBuf, 0, size))
    return 1;

  return 0;
}