void cmdReleaseKey(AgiGame *state, uint8 *p) {
	if (getVersion() >= 0x3098) {
		state->_vm->_egoHoldKey = false;
	}
}