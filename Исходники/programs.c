static int custom_round(float v, int direction) {
	switch (direction) {
	case 0 :
		fesetround(FE_TOWARDZERO);
		break;
	case 1 :
		fesetround(FE_TONEAREST);
		break;
	case 2 :
		fesetround(FE_UPWARD);
		break;
	case 3 :
		fesetround(FE_DOWNWARD);
		break;
	}
	return nearbyintf(v);
}