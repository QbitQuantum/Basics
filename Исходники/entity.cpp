void CEntity::addTransformation (CMatrix &current, UAnimation *anim, float begin, float end, UTrack *posTrack, UTrack *rotquatTrack, 
									   UTrack *nextPosTrack, UTrack *nextRotquatTrack, bool removeLast)
{
	// In place ?
	if (_inPlace)
	{
		// Just identity
		current.identity();
	}
	else
	{
		// Remove the start of the animation
		CQuat rotEnd (0,0,0,1);
		CVector posEnd (0,0,0);
		if (rotquatTrack)
		{
			// Interpolate the rotation
			rotquatTrack->interpolate (end, rotEnd);
		}
		if (posTrack)
		{
			// Interpolate the position
			posTrack->interpolate (end, posEnd);
		}

		// Add the final rotation and position
		CMatrix tmp;
		tmp.identity ();
		tmp.setRot (rotEnd);
		tmp.setPos (posEnd);

		// Incremental ?
		if (_incPos)
			current *= tmp;
		else
			current = tmp;

		if (removeLast)
		{
			CQuat rotStart (0,0,0,1);
			CVector posStart (0,0,0);
			if (nextRotquatTrack)
			{
				// Interpolate the rotation
				nextRotquatTrack->interpolate (begin, rotStart);
			}
			if (nextPosTrack)
			{
				// Interpolate the position
				nextPosTrack->interpolate (begin, posStart);
			}
			// Remove the init rotation and position of the next animation
			tmp.identity ();
			tmp.setRot (rotStart);
			tmp.setPos (posStart);
			tmp.invert ();
			current *= tmp;

			// Normalize the mt
			CVector I = current.getI ();
			CVector J = current.getJ ();
			I.z = 0;
			J.z = 0;
			J.normalize ();
			CVector K = I^J;
			K.normalize ();
			I = J^K;
			I.normalize ();
			tmp.setRot (I, J, K);
			tmp.setPos (current.getPos ());
			current = tmp;
		}
	}
}