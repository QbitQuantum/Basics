void DRMReceiver::run()
{
//	QElapsedTimer Timer;
	m_run = true;
	m_stopAck = false;
	CVector<short> tmpSnd(BufferSize);
	while(m_run)
	{
		if(fromFile)
		{
//			Timer.start();
			fRead(tmpSnd);
			for(int i = 0; i < SAMPLINGSTRIPE; i++)
			{
				tempBuf[i] = tmpSnd.at(i);
			}
		}
		else
		{
//			Timer.start();
			pSoundInInterface->Read(tmpSnd);
			for(int i = 0; i < SAMPLINGSTRIPE; i++)
			{
				tempBuf[i] = tmpSnd.at(i * 2) * 2.5f;
			}
		}
//		qDebug() << "Time" << Timer.elapsed();
//		qDebug() << __FILE__ << __LINE__ << "tempBuf" << tempBuf[SAMPLINGSTRIPE / 2];
		runDRM();

		Io_Led = Qt::green;
	}
	if(fromFile)
	{
		sf_close(sfin);
		tmpSnd.clear();
		qDebug() << __FILE__ << __LINE__ << "sf_close(sfin)";
	}
	// do NOT close pSoundInInterface
//	pSoundInInterface->Close();
	m_stopAck = true;
//	qDebug() << __FILE__ << __LINE__;
}