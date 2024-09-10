//-----------------------------------------------------------------------------
// updateMotion()
//-----------------------------------------------------------------------------
void LLMotionController::updateMotions(bool force_update)
{
	BOOL use_quantum = (mTimeStep != 0.f);

	// Always update mPrevTimerElapsed
	F32 cur_time = mTimer.getElapsedTimeF32();
	F32 delta_time = cur_time - mPrevTimerElapsed;
	mPrevTimerElapsed = cur_time;
	mLastTime = mAnimTime;

	// Always cap the number of loaded motions
	purgeExcessMotions();
	
	// Update timing info for this time step.
	if (!mPaused)
	{
		F32 update_time = mAnimTime + delta_time * mTimeFactor;
		if (use_quantum)
		{
			F32 time_interval = fmodf(update_time, mTimeStep);

            //<singu>
            // This old code is nonsense.
            //S32 quantum_count = llmax(0, ll_round((update_time - time_interval) / mTimeStep)) + 1;
            // (update_time - time_interval) / mTimeStep is an integer! We need ll_round to get rid of floating point errors, not llfloor.
            // Moreover, just rounding off to the nearest integer with ll_round(update_time / mTimeStep) makes a lot more sense:
            // it is the best we can do to get as close to what we should draw as possible.
            // However, mAnimTime may only be incremented; therefore make sure of that with the llmax.
			S32 quantum_count = llmax(ll_round(update_time / mTimeStep), llceil(mAnimTime / mTimeStep));
            //</singu>
			if (quantum_count == mTimeStepCount)
			{
				// we're still in same time quantum as before, so just interpolate and exit
				if (!mPaused)
				{
					F32 interp = time_interval / mTimeStep;
					mPoseBlender.interpolate(interp - mLastInterp);
					mLastInterp = interp;
				}

				updateLoadingMotions();

				return;
			}
			
			// is calculating a new keyframe pose, make sure the last one gets applied
			mPoseBlender.interpolate(1.f);
			clearBlenders();

			mTimeStepCount = quantum_count;
			// Singu note: mAnimTime may never be set back in time.
			// Despite the llmax/llceil above, (F32)quantum_count * mTimeStep can still
			// be a tiny bit smaller than mAnimTime due to floating point round off errors.
			mAnimTime = llmax(mAnimTime, (F32)quantum_count * mTimeStep);
			mLastInterp = 0.f;
		}
		else
		{
			// Singu note: mAnimTime may never be set back in time.
			mAnimTime = llmax(mAnimTime, update_time);
		}
	}

	updateLoadingMotions();

	resetJointSignatures();

	if (mPaused && !force_update)
	{
		updateIdleActiveMotions();
	}
	else
	{
		// update additive motions
		updateAdditiveMotions();
		resetJointSignatures();

		// update all regular motions
		updateRegularMotions();

		if (use_quantum)
		{
			mPoseBlender.blendAndCache(TRUE);
		}
		else
		{
			mPoseBlender.blendAndApply();
		}
	}

	mHasRunOnce = TRUE;
//	llinfos << "Motion controller time " << motionTimer.getElapsedTimeF32() << llendl;
}