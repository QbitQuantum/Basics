void ImageTile::SetWindows(long double variance, bool convolve) {
	bool methodA = false;
	bool methodB = false;
	bool methodC = true;

	// Unwindow everything
	for(unsigned channel = 0;channel<_channelCount;++channel) {
		for(unsigned scan = 0;scan<_scanCount;++scan)
			_isWindowed[channel][scan] = false;
	}

	if(methodA) {
		// Window everything higher than trigger * sigma
		for(unsigned channel = 0;channel<_channelCount;++channel) {
			for(unsigned scan = 0;scan<_scanCount;++scan) {
				if(fabsl(GetValueAt(channel, scan) - EvaluateBaselineFunction(scan, channel)) > _trigger * variance) {
					Window(scan, channel);
				}
			}
		}
	}
	if(methodB) {
		for(unsigned channel = 0;channel<_channelCount;++channel) {
			for(unsigned scan = 0;scan<_scanCount;++scan) {
				bool triggered =
					TriggeredRaise(channel, scan, channel-1, scan-1, variance) ||
					TriggeredRaise(channel, scan, channel-1, scan+1, variance) ||
					TriggeredRaise(channel, scan, channel+1, scan-1, variance) ||
					TriggeredRaise(channel, scan, channel+1, scan+1, variance);
				if(triggered)
					Window(scan, channel);
			}
		}
	}
	if(convolve)
		ConvolveWindows();
	if(methodC) {
		LineThreshold(true, 0.0, variance, convolve);
	}
}