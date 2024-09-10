void OLED12864::print(uint8_t x, uint8_t line, const char ch[])
{

    // simplified for testing only
    // if (invalidXL(x, line)) return;
    // -- This will introduce a bug if last printing stopped at last position which will not advance the line until next print.

    // Try just valid the line only
    if (invalidLine(line)) return;

    uint8_t j;
    uint16_t c;
    uint16_t bPos;
    uint8_t data;

    _cursor.x = x;
    _cursor.y = line * OLED_LINE_HEIGHT;

    int maxChars, charsWrite;

    j = 0;
    while (ch[j] != '\0')
    {
        adjCursor();
        maxChars = ((OLED_WIDTH - _cursor.x) / _font.width); 	// number of characters can be printed in this line.
        charsWrite = 0;
        if (maxChars > 0)
        {
            line = (_cursor.y / OLED_LINE_HEIGHT);
            for (int k = 0; k < _font.lines; k++)
            {
                setDisplayPos(_cursor.x, line + k);
                bPos = posXL(_cursor.x, line + k);
                for (int l = 0; (( l < maxChars) && (ch[j + l] != '\0')) ; l++)
                {
                    c =ch[j+l] - _font.offset;

                    if (_font.width <= 24) {
                        if (_directDraw) Wire.beginTransmission(_i2cAddress);
                        if (_directDraw) Wire.write(0x40);
                        for (uint8_t i=0; i < _font.width; i++)
                        {
                            data = getFontData(c, 5 + c * _font.bytePerChar + k * _font.width + i);
                            if (_directDraw) Wire.write(data);
                            if (_enableBuffer)
                                _buffer[bPos++] = data;
                        }
                        if (_directDraw) Wire.endTransmission();
                    } else {
                        for (uint8_t i=0; i < _font.width; i += 8)
                        {
                            if (_directDraw) Wire.beginTransmission(_i2cAddress);
                            if (_directDraw) Wire.write(0x40);
                            uint8_t maxX = min(8, _font.width - i);
                            for (uint8_t x=0; x < maxX; x++) {
                                data = getFontData(c, 5 + c * _font.bytePerChar + k * _font.width + i + x);
                                if (_directDraw) Wire.write(data);
                                if (_enableBuffer)
                                    _buffer[bPos++] = data;
                            }
                            if (_directDraw) Wire.endTransmission();
                        }
                    }

                    if (k == 0) charsWrite++;  // only count on first row of chars; it may use l as charsWrite, but will need to check stop condition
                }
            }
        }
        j += charsWrite;
        _cursor.x += charsWrite * _font.width;
        if (ch[j] != '\0')
        {
            // advance to next line
            _cursor.x = 0;
            _cursor.y += _font.height;
        }
    }
}