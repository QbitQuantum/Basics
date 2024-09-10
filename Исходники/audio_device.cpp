void SoundStream::init(const FilePath& path) {
  CHECK(ov_fopen(path.getPath(), file.get()) == 0) << "Error opening audio file: " << path;
  info = ov_info(file.get(), -1);
  AL(alGenBuffers(2, buffers));
}