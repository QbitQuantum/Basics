/*
 *
 * returns resolution in gl format (ResX + 'x' + ResY + ':' + Bpp)
 *
 */
void Graphic::resolution(char c[16]) {
	char c2[8];
	_itoa_s(Options::ResolutionX, c,16, 10);
	_itoa_s(Options::ResolutionY, c2,8, 10);
	strncat_s(c, 16, "x",1);
	strncat_s(c, 16, c2,4);
	strncat_s(c, 16, ":",1);
	strncat_s(c, 16, "32",2);
}