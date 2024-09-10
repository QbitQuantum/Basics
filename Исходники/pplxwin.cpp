 _PPLXIMP critical_section_impl::~critical_section_impl()
 {
     DeleteCriticalSection(reinterpret_cast<LPCRITICAL_SECTION>(&_M_impl));
 }