  steady_clock::time_point steady_clock::now(system::error_code & ec)
  {
    timespec ts;
    if ( ::clock_gettime( CLOCK_MONOTONIC, &ts ) )
    {
        if (BOOST_CHRONO_IS_THROWS(ec))
        {
            boost::throw_exception(
                    system::system_error( 
                            errno, 
                            BOOST_CHRONO_SYSTEM_CATEGORY, 
                            "chrono::steady_clock" ));
        }
        else
        {
            ec.assign( errno, BOOST_CHRONO_SYSTEM_CATEGORY );
            return time_point();
        }
    }

    if (!BOOST_CHRONO_IS_THROWS(ec)) 
    {
        ec.clear();
    }
    return time_point(duration(
      static_cast<steady_clock::rep>( ts.tv_sec ) * 1000000000 + ts.tv_nsec));
  }