 static inline int run()
 {
   using std::ceil;
   using std::log;
   return cast<double,int>(ceil(-log(std::numeric_limits<double>::epsilon())
                                / log(10.0)));
 }