F32 Vec2fGetLenght(const Vec2f&  inVec2f) {
	F32 inVec2fxQ = inVec2f.x * inVec2f.x;
	F32 inVec2fyQ = inVec2f.y * inVec2f.y;
	return Sqrtf(inVec2fxQ + inVec2fyQ);
}