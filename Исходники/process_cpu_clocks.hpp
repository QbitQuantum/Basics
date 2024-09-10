 process_system_cpu_clock::time_point process_system_cpu_clock::now(system::error_code & ec)
 {
   tms tm;
   clock_t c = ::times(&tm);
   if (c == clock_t(-1)) // error
   {
     if (BOOST_CHRONO_IS_THROWS(ec))
     {
       pdalboost::throw_exception(system::system_error(errno, BOOST_CHRONO_SYSTEM_CATEGORY, "chrono::process_system_cpu_clock"));
     } else
     {
       ec.assign(errno, BOOST_CHRONO_SYSTEM_CATEGORY);
       return time_point();
     }
   } else
   {
     long factor = chrono_detail::tick_factor();
     if (factor != -1)
     {
       if (!BOOST_CHRONO_IS_THROWS(ec))
       {
         ec.clear();
       }
       return time_point(nanoseconds((tm.tms_stime + tm.tms_cstime) * factor));
     } else
     {
       if (BOOST_CHRONO_IS_THROWS(ec))
       {
         pdalboost::throw_exception(system::system_error(errno, BOOST_CHRONO_SYSTEM_CATEGORY, "chrono::process_system_cpu_clock"));
       } else
       {
         ec.assign(errno, BOOST_CHRONO_SYSTEM_CATEGORY);
         return time_point();
       }
     }
   }
 }