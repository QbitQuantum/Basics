void QMidiOut::disconnect()
{
	if (!fConnected) {
		return;
	}

	midiOutClose(fMidiPtrs->midiOutPtr);

	delete fMidiPtrs;
	fMidiPtrs = NULL;
	fConnected = false;
    qDebug() << "DC";
}