// FileIO_Std::Tell()
off_t FileIO_Std::Tell() {
#ifdef _MSC_VER
	return _ftelli64(fp_);
#else
  return ftello(fp_);
#endif
}