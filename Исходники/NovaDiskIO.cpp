	NovaDiskOut()
	{
		mChannelCount = in0(0);

		const int indexOfPathSize  = 1 + mChannelCount;
		const int indexOfPathStart = 2 + mChannelCount;
		const int pathSize  = (int)in0(indexOfPathSize);
		char path[16384];

		nova::loop(pathSize, [&](int index) {
			path[index] = (char)in0(indexOfPathStart + index);
		});

		mTicket = gThread->openFile(path, mChannelCount, (int)sampleRate());
		if (mTicket == -1) {
			Print("Cannot open file %s\n", path);
			mCalcFunc = ft->fClearUnitOutputs;
			return;
		}

		mCalcFunc = make_calc_function<NovaDiskOut, &NovaDiskOut::next>();
	}