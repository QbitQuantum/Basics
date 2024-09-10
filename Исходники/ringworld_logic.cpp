void SceneArea::synchronize(Serializer &s) {
	if (s.getVersion() >= 2)
		SavedObject::synchronize(s);

	s.syncAsSint16LE(_pt.x);
	s.syncAsSint16LE(_pt.y);
	s.syncAsSint32LE(_resNum);
	s.syncAsSint32LE(_rlbNum);
	s.syncAsSint32LE(_subNum);
	s.syncAsSint32LE(_actionId);
	_bounds.synchronize(s);
}