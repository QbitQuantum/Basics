  void ntfsStrDump(const uint16_t* bytes, uint8_t length)
  {
    uint8_t i;

    for (i=0; i<length; i++)
    {
      if (bytes[i] > 255)
      {
        ntfsDebug(L"\nWarning: non printable character: 0x%04x \n",bytes[i]);
        continue;
      }

      putwc(bytes[i], stdout);
    }
  }