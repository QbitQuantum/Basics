LogPmQ::LogPmQ(float llr2Value)
  : m_isPos( !signbit(llr2Value) ),
    m_val( logf(tanhf(fabsf(llr2Value))) )
{}