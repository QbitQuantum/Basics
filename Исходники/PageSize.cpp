/** Computes width and height of ISO/DIN An.
 *  @param[in]  n the A level (e.g. n=4 => DIN A4)
 *  @param[out] width contains the page width when function returns
 *  @param[out] height contains the page height when function returns */
static void computeASize (int n, Length &width, Length &height) {
	height.set(floor(1189.0/pow(math::SQRT2, n)+0.5), Length::Unit::MM);
	width.set(floor(height.mm()/math::SQRT2+0.5), Length::Unit::MM);
}