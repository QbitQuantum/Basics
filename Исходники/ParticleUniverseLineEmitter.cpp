	//-----------------------------------------------------------------------
	void LineEmitter::_notifyRescaled(const Ogre::Vector3& scale)
	{
		// Scale the internal attributes and use them, otherwise this results in too many calculations per particle
		ParticleEmitter::_notifyRescaled(scale);
		Ogre::Real scaleLength = scale.length();
		_mScaledEnd = mEnd * scale;
		_mScaledMaxDeviation = mMaxDeviation * scaleLength;
		_mScaledMinIncrement = mMinIncrement * scaleLength;
		_mScaledMaxIncrement = (mMaxIncrement - mMinIncrement) * scaleLength;
		_mScaledLength = _mScaledEnd.length();
	}