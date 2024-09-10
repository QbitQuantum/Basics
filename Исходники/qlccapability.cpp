bool QLCCapability::overlaps(const QLCCapability& cap)
{
    if (m_min >= cap.min() && m_min <= cap.max())
        return true;
    else if (m_max >= cap.min() && m_max <= cap.max())
        return true;
    else if (m_min <= cap.min() && m_max >= cap.min())
        return true;
    else
        return false;
}