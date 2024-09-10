// Call this function as soon as possible. Basically should be at the moment you
// jump into your C/C++ kernel. But keep in mind that kernel is not yet initialized,
// and you can't use a lot of stuff in your constructors!
bool CallConstructors() {
	// Do C initialization
	int initret = _initterm_e(__xi_a, __xi_z);
	if (initret != 0) {
		return false;
	}

	// Do C++ initialization
	_initterm(__xc_a, __xc_z);
	return true;
}