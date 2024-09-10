/**
 * Converts an epicsTime to a date string
 *
 * @param  t  the time to convert. 
 * @return The date string.
 */
std::string getDate(const epicsTime & t)
{
    char buf[1024];
    buf[0] = '\0';
    buf[sizeof(buf)-1] = '\0';
    t.strftime(buf, sizeof(buf)-1, "%c");
    return buf;
}