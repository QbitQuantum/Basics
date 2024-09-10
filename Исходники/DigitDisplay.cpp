void DigitDisplay::setColon(bool enable)
{
    if (_colon != enable) {
        _colon = enable;
        
        if (enable) {
            _content[POSITION_COLON] |= 0x80;
        } else {
            _content[POSITION_COLON] &= 0x7F;
        }
        
        writeRaw(POSITION_COLON, _content[POSITION_COLON]);
    }    
}