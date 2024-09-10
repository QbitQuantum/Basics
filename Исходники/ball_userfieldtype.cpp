// CLASS METHODS
bsl::ostream& UserFieldType::print(bsl::ostream&       stream,
                                   UserFieldType::Enum value,
                                   int                 level,
                                   int                 spacesPerLevel)
{
    bslim::Printer printer(&stream, level, spacesPerLevel);

    printer.start(true);
    stream << toAscii(value);
    printer.end(true);

    return stream;
}