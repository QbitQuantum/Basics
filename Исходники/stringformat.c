static void test_characterrange(void)
{
    CharacterRange ranges[3];
    INT count;
    GpStringFormat* format;
    GpStatus stat;

    stat = GdipCreateStringFormat(0, LANG_NEUTRAL, &format);
    expect(Ok, stat);
    stat = GdipSetStringFormatMeasurableCharacterRanges(NULL, 3, ranges);
    expect(InvalidParameter, stat);
    stat = GdipSetStringFormatMeasurableCharacterRanges(format, 0, ranges);
    expect(Ok, stat);
    stat = GdipSetStringFormatMeasurableCharacterRanges(format, 3, NULL);
    expect(InvalidParameter, stat);

    stat = GdipSetStringFormatMeasurableCharacterRanges(format, 3, ranges);
    expect(Ok, stat);
    stat = GdipGetStringFormatMeasurableCharacterRangeCount(format, &count);
    expect(Ok, stat);
    if (stat == Ok) expect(3, count);

    stat= GdipDeleteStringFormat(format);
    expect(Ok, stat);
}