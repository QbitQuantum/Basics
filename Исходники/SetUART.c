void sub_putH(unsigned char byte) {
	if (byte > 9) putC(byte + ('A'-10));
	else putC(byte + '0');
}