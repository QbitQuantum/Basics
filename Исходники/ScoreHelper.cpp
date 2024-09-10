ScoreHelper::ScoreHelper(const RewardInfo& reward_info)
    : m_SampleSize(0)
    , m_Zero(reward_info.getInstance())
    , m_Total(m_Zero)
    , m_SumOfSquares(m_Zero)
    , m_Average(m_Zero)
    , m_StandardDeviation(m_Zero)
    , m_Min(m_Zero)
    , m_Max(m_Zero)
{
    for (size_t i = 0; i < m_Min.size(); ++i)
    {
        m_Min[i] = FLT_MAX;
        m_Max[i] = -FLT_MAX;
    }
}