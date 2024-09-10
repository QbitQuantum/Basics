			~inAudioCapture()
			{
				#if WRITEWAVE
				finishWaveFile();
				#endif
				waveInStop(hWaveIn);
				std::cout << "Stop Recording.\n" << std::endl;
				waveInClose(hWaveIn);
				if(!dataIn) delete [] dataIn;
				
			}