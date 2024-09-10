	virtual void TearDown()
	{
		ae->shutdown();
		sc->shutdown();
		delete bc;
		delete cc;
		delete uc;
		delete crc;
		delete ae->getIAlicaClock();
	}