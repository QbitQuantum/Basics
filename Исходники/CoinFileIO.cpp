  virtual char *gets (char *buffer, int size) override
  {
    if (size <= 1)
      return 0;

    char *dest = buffer;
    char *destLast = dest + size - 2; // last position allowed to be written

    bool initiallyEmpty = (dataStart_ == dataEnd_);

    for (;;)
      {
	// refill dataBuffer if needed
	if (dataStart_ == dataEnd_)
	  {
	    dataStart_ = dataEnd_ = &dataBuffer_[0];
	    int count = readRaw (dataStart_, static_cast<int>(dataBuffer_.size ()));

	    // at EOF?
	    if (count <= 0)
	      {
		*dest = 0;
		// if it was initially empty we had nothing written and should
		// return 0, otherwise at least the buffer contents were
		// transfered and buffer has to be returned.
		return initiallyEmpty ? 0 : buffer;
	      }

	    dataEnd_ = dataStart_ + count;
	  }

	// copy character from buffer
	*dest = *dataStart_++;

	// terminate, if character was \n or bufferEnd was reached
	if (*dest == '\n' || dest == destLast)
	  {
	    *++dest = 0;
	    return buffer;
	  }

	++dest;
      }

    // we should never reach this place
    throw CoinError ("Reached unreachable code!",
		     "gets",
		     "CoinGetslessFileInput");
  }