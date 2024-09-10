 double getLocalTime(const Arguments& arguments, http::server::reply& reply)
 {
     return getLocalTime(getTimeStamp(arguments, reply));
 }