 inline boost::filesystem::path program_location_impl(boost::system::error_code& ec) {
     ec.clear();
     return boost::filesystem::path(getexecname());
 }