	void WaveletStack3D::CreateSingleLayer(float* data)
	{
		if (1 > mStack.size())
		{
			mStack.resize(1, nullptr);
		}

		const size_t elem_cnt = static_cast<size_t>(mResX*mResY*mResZ);
		if (mStack[0] == nullptr) mStack[0] = new float[elem_cnt];

		Decompose(data, mBufferLowFreq, mBufferHighFreq, mBufferHalfSize, mResX, mResY, mResZ);

		// Save downsampled image to the stack
		memcpy(mStack[0], mBufferHighFreq, elem_cnt*sizeof(float));
	}