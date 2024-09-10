BigData BigData::operator/(const BigData& bigData)
{
	if (bigData.m_llValue == 0)
	{
		assert("³ýÊý²»ÄÜÎª0");
		return BigData(INT64(0));
	}
	if (!IsINT64Overflow() && bigData.IsINT64Overflow())
	{
		return BigData(m_llValue / bigData.m_llValue);
	}
	return BigData(Div(m_strData, bigData.m_strData).c_str());
}