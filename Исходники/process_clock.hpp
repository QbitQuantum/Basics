    void process_clock::now( process_times & times_, system::error_code & ec ) {

        tms tm;
        clock_t c = ::times( &tm );
        if ( c == clock_t(-1) ) // error
        {
            if (BOOST_CHRONO_IS_THROWS(ec))
            {
                boost::throw_exception(
                        system::system_error( 
                                errno, 
                                BOOST_CHRONO_SYSTEM_CATEGORY, 
                                "chrono::process_clock" ));
            }
            else
            {
                ec.assign( errno, BOOST_CHRONO_SYSTEM_CATEGORY );
                times_.real = times_.system = times_.user = nanoseconds(-1);
            }
        }
        else
        {
            times_.real = microseconds(c);
            times_.system = microseconds(tm.tms_stime + tm.tms_cstime);
            times_.user = microseconds(tm.tms_utime + tm.tms_cutime);
            if ( chrono_detail::tick_factor() != -1 )
            {
                if (!BOOST_CHRONO_IS_THROWS(ec)) 
                {
                  ec.clear();
                }
                times_.real *= chrono_detail::tick_factor();
                times_.user *= chrono_detail::tick_factor();
                times_.system *= chrono_detail::tick_factor();
            }
            else
            {
                if (BOOST_CHRONO_IS_THROWS(ec))
                {
                    boost::throw_exception(
                            system::system_error( 
                                    errno, 
                                    BOOST_CHRONO_SYSTEM_CATEGORY, 
                                    "chrono::process_clock" ));
                }
                else
                {
                    ec.assign( errno, BOOST_CHRONO_SYSTEM_CATEGORY );
                    times_.real = times_.user = times_.system = nanoseconds(-1);
                }
            }
        }

    }