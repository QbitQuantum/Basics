void W32AudioDriver::StopDriver() {
	if (waveOut_) {
	   waveOutReset(waveOut_) ;
    }

} ;