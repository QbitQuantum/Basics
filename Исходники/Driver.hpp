    //! Read the contents of the MT SBD message buffer.
    //! @param[in] data buffer to hold binary data.
    //! @param[in] data_size size of binary data buffer.
    //! @return number of bytes read.
    unsigned
    readBufferMT(uint8_t* data, unsigned data_size)
    {
        ReadMode saved_read_mode = getReadMode();
        Counter<double> timer(getTimeout());
        uint8_t bfr[2] = {0};
        uint8_t ccsum[2] = {0};
        unsigned length = 0;

        try
        {
            // Prepare to read raw data.
            setReadMode(READ_MODE_RAW);

            // Send command.
            sendAT("+SBDRB");

            // Read incoming data length.
            length = getBufferSizeMT(timer);
            getTask()->spew("reading %u bytes of SBD binary data", length);

            // Read data.
            if (length > data_size)
                throw BufferTooSmall(data_size, length);

            if (length > 0)
            {
                readRaw(timer, data, length);
                computeChecksum(data, length, ccsum);
            }

            // Read and validate.
            readRaw(timer, bfr, 2);
            if ((bfr[0] != ccsum[0]) || (bfr[1] != ccsum[1]))
                throw Hardware::InvalidChecksum(bfr, ccsum);

            setReadMode(saved_read_mode);
            expectOK();
        }
        catch (...)
        {
            setReadMode(saved_read_mode);
            throw;
        }

        return length;
    }