Mappable *
MappableExtractFile::Create(const char *name, Zip *zip, Zip::Stream *stream)
{
  MOZ_ASSERT(zip && stream);

  const char *cachePath = getenv("MOZ_LINKER_CACHE");
  if (!cachePath || !*cachePath) {
    WARN("MOZ_LINKER_EXTRACT is set, but not MOZ_LINKER_CACHE; "
        "not extracting");
    return nullptr;
  }

  // Ensure that the cache dir is private.
  chmod(cachePath, 0770);

  UniquePtr<char[]> path =
    MakeUnique<char[]>(strlen(cachePath) + strlen(name) + 2);
  sprintf(path.get(), "%s/%s", cachePath, name);

  CacheValidator validator(path.get(), zip, stream);
  if (validator.IsValid()) {
    DEBUG_LOG("Reusing %s", static_cast<char *>(path.get()));
    return MappableFile::Create(path.get());
  }
  DEBUG_LOG("Extracting to %s", static_cast<char *>(path.get()));
  AutoCloseFD fd;
  fd = open(path.get(), O_TRUNC | O_RDWR | O_CREAT | O_NOATIME,
                        S_IRUSR | S_IWUSR);
  if (fd == -1) {
    ERROR("Couldn't open %s to decompress library", path.get());
    return nullptr;
  }
  AutoUnlinkFile file(path.release());
  if (stream->GetType() == Zip::Stream::DEFLATE) {
    if (ftruncate(fd, stream->GetUncompressedSize()) == -1) {
      ERROR("Couldn't ftruncate %s to decompress library", file.get());
      return nullptr;
    }
    /* Map the temporary file for use as inflate buffer */
    MappedPtr buffer(MemoryRange::mmap(nullptr, stream->GetUncompressedSize(),
                                       PROT_WRITE, MAP_SHARED, fd, 0));
    if (buffer == MAP_FAILED) {
      ERROR("Couldn't map %s to decompress library", file.get());
      return nullptr;
    }

    zxx_stream zStream = stream->GetZStream(buffer);

    /* Decompress */
    if (inflateInit2(&zStream, -MAX_WBITS) != Z_OK) {
      ERROR("inflateInit failed: %s", zStream.msg);
      return nullptr;
    }
    if (inflate(&zStream, Z_FINISH) != Z_STREAM_END) {
      ERROR("inflate failed: %s", zStream.msg);
      return nullptr;
    }
    if (inflateEnd(&zStream) != Z_OK) {
      ERROR("inflateEnd failed: %s", zStream.msg);
      return nullptr;
    }
    if (zStream.total_out != stream->GetUncompressedSize()) {
      ERROR("File not fully uncompressed! %ld / %d", zStream.total_out,
          static_cast<unsigned int>(stream->GetUncompressedSize()));
      return nullptr;
    }
  } else if (XZStream::IsXZ(stream->GetBuffer(), stream->GetSize())) {
    XZStream xzStream(stream->GetBuffer(), stream->GetSize());

    if (!xzStream.Init()) {
      ERROR("Couldn't initialize XZ decoder");
      return nullptr;
    }
    DEBUG_LOG("XZStream created, compressed=%" PRIuPTR
              ", uncompressed=%" PRIuPTR,
              xzStream.Size(), xzStream.UncompressedSize());

    if (ftruncate(fd, xzStream.UncompressedSize()) == -1) {
      ERROR("Couldn't ftruncate %s to decompress library", file.get());
      return nullptr;
    }
    MappedPtr buffer(MemoryRange::mmap(nullptr, xzStream.UncompressedSize(),
                                       PROT_WRITE, MAP_SHARED, fd, 0));
    if (buffer == MAP_FAILED) {
      ERROR("Couldn't map %s to decompress library", file.get());
      return nullptr;
    }
    const size_t written = xzStream.Decode(buffer, buffer.GetLength());
    DEBUG_LOG("XZStream decoded %" PRIuPTR, written);
    if (written != buffer.GetLength()) {
      ERROR("Error decoding XZ file %s", file.get());
      return nullptr;
    }
  } else if (stream->GetType() == Zip::Stream::STORE) {
    SeekableZStream zStream;
    if (!zStream.Init(stream->GetBuffer(), stream->GetSize())) {
      ERROR("Couldn't initialize SeekableZStream for %s", name);
      return nullptr;
    }
    if (ftruncate(fd, zStream.GetUncompressedSize()) == -1) {
      ERROR("Couldn't ftruncate %s to decompress library", file.get());
      return nullptr;
    }
    MappedPtr buffer(MemoryRange::mmap(nullptr, zStream.GetUncompressedSize(),
                                       PROT_WRITE, MAP_SHARED, fd, 0));
    if (buffer == MAP_FAILED) {
      ERROR("Couldn't map %s to decompress library", file.get());
      return nullptr;
    }

    if (!zStream.Decompress(buffer, 0, zStream.GetUncompressedSize())) {
      ERROR("%s: failed to decompress", name);
      return nullptr;
    }
  } else {
    return nullptr;
  }

  validator.CacheChecksum();
  return new MappableExtractFile(fd.forget(), file.release());
}