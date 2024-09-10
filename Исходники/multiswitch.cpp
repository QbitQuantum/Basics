MultiSwitch::MultiSwitch(int Pin0, int Pin1, int Pin2, int Pin3, int Pin4, int Pin5, int Pin6, int Pin7)
{
  _aPinPort[0] = Pin0;
  _aPinPort[1] = Pin1;
  _aPinPort[2] = Pin2;
  _aPinPort[3] = Pin3;
  _aPinPort[4] = Pin4;
  _aPinPort[5] = Pin5;
  _aPinPort[6] = Pin6;
  _aPinPort[7] = Pin7;

  _nPins = 0;

  for (byte i = 0; i < 8; i++)
  {
    if (_aPinPort[i] >= 0)
    {
      pinMode(_aPinPort[i], INPUT_PULLUP);
      _nPins = i + 1;
    }
  }

  _nDebounceCounter = 999;
  _valueScan = 255;
  Scan();
  _value = _valueScan;
  _bChanged = false;
}