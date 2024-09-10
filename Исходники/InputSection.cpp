// Uncompress section contents if required. Note that this function
// is called from parallelForEach, so it must be thread-safe.
void InputSectionBase::maybeUncompress() {
  if (UncompressBuf || !Decompressor::isCompressedELFSection(Flags, Name))
    return;

  Decompressor Dec = check(Decompressor::create(Name, toStringRef(Data),
                                                Config->IsLE, Config->Is64));

  size_t Size = Dec.getDecompressedSize();
  UncompressBuf.reset(new char[Size]());
  if (Error E = Dec.decompress({UncompressBuf.get(), Size}))
    fatal(toString(this) +
          ": decompress failed: " + llvm::toString(std::move(E)));

  Data = makeArrayRef((uint8_t *)UncompressBuf.get(), Size);
  Flags &= ~(uint64_t)SHF_COMPRESSED;
}