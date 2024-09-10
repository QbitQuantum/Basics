void MyTriangle::calcTextCoords() {

	float base1 = sqrtf(exp2(x2 - x1) + exp2(y2 - y1) + exp2(z2 - z1));
	float hipot = sqrtf(exp2(x3 - x1) + exp2(y3 - y1) + exp2(z3 - z1));
	float teta = acos((x1 * x2 + y1 * y2 + z1 * z2) / (base1 * hipot));
	float base2 = hipot * cos(teta);
	float hight = sqrt(exp2(hipot) - exp2f(base2));
	float deltas1 = base1 / getAppearance()->getSWrap();
	float deltas2 = base2 / getAppearance()->getSWrap();
	float deltat = hight / getAppearance()->getTWrap();

	text_coords[0][0] = 0.0;
	text_coords[0][1] = 0.0;
	text_coords[1][0] = deltas1;
	text_coords[1][1] = 0.0;
	text_coords[2][0] = deltas2;
	text_coords[2][1] = deltat;
}