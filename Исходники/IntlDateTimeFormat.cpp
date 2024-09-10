void IntlDateTimeFormat::UDateFormatDeleter::operator()(UDateFormat* dateFormat) const
{
    if (dateFormat)
        udat_close(dateFormat);
}