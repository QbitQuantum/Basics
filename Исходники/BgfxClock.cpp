		Time BgfxClock::GetElapsedTime()
		{
			const double Freq = double( bx::getHPFrequency() );
			const double ToMs = 1000.0 / Freq;
			return Time( bx::getHPCounter() * ToMs * 0.001f );
		}