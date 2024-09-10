void TextLCD::writeByte(int value) {
    _e = 1;
    __nop();    
    _d = value >> 4;
    __nop();
    _e = 0;
    __nop();
    _e = 1;
    __nop();
    _d = value >> 0;
    __nop();
    _e = 0;
}