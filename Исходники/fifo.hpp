    bool enqueue_try_nosync(ArenaT& arena, const T* entry)
    {
        const float* pSrc = (const float*)entry;
        float* pDst = (float*)&mCurBlock[mTail];

        auto lambda = [&](int32_t i)
        {
            __m256 vSrc = _mm256_load_ps(pSrc + i*KNOB_SIMD_WIDTH);
            _mm256_stream_ps(pDst + i*KNOB_SIMD_WIDTH, vSrc);
        };
            
        const uint32_t numSimdLines = sizeof(T) / (KNOB_SIMD_WIDTH*4);
        static_assert(numSimdLines * KNOB_SIMD_WIDTH * 4 == sizeof(T),
            "FIFO element size should be multiple of SIMD width.");

        UnrollerL<0, numSimdLines, 1>::step(lambda);

        mTail ++;
        if (mTail == mBlockSize)
        {
            if (++mCurBlockIdx < mBlocks.size())
            {
                mCurBlock = mBlocks[mCurBlockIdx];
            }
            else
            {
                T* newBlock = (T*)arena.AllocAligned(sizeof(T)*mBlockSize, KNOB_SIMD_WIDTH*4);
                SWR_ASSERT(newBlock);

                mBlocks.push_back(newBlock);
                mCurBlock = newBlock;
            }

            mTail = 0;
        }

        mNumEntries ++;
        return true;
    }