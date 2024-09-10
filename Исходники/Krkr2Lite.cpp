CKrkr2::XP3ExtractionFilterFunc CKrkr2Lite::SetXP3ExtractionFilter(CKrkr2::XP3ExtractionFilterFunc Filter)
{
    return (CKrkr2::XP3ExtractionFilterFunc)_InterlockedExchangePointer(&m_ExtractionFilter, Filter);
}