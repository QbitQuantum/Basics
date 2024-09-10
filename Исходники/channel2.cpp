void Channel2::reset() {
	// cycleCounter >> 12 & 7 represents the frame sequencer position.
	cycleCounter_ &= 0xFFF;
	cycleCounter_ += ~(cycleCounter_ + 2) << 1 & 0x1000;

	dutyUnit_.reset();
	envelopeUnit_.reset();
	setEvent();
}