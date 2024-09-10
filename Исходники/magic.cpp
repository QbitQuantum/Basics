    bool matches(InputStream &stream)
    {
      unsigned char header[12];

      return stream.read(0, header, sizeof header) && decrypt(header);
    }