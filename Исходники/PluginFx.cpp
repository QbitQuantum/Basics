static float logsc(float param, const float min,const float max,const float rolloff = 19.0f) {
	return ((expf(param * logf(rolloff+1)) - 1.0f) / (rolloff)) * (max-min) + min;
}