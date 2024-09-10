double IMCSEngine::getTimingResult(const double tStart) {
	return (((double)getTickCount() - tStart) / getTickFrequency()) * 1000;			//Calculate execution time in milliseconds relative to tStart
}