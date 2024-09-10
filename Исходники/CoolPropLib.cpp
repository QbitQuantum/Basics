 ~fpu_reset_guard() {
 #if defined(_MSC_VER)
     _clearfp(); // For MSVC, clear the floating point error flags
 #elif defined(FE_ALL_EXCEPT)
     feclearexcept(FE_ALL_EXCEPT);
 #endif
 }