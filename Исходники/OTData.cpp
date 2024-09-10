OTData& OTData::operator+=(const OTData& rhs)
{
    if (rhs.GetSize() > 0) {
        Concatenate(rhs.data_, rhs.GetSize());
    }
    return *this;
}