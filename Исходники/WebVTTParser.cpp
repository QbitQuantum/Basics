bool WebVTTParser::parseFloatPercentageValuePair(VTTScanner& valueScanner, char delimiter, FloatPoint& valuePair)
{
    float firstCoord;
    if (!parseFloatPercentageValue(valueScanner, firstCoord))
        return false;

    if (!valueScanner.scan(delimiter))
        return false;

    float secondCoord;
    if (!parseFloatPercentageValue(valueScanner, secondCoord))
        return false;

    valuePair = FloatPoint(firstCoord, secondCoord);
    return true;
}