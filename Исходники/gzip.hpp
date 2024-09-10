// Returns a gzip decompressed version of the provided string.
inline Try<std::string> decompress(const std::string& compressed)
{
  Decompressor decompressor;
  Try<std::string> decompressed = decompressor.decompress(compressed);

  // Ensure that the decompression stream does not expect more input.
  if (decompressed.isSome() && !decompressor.finished()) {
    return Error("More input is expected");
  }

  return decompressed;
}