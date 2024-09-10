	virtual void TearDown()
	{
		ae->shutdown();
		ae2->shutdown();
		delete cace;
		delete ae->getCommunicator();
		delete cace2;
		delete ae2->getCommunicator();
		delete ae->getIAlicaClock();
		delete ae2->getIAlicaClock();
		sc->shutdown();
		delete cc;
		delete bc;
		delete uc;
		delete crc;
	}