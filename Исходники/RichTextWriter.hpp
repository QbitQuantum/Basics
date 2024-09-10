    //////////////////////////////////////////////////////////////////////////////////////////
    // RtfWriter::setForeColour
    //! Sets the text colour
    //!
    //! \param[in] c - The colour
    //!
    //! \throw wtl::invalid_argument - Unrecognised colour
    //! \throw wtl::logic_error - [Debug only] Writer has been closed
    //! \throw wtl::domain_error - I/O error occurred
    //////////////////////////////////////////////////////////////////////////////////////////
    void   setForeColour(COLORREF c)
    {
      CHR buf[10];

      // Check stream is open
      if (Closed)
        throw wtl::logic_error(HERE, "Writer is closed");

      // Skip if colour already set
      if (ForeColour == c)
        return;

      // Lookup colour ID
      for (UINT id = 0; id < Colours.size(); id++)
        if (Colours[id] == c)
        {  // Write colour change
          StringCchPrintfA(buf, 10, "\\cf%d ", id + 1);
          writeString(buf);
          ForeColour = c;
          return;
        }

      // Unknown colour
      throw wtl::invalid_argument(HERE, "No such colour in the colour table");
    }