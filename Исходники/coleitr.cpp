void CollationElementIterator::setOffset(int32_t newOffset, 
                                         UErrorCode& status)
{
    ucol_setOffset(m_data_, newOffset, &status);
}