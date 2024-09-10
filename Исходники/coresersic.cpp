/**
 * The evaluation of the coresersic profile at coresersic coordinates (x,y).
 *
 * The coresersic profile has this form:
 *
 *    (1+(r/rb)^(-a))^(b/a)*
 *        exp(-bn*(((r^a+rb^a)/re^a))^(1/(nser*a)))
 *
 * with::
 *
 *           r = (x^{2+B} + y^{2+B})^{1/(2+B)}
 *           B = box parameter
 */
double CoreSersicProfile::evaluate_at(double x, double y) const {

	using std::abs;
	using std::exp;
	using std::pow;

	double box = this->box + 2.;
	double r = pow( pow(abs(x), box) + pow(abs(y), box), 1./box);
	return pow(1 + pow(r/rb,-a), b/a) *
	       exp(-_bn * pow((pow(r, a) + pow(rb, a))/pow(re,a), 1/(nser*a)));
}