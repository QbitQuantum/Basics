	virtual void Realize(DrawContext& drawContext)
	{
		if (mRealizedFrame == drawContext.GetFrameStamp()
			|| 0 == mCount)
		{
			return;
		}
		else if (INIT_FRAME_STAMP == mRealizedFrame)
		{
			mPositionStream.Release();
			mColorStream.Release();
			mRawDataBuffers.removeAll();
			mStreamOutBuffers.removeAll();
			mParticleBuffers.removeAll();
			mPositionStream.Initialize(sizeof(Point3));
			mPositionStream.SetBufferUsageType(BufferUsageStatic);
			mPositionStream.SetNumberOfVertices(mCount);
			float* pPosBuffer = (float*)(mPositionStream.Lock(0, 0));
			for (int i = 0; i < mCount; ++i)
			{
				pPosBuffer[0] = (float)rand() / RAND_MAX * mRadius; //radius
				pPosBuffer[1] = (float)rand() / RAND_MAX * 6.28f; //init rad
				pPosBuffer[2] = pPosBuffer[0] / mRadius * (3.1415926f / 8.0f) ; //rad speed
				pPosBuffer += 3;
			}
			mPositionStream.Unlock();

			mColorStream.Initialize(sizeof(DWORD));
			mColorStream.SetBufferUsageType(BufferUsageStatic);
			mColorStream.SetNumberOfVertices(mCount);
			DWORD* dwColor = (DWORD*)mColorStream.Lock(0, 0);
			for (int i = 0; i < mCount; ++i)
			{
				int r = (float)rand() / RAND_MAX * 255;
				int g = (float)rand() / RAND_MAX * 255;
				int b = (float)rand() / RAND_MAX * 255;
				*dwColor = COLOR_ARGB(255, r, g, b);
				++dwColor;
			}
			mColorStream.Unlock();

			mStreamOutData.Initialize(sizeof(Point4) + sizeof(Point3));
			mStreamOutData.SetNumberOfVertices(mCount);
			mStreamOutData.SetBufferUsageType(BufferUsageStreamOut);

			mRawDataBuffers.append(mPositionStream);
			mRawDataBuffers.append(mColorStream);

			mStreamOutBuffers.append(mStreamOutData);

			mParticleBuffers.append(mQuad);
			mParticleBuffers.append(mStreamOutData);
		}
		mRealizedFrame = drawContext.GetFrameStamp();
		IVirtualDevice& vd = drawContext.GetVirtualDevice();
		DepthStencilState depthBack = vd.GetDepthStencilState();

		vd.SetDepthStencilState(mDepthState);
		
		mMotionShader.Activate(drawContext);
		mMotionShader.ActivatePass(drawContext, 0);
		vd.SetStreamFormat(mMotionFormat);
		vd.SetIndexBuffer(nullptr);
		vd.SetVertexStreams(mRawDataBuffers);
		vd.SetOutputStreams(&mStreamOutBuffers);
		vd.Draw(PrimitivePointList, 0, (int)mCount);
		vd.SetOutputStreams(nullptr);
		mMotionShader.PassesFinished(drawContext);
		mMotionShader.Terminate();
		vd.SetDepthStencilState(depthBack);
	}