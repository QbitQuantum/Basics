void MidiController::loop() {
  unsigned long now = micros();
  if (now >= _next) {
    _next += _sleep;

    Clock();
    if (_timerCallback) {
      _timerCallback();
    }
  }

  midiOUT2.read();
  midiOUT.read();
  midiIN.read();
}