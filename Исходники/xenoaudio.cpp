void XenoAudio::SetChannelPos(int i)
{
	if (!audioOn) return;

	if (sounds[i].pos.IsZero()) {
		Mix_SetPosition(i, 0, 0);
	}
	else {
		Vector3F delta = sounds[i].pos - listenerPos;
		float len = delta.Length();
		float df = len / MAX_DISTANCE;
		int d = LRintf(df*255.0f);
		d = Clamp(d, 0, 255);

		if (delta.LengthSquared() > 0.001f) {
			delta.Normalize();
		}
		else {
			delta.Set(0, 0, -1);
		}

		static const Vector3F UP = { 0, 1, 0 };
		Vector3F listenerRight = CrossProduct(listenerDir, UP);

		float dotFront = DotProduct(delta, listenerDir);
		float dotRight = DotProduct(delta, listenerRight);

		// 0 is north, 90 is east, etc. WTF.
		float rad = atan2(dotRight, dotFront);
		float deg = rad * 180.0f / PI;
		int degi = int(deg);
		if (degi < 0) degi += 360;

		int result = Mix_SetPosition(i, degi, d);
		GLASSERT(result != 0);
		(void)result;
	}
}