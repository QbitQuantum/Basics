 future_error(boost::system::error_code ec)
 : logic_error(ec.message())
 , ec_(ec)
 {}