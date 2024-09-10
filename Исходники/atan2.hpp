 inline
 quan::angle::rad atan2(QUAN_FLOAT_TYPE const & lhs, QUAN_FLOAT_TYPE const & rhs)
 {
 #ifndef QUAN_AVR_NO_CPP_STDLIB
     using std::atan2;
 #else
     using ::atan2;
 #endif
     return quan::angle::rad {atan2(lhs, rhs)};
 }