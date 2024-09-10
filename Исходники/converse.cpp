void SequenceManager::synchronize(Serializer &s) {
	if (s.getVersion() >= 2)
		Action::synchronize(s);

	s.syncAsSint32LE(_resNum);
	s.syncAsSint32LE(_sequenceOffset);
	s.syncAsByte(_keepActive);
	s.syncAsSint32LE(_fontNum);
	s.syncAsSint32LE(_field26);

	s.syncAsSint32LE(_objectIndex);
	SYNC_POINTER(_sceneObject);
	for (int i = 0; i < 6; ++i)
		SYNC_POINTER(_objectList[i]);

	int seqSize = _sequenceData.size();
	s.syncAsUint32LE(seqSize);
	if (s.isLoading())
		_sequenceData.resize(seqSize);
	if (seqSize > 0)
		s.syncBytes(&_sequenceData[0], seqSize);
}