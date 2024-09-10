  unsigned long
  StaticRangeCoder::encodeIntVectorToStream (std::vector<unsigned int>& inputIntVector_arg,
                                             std::ostream& outputByteStream_arg)
  {

    unsigned int inputsymbol;
    unsigned int i, f;
    char out;

    unsigned long frequencyTableSize;
    uint8_t frequencyTableByteSize;

    // define numerical limits
    const uint64_t top = (uint64_t)1 << 56;
    const uint64_t bottom = (uint64_t)1 << 48;
    const uint64_t maxRange = (uint64_t)1 << 48;

    unsigned long input_size = inputIntVector_arg.size ();
    uint64_t low, range;

    unsigned int inputSymbol;

    unsigned int readPos;

    unsigned long streamByteCount;

    streamByteCount = 0;

    // init output vector
    outputCharVector_.clear();
    outputCharVector_.reserve(sizeof(char) * input_size * 2);

    frequencyTableSize = 1;

    readPos = 0;

    // calculate frequency table
    cFreqTable_[0] = cFreqTable_[1] = 0;
    while (readPos < input_size)
    {
      inputSymbol = inputIntVector_arg[readPos++];

      if (inputSymbol + 1 >= frequencyTableSize)
      {
        // frequency table is to small -> adaptively extend it
        unsigned long oldfrequencyTableSize;
        oldfrequencyTableSize = frequencyTableSize;

        do
        {
          // increase frequency table size by factor 2
          frequencyTableSize <<= 1;
        } while (inputSymbol + 1 > frequencyTableSize);

        if (cFreqTable_.size () < frequencyTableSize + 1)
        {
          // resize frequency vector
          cFreqTable_.resize (frequencyTableSize + 1);
        }

        // init new frequency range with zero
        memset (&cFreqTable_[oldfrequencyTableSize + 1], 0,
                sizeof(uint64_t) * (frequencyTableSize - oldfrequencyTableSize));
      }
      cFreqTable_[inputSymbol + 1]++;
    }
    frequencyTableSize++;

    // convert to cumulative frequency table
    for (f = 1; f < frequencyTableSize; f++)
    {
      cFreqTable_[f] = cFreqTable_[f - 1] + cFreqTable_[f];
      if (cFreqTable_[f] <= cFreqTable_[f - 1])
        cFreqTable_[f] = cFreqTable_[f - 1] + 1;
    }

    // rescale if numerical limits are reached
    while (cFreqTable_[frequencyTableSize - 1] >= maxRange)
    {
      for (f = 1; f < cFreqTable_.size (); f++)
      {
        cFreqTable_[f] /= 2;
        ;
        if (cFreqTable_[f] <= cFreqTable_[f - 1])
          cFreqTable_[f] = cFreqTable_[f - 1] + 1;
      }
    }

    // calculate amount of bytes per frequeny table entry
    frequencyTableByteSize = (uint8_t)ceil (Log2 (cFreqTable_[frequencyTableSize - 1]) / 8.0);

    // write size of frequency table to output stream
    outputByteStream_arg.write ((const char *)&frequencyTableSize, sizeof(frequencyTableSize));
    outputByteStream_arg.write ((const char *)&frequencyTableByteSize, sizeof(frequencyTableByteSize));

    streamByteCount += sizeof(frequencyTableSize)+sizeof(frequencyTableByteSize);

    // write cumulative  frequency table to output stream
    for (f = 1; f < frequencyTableSize; f++)
    {
      outputByteStream_arg.write ((const char *)&cFreqTable_[f], frequencyTableByteSize);
      streamByteCount += frequencyTableByteSize;
    }

    readPos = 0;
    low = 0;
    range = (uint64_t)-1;

    // start encoding
    while (readPos < input_size)
    {

      // read symol
      inputsymbol = inputIntVector_arg[readPos++];

      // map to range
      low += cFreqTable_[inputsymbol] * (range /= cFreqTable_[frequencyTableSize - 1]);
      range *= cFreqTable_[inputsymbol + 1] - cFreqTable_[inputsymbol];

      // check range limits
      while ((low ^ (low + range)) < top || ((range < bottom) && ((range = -low & (bottom - 1)), 1)))
      {
        out = low >> 56;
        range <<= 8;
        low <<= 8;
        outputCharVector_.push_back(out);
      }

    }

    // flush remaining data
    for (i = 0; i < 8; i++)
    {
      out = low >> 56;
      outputCharVector_.push_back(out);
      low <<= 8;
    }

    // write encoded data to stream
    outputByteStream_arg.write (&outputCharVector_[0], outputCharVector_.size());

    streamByteCount += outputCharVector_.size();

    return streamByteCount;

  }