  void ZlibCompressor::Compress(std::string& compressed,
                                const void* uncompressed,
                                size_t uncompressedSize)
  {
    if (uncompressedSize == 0)
    {
      compressed.clear();
      return;
    }

    uLongf compressedSize = compressBound(uncompressedSize) + 1024 /* security margin */;
    if (compressedSize == 0)
    {
      compressedSize = 1;
    }

    uint8_t* target;
    if (HasPrefixWithUncompressedSize())
    {
      compressed.resize(compressedSize + sizeof(uint64_t));
      target = reinterpret_cast<uint8_t*>(&compressed[0]) + sizeof(uint64_t);
    }
    else
    {
      compressed.resize(compressedSize);
      target = reinterpret_cast<uint8_t*>(&compressed[0]);
    }

    int error = compress2(target,
                          &compressedSize,
                          const_cast<Bytef *>(static_cast<const Bytef *>(uncompressed)), 
                          uncompressedSize,
                          GetCompressionLevel());

    if (error != Z_OK)
    {
      compressed.clear();

      switch (error)
      {
      case Z_MEM_ERROR:
        throw OrthancException(ErrorCode_NotEnoughMemory);

      default:
        throw OrthancException(ErrorCode_InternalError);
      }  
    }

    // The compression was successful
    if (HasPrefixWithUncompressedSize())
    {
      uint64_t s = static_cast<uint64_t>(uncompressedSize);
      memcpy(&compressed[0], &s, sizeof(uint64_t));
      compressed.resize(compressedSize + sizeof(uint64_t));
    }
    else
    {
      compressed.resize(compressedSize);
    }
  }