float TVA::nextAmp() {
	// FIXME: This whole method is based on guesswork
	Bit32u target = la32TargetAmp * TVA_TARGET_AMP_MULT;
	if (la32AmpIncrement == 0) {
		currentAmp = target;
	} else {
		if ((la32AmpIncrement & 0x80) != 0) {
			// Lowering amp
			if (largeAmpInc > currentAmp) {
				currentAmp = target;
				nextPhase();
			} else {
				currentAmp -= largeAmpInc;
				if (currentAmp <= target) {
					currentAmp = target;
					nextPhase();
				}
			}
		} else {
			// Raising amp
			if (MAX_CURRENT_AMP - currentAmp < largeAmpInc) {
				currentAmp = target;
				nextPhase();
			} else {
				currentAmp += largeAmpInc;
				if (currentAmp >= target) {
					currentAmp = target;
					nextPhase();
				}
			}
		}
	}
	// FIXME:KG: Note that the "65536.0f" here is slightly arbitrary, and needs to be confirmed. 32768.0f is more likely.
	// FIXME:KG: We should perhaps use something faster once we've got the details sorted out, but the real synth's amp level changes pretty smoothly.
	return EXP2F((float)currentAmp / TVA_TARGET_AMP_MULT / 16.0f - 1.0f) / 65536.0f;
}