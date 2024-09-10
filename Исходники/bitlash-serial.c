void chkpin(char pin) {
	// TODO: fix this warning re: comparison
	if ((pin >= NUMPINS) || (pin < 0)) unexpected(M_number); 
}