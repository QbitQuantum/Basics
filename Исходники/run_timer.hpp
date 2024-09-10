    void run_timer::report( system::error_code & ec )
    {
      m_reported = true;
      if ( m_format.empty() ) m_format = chrono_detail::default_format();

      process_times times;
      elapsed( times, ec );
      if (ec) return;

      if ( BOOST_CHRONO_IS_THROWS(ec) )
      {
        chrono_detail::show_time( times, m_format.c_str(), m_places, m_os );
      }
      else // non-throwing
      {
        try
        {
          chrono_detail::show_time( times, m_format.c_str(), m_places, m_os );
          if (!BOOST_CHRONO_IS_THROWS(ec)) 
          {
            ec.clear();
          }
        }

        catch (...) // eat any exceptions
        {
          BOOST_ASSERT( 0 && "error reporting not fully implemented yet" );
          if (BOOST_CHRONO_IS_THROWS(ec))
          {
              boost::throw_exception(
                      system::system_error( 
                              errno, 
                              BOOST_CHRONO_SYSTEM_CATEGORY, 
                              "chrono::run_timer" ));
          } 
          else
          {
            ec.assign(system::errc::success, BOOST_CHRONO_SYSTEM_CATEGORY);
          }
          }
      }
    }