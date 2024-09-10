  std::pair<char*, size_t> LZ4RunReader::next()
  {
    // Is there a complete key in the buffer?
    if( decomp_.fill() >= sizeof(size_t) &&
        decomp_.fill() >= (sizeof(size_t) + next_size()) )
    {
      auto ret = std::make_pair(decomp_.base() + decomp_.lo() + sizeof(size_t),
                                next_size());

      decomp_.advance_lo(ret.second + sizeof(size_t));

      return ret;
    }
    // No key. Did we hit eof?
    else if( eof_ )
    {
      if( decomp_.fill() )
      {
        WARNING("Run file had " << decomp_.fill() << " extraneous bytes at end");
      }

      if( comp_.fill() )
      {
        WARNING("Run file consumed with " << comp_.fill() << " compressed"
                " bytes remaining");
      }

      return std::pair<char*, size_t>(nullptr, 0);
    }
    // We need some more data
    else
    {
      // Fill buffer until we have hit the trigger point, and we have a
      // a complete key
      while( !eof_ &&
             ( decomp_.fill() < trigger_ || 
               decomp_.fill() < (sizeof(size_t) + next_size()) ) )
      {
        // First try to decompress that which we have
        if( comp_.fill() )
        {
          decompress();

          // Skip read if we got enough data
          if( decomp_.fill() >= trigger_ && 
              decomp_.fill() >= (sizeof(size_t) + next_size()) )
          {
            continue;
          }
        }

        if( poll(fds_, 1, -1) < 0 )
        {
          WARNING("poll() failed, input may have terminated prematurely.");
          eof_ = true;
        }

        // Read into the compressed buffer
        int bytes_read = read(fds_[0].fd, comp_.base() + comp_.hi(),
                                          comp_.size() - comp_.fill());

        if( bytes_read <= 0 )
        {
          eof_ = true;

          if( bytes_read < 0 )
          {
            WARNING("read() failed, input may have terminated prematurely.");
          }
        }
        else
        {
          comp_.advance_hi(bytes_read);
          decompress();
        }
      }

      // Warn if eof without a complete key
      if( eof_ && ( decomp_.fill() < sizeof(size_t) ||
                    decomp_.fill() < (sizeof(size_t) + next_size()) ) )
      {
        WARNING("Run file had " << decomp_.fill() << " extraneous bytes at end");
        return std::pair<char*, size_t>(nullptr, 0);
      }
      
      // We now have at least one key in the buffer. Return the first.
      auto ret = std::make_pair(decomp_.base() + decomp_.lo() + sizeof(size_t),
                                next_size());

      decomp_.advance_lo(ret.second + sizeof(size_t));

      return ret;
    }
  }