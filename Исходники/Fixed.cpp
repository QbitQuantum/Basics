std::string fixed::ToString() const
{
    std::stringstream stream;
    stream << m_num;

    std::string str = stream.str();

    if ((str.length() != m_precision) && ((m_num / (unsigned long int)powl(10.0, m_precision)) == 0))
    {
        // this handles the case where a fixed has no integer part (like 0.00003)
        // In this case, m_num is stored as 3, and is converted the same way
        // add the leading zeros:

        str.insert(0, std::string(m_precision, '0'));
    }

    if (str.length() - m_precision == 0)
        str.insert(0, "0."); // we want a leading 0 if there is no integer part to this fixed
    else if (m_precision != 0)
        str.insert(str.length() - m_precision, ".");

    if (!m_positive && (str.length() - m_precision != 0)) // don't add a "-" if we're a 0 number!
        str.insert(0, "-");

    return str;
}