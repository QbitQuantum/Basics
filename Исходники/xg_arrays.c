xint32 xi_arrays_bscan32(xint32 i) {
	DWORD idx = 0; // windows DWORD is always 32 bits.
	if (_BitScanForward(&idx, i)) {
		// windows index is from 0 (posix index from 1
		return idx+1;
	} else {
		return 0;
	}
}