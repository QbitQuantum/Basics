bool FloatQuad::isCounterclockwise() const
{
    // Return if the two first vectors are turning clockwise. If the quad is convex then all following vectors will turn the same way.
    return determinant(m_p2 - m_p1, m_p3 - m_p2) < 0;
}