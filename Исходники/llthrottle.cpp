BOOL LLThrottleGroup::dynamicAdjust()
{
	const F32 DYNAMIC_ADJUST_TIME = 1.0f;		// seconds
	const F32 CURRENT_PERIOD_WEIGHT = .25f;		// how much weight to give to last period while determining BPS utilization
	const F32 BUSY_PERCENT = 0.75f;		// if use more than this fraction of BPS, you are busy
	const F32 IDLE_PERCENT = 0.70f;		// if use less than this fraction, you are "idle"
	const F32 TRANSFER_PERCENT = 0.90f;	// how much unused bandwidth to take away each adjustment
	const F32 RECOVER_PERCENT = 0.25f;	// how much to give back during recovery phase

	S32 i;

	F64 mt_sec = LLMessageSystem::getMessageTimeSeconds();

	// Only dynamically adjust every few seconds
	if ((mt_sec - mDynamicAdjustTime) < DYNAMIC_ADJUST_TIME)
	{
		return FALSE;
	}
	mDynamicAdjustTime = mt_sec;

	S32 total = 0;
	// Update historical information
	for (i = 0; i < TC_EOF; i++)
	{
		if (mBitsSentHistory[i] == 0)
		{
			// first run, just copy current period
			mBitsSentHistory[i] = mBitsSentThisPeriod[i];
		}
		else
		{
			// have some history, so weight accordingly
			mBitsSentHistory[i] = (1.f - CURRENT_PERIOD_WEIGHT) * mBitsSentHistory[i] 
				+ CURRENT_PERIOD_WEIGHT * mBitsSentThisPeriod[i];
		}

		mBitsSentThisPeriod[i] = 0;
		total += llround(mBitsSentHistory[i]);
	}

	// Look for busy channels
	// TODO: Fold into loop above.
	BOOL channels_busy = FALSE;
	F32  busy_nominal_sum = 0;
	BOOL channel_busy[TC_EOF];
	BOOL channel_idle[TC_EOF];
	BOOL channel_over_nominal[TC_EOF];

	for (i = 0; i < TC_EOF; i++)
	{
		// Is this a busy channel?
		if (mBitsSentHistory[i] >= BUSY_PERCENT * DYNAMIC_ADJUST_TIME * mCurrentBPS[i])
		{
			// this channel is busy
			channels_busy = TRUE;
			busy_nominal_sum += mNominalBPS[i];		// use for allocation of pooled idle bandwidth
			channel_busy[i] = TRUE;
		}
		else
		{
			channel_busy[i] = FALSE;
		}

		// Is this an idle channel?
		if ((mBitsSentHistory[i] < IDLE_PERCENT * DYNAMIC_ADJUST_TIME * mCurrentBPS[i]) &&
			(mBitsAvailable[i] > 0))
		{
			channel_idle[i] = TRUE;
		}
		else
		{
			channel_idle[i] = FALSE;
		}

		// Is this an overpumped channel?
		if (mCurrentBPS[i] > mNominalBPS[i])
		{
			channel_over_nominal[i] = TRUE;
		}
		else
		{
			channel_over_nominal[i] = FALSE;
		}

		//if (total)
		//{
		//	llinfos << i << ": B" << channel_busy[i] << " I" << channel_idle[i] << " N" << channel_over_nominal[i];
		//	llcont << " Nom: " << mNominalBPS[i] << " Cur: " << mCurrentBPS[i] << " BS: " << mBitsSentHistory[i] << llendl;
		//}
	}

	if (channels_busy)
	{
		// Some channels are busy.  Let's see if we can get them some bandwidth.
		F32 used_bps;
		F32 avail_bps;
		F32 transfer_bps;

		F32 pool_bps = 0;

		for (i = 0; i < TC_EOF; i++)
		{
			if (channel_idle[i] || channel_over_nominal[i] )
			{
				// Either channel i is idle, or has been overpumped.
				// Therefore it's a candidate to give up some bandwidth.
				// Figure out how much bandwidth it has been using, and how
				// much is available to steal.
				used_bps = mBitsSentHistory[i] / DYNAMIC_ADJUST_TIME;

				// CRO make sure to keep a minimum amount of throttle available
				// CRO NB: channels set to < MINIMUM_BPS will never give up bps, 
				// which is correct I think
				if (used_bps < gThrottleMinimumBPS[i])
				{
					used_bps = gThrottleMinimumBPS[i];
				}

				if (channel_over_nominal[i])
				{
					F32 unused_current = mCurrentBPS[i] - used_bps;
					avail_bps = llmax(mCurrentBPS[i] - mNominalBPS[i], unused_current);
				}
				else
				{
					avail_bps = mCurrentBPS[i] - used_bps;
				}

				//llinfos << i << " avail " << avail_bps << llendl;

				// Historically, a channel could have used more than its current share,
				// even if it's idle right now.
				// Make sure we don't steal too much.
				if (avail_bps < 0)
				{
					continue;
				}

				// Transfer some bandwidth from this channel into the global pool.
				transfer_bps = avail_bps * TRANSFER_PERCENT;
				mCurrentBPS[i] -= transfer_bps;
				pool_bps += transfer_bps;
			}
		}

		//llinfos << "Pool BPS: " << pool_bps << llendl;
		// Now redistribute the bandwidth to busy channels.
		F32 unused_bps = 0.f;

		for (i = 0; i < TC_EOF; i++)
		{
			if (channel_busy[i])
			{
				F32 add_amount = pool_bps * (mNominalBPS[i] / busy_nominal_sum);
				//llinfos << "Busy " << i << " gets " << pool_bps << llendl;
				mCurrentBPS[i] += add_amount;

				// CRO: make sure this doesn't get too huge
				// JC - Actually, need to let mCurrentBPS go less than nominal, otherwise
				// you aren't allowing bandwidth to actually be moved from one channel
				// to another.  
				// *TODO: If clamping high end, would be good to re-
				// allocate to other channels in the above code.
				const F32 MAX_BPS = 4 * mNominalBPS[i];
				if (mCurrentBPS[i] > MAX_BPS)
				{
					F32 overage = mCurrentBPS[i] - MAX_BPS;
					mCurrentBPS[i] -= overage;
					unused_bps += overage;
				}

				// Paranoia
				if (mCurrentBPS[i] < gThrottleMinimumBPS[i])
				{
					mCurrentBPS[i] = gThrottleMinimumBPS[i];
				}
			}
		}

		// For fun, add the overage back in to objects
		if (unused_bps > 0.f)
		{
			mCurrentBPS[TC_TASK] += unused_bps;
		}
	}
	else
	{
		// No one is busy.
		// Make the channel allocations seek toward nominal.

		// Look for overpumped channels
		F32 starved_nominal_sum = 0;
		F32 avail_bps = 0;
		F32 transfer_bps = 0;
		F32 pool_bps = 0;
		for (i = 0; i < TC_EOF; i++)
		{
			if (mCurrentBPS[i] > mNominalBPS[i])
			{
				avail_bps = (mCurrentBPS[i] - mNominalBPS[i]);
				transfer_bps = avail_bps * RECOVER_PERCENT;

				mCurrentBPS[i] -= transfer_bps;
				pool_bps += transfer_bps;
			}
		}

		// Evenly distribute bandwidth to channels currently
		// using less than nominal.
		for (i = 0; i < TC_EOF; i++)
		{
			if (mCurrentBPS[i] < mNominalBPS[i])
			{
				// We're going to weight allocations by nominal BPS.
				starved_nominal_sum += mNominalBPS[i];
			}
		}

		for (i = 0; i < TC_EOF; i++)
		{
			if (mCurrentBPS[i] < mNominalBPS[i])
			{
				// Distribute bandwidth according to nominal allocation ratios.
				mCurrentBPS[i] += pool_bps * (mNominalBPS[i] / starved_nominal_sum);
			}
		}
	}
	return TRUE;
}