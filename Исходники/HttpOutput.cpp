  void HttpOutput::Answer(const void* buffer, 
                          size_t length)
  {
    if (length == 0)
    {
      AnswerEmpty();
      return;
    }

    HttpCompression compression = GetPreferredCompression(length);

    if (compression == HttpCompression_None)
    {
      stateMachine_.SetContentLength(length);
      stateMachine_.SendBody(buffer, length);
      return;
    }

    std::string compressed, encoding;

    switch (compression)
    {
      case HttpCompression_Deflate:
      {
        encoding = "deflate";
        ZlibCompressor compressor;
        // Do not prefix the buffer with its uncompressed size, to be compatible with "deflate"
        compressor.SetPrefixWithUncompressedSize(false);  
        compressor.Compress(compressed, buffer, length);
        break;
      }

      case HttpCompression_Gzip:
      {
        encoding = "gzip";
        GzipCompressor compressor;
        compressor.Compress(compressed, buffer, length);
        break;
      }

      default:
        throw OrthancException(ErrorCode_InternalError);
    }

    LOG(TRACE) << "Compressing a HTTP answer using " << encoding;

    // The body is empty, do not use HTTP compression
    if (compressed.size() == 0)
    {
      AnswerEmpty();
    }
    else
    {
      stateMachine_.AddHeader("Content-Encoding", encoding);
      stateMachine_.SetContentLength(compressed.size());
      stateMachine_.SendBody(compressed.c_str(), compressed.size());
    }

    stateMachine_.CloseBody();
  }