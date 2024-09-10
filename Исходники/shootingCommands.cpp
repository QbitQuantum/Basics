void
Controller::startSequence( ShotSeq *shotSeq )
{
    if( camera->handle() == 0 ) {
	doSeq = false;
	emit eventReport( new Event( Event::SequenceCancelledNoConnection ) );
	return;
    }

    if( (camera->getMirrorLockup() == 1) && !doLive ) {
	doSeq = false;
	emit eventReport( new Event( Event::SequenceCancelledMirrorLockup ) );
	return;
    }

    if( (shotSeq->type == ShotSeq::FocusBracketing) &&
        (camera->getEvfOutputDevice() == 0) ) {
	doSeq = false;
	emit eventReport( new Event( Event::SequenceCancelledNotEvfMode ) );
	return;
    }

    this->shotSeq = shotSeq;
    doSeq = true;

    emit eventReport( new Event( Event::SequenceInitiated, shotSeq->type ) );

    if( shotSeq->type == ShotSeq::ExposureBracketingManual ) {
	/*
	 *  Exposure bracketing in Manual shooting mode.
	 *  Keep aperture constant, adjust shutter speed.
	 */
	for( int i = 0; (i < shotSeq->frames) && doSeq; i++ ) {
	    setPropertyCommand( kEdsPropID_Tv, shotSeq->bracket[i] );
	    takePictureCommand();
	    QCoreApplication::processEvents();
	}
	// restore shutter speed to its original setting
	setPropertyCommand( kEdsPropID_Tv, shotSeq->bracket[0] );
    }
    else
    if( shotSeq->type == ShotSeq::ExposureBracketingAv ) {
	/*
	 *  Exposure bracketing in Av shooting mode.
	 *  Keep aperture constant, adjust shutter speed
	 *  by changing exposure compensation.
	 */
	for( int i = 0; (i < shotSeq->frames) && doSeq; i++ ) {
	    setPropertyCommand( kEdsPropID_ExposureCompensation,
		shotSeq->bracket[i] );
	    takePictureCommand();
	    QCoreApplication::processEvents();
	}
	// restore exposure compensation to its original setting
	setPropertyCommand( kEdsPropID_ExposureCompensation,
	    shotSeq->bracket[0] );
    }
    else
    if( shotSeq->type == ShotSeq::FocusBracketing ) {
	/*
	 *  Focus bracketing.
	 */
	//const int latency = 333;	// 100 is sufficient for USM lens
	const int latency = 3333;	// 100 is sufficient for USM lens
	for( int i = 0; (i < shotSeq->frames) && doSeq; i++ ) {
	    if( shotSeq->bracket[i] != 0 ) {
		focusAdjustment( shotSeq->bracket[i] );
	    }
	    Sleep( latency );
	    takePictureCommand();
	    /*
	     *  The camera becomes unstable if focus adjustments
	     *  are attempted while the shutter is open. This is
	     *  an inelegant but simple fix.
	     */
	    QApplication::setOverrideCursor( Qt::BusyCursor );
	    int l = Map::toShutterSpeed( camera->getTv() );
	    // break into 100 millisecond chunks
	    l = l/100;
	    for( int i = 0; i <= l; i++ ) {
		QCoreApplication::processEvents();
		Sleep( 100 );
	    }
	    QCoreApplication::processEvents();
	    QApplication::restoreOverrideCursor();
	}
    }
    else
    if( shotSeq->type == ShotSeq::Interval ) {
	/*
	 *  Interval shooting. Delay til first shot.
	 */
	QTimer::singleShot( shotSeq->delay, this, SLOT(firstShot()) );
    }
    else
    if( shotSeq->type == ShotSeq::Stitch ) {
	/*
	 *  Panorama shooting.
	 */
	doSeq = true;
    }
    else {
	doSeq = false;
	emit eventReport( new Event( Event::SequenceCancelled ) );
    }
}