EulerAngles::EulerAngles(const Dcm &dcm) :
	Vector(3)
{
	setTheta(asinf(-dcm(2, 0)));

	if (fabsf(getTheta() - M_PI_2_F) < 1.0e-3f) {
		setPhi(0.0f);
		setPsi(atan2f(dcm(1, 2) - dcm(0, 1),
			      dcm(0, 2) + dcm(1, 1)) + getPhi());

	} else if (fabsf(getTheta() + M_PI_2_F) < 1.0e-3f) {
		setPhi(0.0f);
		setPsi(atan2f(dcm(1, 2) - dcm(0, 1),
			      dcm(0, 2) + dcm(1, 1)) - getPhi());

	} else {
		setPhi(atan2f(dcm(2, 1), dcm(2, 2)));
		setPsi(atan2f(dcm(1, 0), dcm(0, 0)));
	}
}