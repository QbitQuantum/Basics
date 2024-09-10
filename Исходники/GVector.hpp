// Vector atanh
inline
GVector atanh(const GVector &v)
{
    GVector result(v.m_num);
    for (int i = 0; i < v.m_num; ++i)
        result.m_data[i] = atanh(v.m_data[i]);
    return result;
}