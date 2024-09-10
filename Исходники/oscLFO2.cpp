void audioCB(AudioIOData& io){

	while(io()){
	
		if(tmr()){
			if(cnt()){
				modMode ^= true;			// increment LFO type, switch mod mode when wraps
				printf("\nMod mode: %s modulation\n", modMode? "Amp" : "Freq");
			}
		}
			
		env.mod(mod.cosU());	// modulate modifier parameter with unipolar cosine wave

		float s = 0.f;			// initialize current sample to zero

		switch(cnt.val){			
				
			// non-modifiable generators ordered from smooth to sharp:
			case  0: s = env.cosU();	break;	// unipolar cosine
			case  1: s = env.hann();	break;	// a computed hann window (inverted cosU)
			case  2: s = env.triU();	break;	// unipolar triangle
			case  3: s = env.upU();		break;  // unipolar upward ramp
			case  4: s = env.downU();	break;  // unipolar downward ramp
			case  5: s = env.sqrU();	break;	// unipolar square

			// modifiable generator ordered from smooth to sharp:
			case  6: s = env.pulseU();	break;	// Mix between upward ramp and downward ramp
			case  7: s = env.stairU();	break;	// Mix between a square and impulse. 
			case  8: s = env.line2U();	break;	// Mix between a ramp and a triangle
			case  9: s = env.up2U();	break;  // Mix between two ramps			
		}
		
		if(modMode){			// amplitude modulate noise with envelope
			s *= noise();
		}
		else{					   // frequency modulate oscillator with envelope
			osc.freq(s*400 + 200); // between 100 and 200 hz
			s = osc.cos();
		}
		
		io.out(0) = io.out(1) = s*0.2;
	}
}