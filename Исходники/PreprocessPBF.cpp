  bool PreprocessPBF::GetPos(FILE* file,
                             FileOffset& pos) const
  {
#if defined(__WIN32__) || defined(WIN32)
    const __int64 filepos=_ftelli64(file);

    if (filepos==-1) {
      return false;
    }
    else {
      pos=(FileOffset)filepos;
    }
#elif defined(HAVE_FSEEKO)
    off_t filepos=ftello(file);

    if (filepos==-1) {
      return false;
    }
    else {
      pos=(FileOffset)filepos;
    }
#else
    long filepos=ftell(file);

    if (filepos==-1) {
      return false;
    }
    else {
      pos=(FileOffset)filepos;
    }
#endif

    return true;
  }