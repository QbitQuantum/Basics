// CLASS METHODS
bsl::ostream& DayCountConvention::print(
                                       bsl::ostream&            stream,
                                       DayCountConvention::Enum value,
                                       int                      level,
                                       int                      spacesPerLevel)
{
    bslim::Printer printer(&stream, level, spacesPerLevel);
    printer.start(true);  // 'true' -> suppress '['
    stream << toAscii(value);
    printer.end(true);    // 'true' -> suppress ']'

    return stream;
}