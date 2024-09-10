void audioCB(AudioIOData& io){

	while(io()){
		float s	= sineT1()
				+ sineT2.nextL()
				+ sineCS().i
				+ sineC1.cos()
				+ sineC2()
				+ sineRs()
		;

		s = s/6 - sin(sineC3.nextPhase());	// pass only the artifacts
		
		io.out(0) = io.out(1) = s * 0.2f;
	}

}